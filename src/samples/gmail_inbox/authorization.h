#ifndef __AUTHORIZATION_H__
#define __AUTHORIZATION_H__

#include <iostream>
#include <memory>
#include <string>

#include "googleapis/client/auth/oauth2_authorization.h"
#include "googleapis/client/transport/http_transport.h"
#include "googleapis/client/util/status.h"

namespace googleapis {
namespace util {
    using std::string;
    using client::OAuth2AuthorizationFlow;
    using client::HttpTransportLayerConfig;

    std::unique_ptr<OAuth2AuthorizationFlow> authorization_flow_create(const HttpTransportLayerConfig &config, const string &client_secrets_file, const string &scope, const string &credential_name, util::Status &status);
}
}

#endif
