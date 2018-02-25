#include <iostream>
#include <algorithm>

#include <boost/beast/core/detail/base64.hpp> // http://www.boost.org/users/history/version_1_66_0.html

#include "google/gmail_api/gmail_api.h"  // NOLINT

#include "googleapis/strings/strcat.h"

#include "authorization.h"
#include "http_status.h"

#include "inbox.h"

namespace googleapis {
namespace gmail {

    using client::OAuth2RequestOptions;

    using client::StatusCanceled;
    using client::StatusInvalidArgument;
    using client::StatusOk;

    using google_gmail_api::ListMessagesResponse;
    using google_gmail_api::UsersResource_MessagesResource_ListMethod;
    using google_gmail_api::UsersResource_MessagesResource_GetMethod;

    static std::unique_ptr<GmailService> gmail_service_create(const HttpTransportLayerConfig &config, util::Status &status)
    {
        auto *transport = config.NewDefaultTransport(&status);
        if (!status.ok())
        {
            return nullptr;
        }

        std::unique_ptr<GmailService> service(new GmailService(transport)); // ownership of `transport` transferred

        return service;
    }

    static void message_view(const Message &msg, std::function<void(const string &)>cb)
    {
        if (!msg.has_payload())
        {
            return;
        }

        auto &payload = msg.get_payload();

        if (!payload.has_headers())
        {
            return;
        }

        auto &headers = payload.get_headers();

        for (const auto &header: headers)
        {
            if (!header.has_name() || !header.has_value())
            {
                continue;
            }

            auto &name = header.get_name();

            if (("Date" == name) || ("Subject" == name) ||
                ("From" == name) || ("To" == name))
            {
                cb(StrCat(name, ":\n", header.get_value().as_string(), "\n"));
            }
        }

        if (!payload.has_parts())
        {
            return;
        }

        auto &parts = payload.get_parts();
        if (parts.empty())
        {
            return;
        }

        auto &part = parts[0];
        if (!part.has_body())
        {
            return;
        }

        auto &body = part.get_body();
        if (!body.has_data())
        {
            return;
        }

        cb(StrCat("Message:\n", boost::beast::detail::base64_decode(body.get_data().as_string()), "\n\n"));
    }

    util::Status Inbox::init(const HttpTransportLayerConfig &config, const string &client_secrets_file)
    {
        util::Status status;

        flow_ = util::authorization_flow_create(config, client_secrets_file, GmailService::SCOPES::GMAIL_READONLY, CREDENTIAL_NAME, status);
        if (!status.ok())
        {
            return status;
        }

        service_ = gmail_service_create(config, status);

        return status;
    }

    util::Status Inbox::message_retrieve(const string &credential_store_key, const string &after, const string &before, std::function<void(const string &)>cb)
    {
        OAuth2Credential credential;

        util::Status status = authorize(credential, credential_store_key);
        if (!status.ok())
        {
            return status;
        }

        return message_list(credential, after, before, std::bind(message_view, std::placeholders::_1, cb));
    }

    util::Status Inbox::authorize(OAuth2Credential &credential, const string &credential_store_key)
    {
        OAuth2RequestOptions options;
        options.email = credential_store_key;

        util::Status status = flow_->RefreshCredentialWithOptions(options, &credential);
        if (!status.ok())
        {
            return status;
        }

        credential.set_flow(flow_.get());

        return StatusOk();
    }

    util::Status Inbox::message_list(OAuth2Credential &credential, const string &after, const string &before, std::function<void(const Message &)>cb) const
    {
        std::unique_ptr<UsersResource_MessagesResource_ListMethod> method(service_->get_users().get_messages().NewListMethod(&credential, "me", after, before));
        std::unique_ptr<ListMessagesResponse> msg_list(ListMessagesResponse::New());

        util::Status status = method->ExecuteAndParseResponse(msg_list.get());
        if (!status.ok())
        {
            return StatusCanceled(util::http_error_parse(method.get()));
        }

        for (const auto &message: msg_list->get_messages())
        {
            if (message.has_id())
            {
                message_get(credential, message.get_id().as_string(), cb);
            }
        }

        return StatusOk();
    }

    util::Status Inbox::message_get(OAuth2Credential &credential, const string &msg_id, std::function<void(const Message &)>cb) const
    {
        std::unique_ptr<UsersResource_MessagesResource_GetMethod> method(service_->get_users().get_messages().NewGetMethod(&credential, "me", msg_id));
        std::unique_ptr<Message> msg(Message::New());

        util::Status status = method->ExecuteAndParseResponse(msg.get());
        if (!status.ok())
        {
            return StatusCanceled(util::http_error_parse(method.get()));
        }

        cb(*msg);

        return StatusOk();
    }

    const char *Inbox::CREDENTIAL_NAME = "GmailInbox";
    std::unique_ptr<GmailService> Inbox::service_;
    std::unique_ptr<OAuth2AuthorizationFlow> Inbox::flow_;

}
}
