#ifndef __INBOX_H__
#define __INBOX_H__

#include <functional>
#include <memory>
#include <string>

#include "googleapis/client/auth/oauth2_authorization.h"
#include "googleapis/client/util/status.h"

#include "google/gmail_api/message.h"
#include "google/gmail_api/gmail_service.h"

namespace googleapis {
namespace gmail {
    using std::string;

    using client::HttpTransportLayerConfig;
    using client::OAuth2Credential;
    using client::OAuth2AuthorizationFlow;

    using google_gmail_api::Message;
    using google_gmail_api::GmailService;

    class Inbox {
    public:
        static util::Status init(const HttpTransportLayerConfig &config, const string &client_secrets_file);
        util::Status message_retrieve(const string &credential_store_key, const string &after, const string &before, std::function<void(const string &)> cb);

    private:
        static const char *CREDENTIAL_NAME;
        static std::unique_ptr<GmailService> service_;
        static std::unique_ptr<OAuth2AuthorizationFlow> flow_;

        util::Status authorize(OAuth2Credential &credential, const string &credential_store_key);

        util::Status message_list(OAuth2Credential &credential, const string &after, const string &before, std::function<void(const Message &)> cb) const;
        util::Status message_get(OAuth2Credential &credential, const string &msg_id, std::function<void(const Message &)> cb) const;
    };
}
}

#endif
