/* Ported from Calendar Sample */

#include "googleapis/client/auth/file_credential_store.h"

#include "authorization.h"

namespace googleapis {
namespace util {
    using std::cout;
    using std::endl;
    using std::cin;

    using client::FileCredentialStoreFactory;
    using client::OAuth2RequestOptions;
#if HAVE_OPENSSL
    using client::OpenSslCodecFactory;
#endif
    using client::StatusCanceled;
    using client::StatusInvalidArgument;
    using client::StatusOk;

    static util::Status PromptShellForAuthorizationCode(OAuth2AuthorizationFlow *flow,
                                                        const OAuth2RequestOptions &options,
                                                        string *authorization_code)
    {
        string url = flow->GenerateAuthorizationCodeRequestUrlWithOptions(options);

        cout << "Enter the following URL into a browser:" << endl;
        cout << url << endl;
        cout << endl;
        cout << "Enter the browser's response to confirm authorization: ";

        authorization_code->clear();

        cin >> *authorization_code;

        if (authorization_code->empty())
        {
            return StatusCanceled("Canceled");
        }
        else
        {
            return StatusOk();
        }
    }

    std::unique_ptr<OAuth2AuthorizationFlow> authorization_flow_create(const HttpTransportLayerConfig &config, const string &client_secrets_file, const string &scope, const string &credential_name, util::Status &status)
    {
        auto *transport = config.NewDefaultTransport(&status);
        if (!status.ok())
        {
            return nullptr;
        }

        std::unique_ptr<OAuth2AuthorizationFlow> flow(OAuth2AuthorizationFlow::MakeFlowFromClientSecretsPath(client_secrets_file, transport, &status));
        // ownership of `transport` transferred

        if (!status.ok())
        {
            return nullptr;
        }

        flow->set_default_scopes(scope);
        flow->mutable_client_spec()->set_redirect_uri(OAuth2AuthorizationFlow::kOutOfBandUrl);
        flow->set_authorization_code_callback(NewPermanentCallback(&PromptShellForAuthorizationCode, flow.get()));

        string home_path;

        status = FileCredentialStoreFactory::GetSystemHomeDirectoryStorePath(&home_path);
        if (!status.ok())
        {
            return nullptr;
        }

        FileCredentialStoreFactory store_factory(home_path);
        // Use a credential store to save the credentials between runs so that
        // we dont need to get permission again the next time we run. We are
        // going to encrypt the data in the store, but leave it to the OS to
        // protect access since we do not authenticate users in this sample.

#if HAVE_OPENSSL
        OpenSslCodecFactory *openssl_factory = new OpenSslCodecFactory;
        status = openssl_factory->SetPassphrase(flow->client_spec().client_secret());
        if (!status.ok())
        {
            return nullptr;
        }

        store_factory.set_codec_factory(openssl_factory);
#endif
        flow->ResetCredentialStore(store_factory.NewCredentialStore(credential_name, &status));

        return flow;
    }
}
}
