#ifndef __NEW_HTTP_TRANSPORT_LAYER_CONFIG_H__
#define __NEW_HTTP_TRANSPORT_LAYER_CONFIG_H__

#include "googleapis/client/transport/curl_http_transport.h"

namespace googleapis {
    namespace util {
        client::HttpTransportLayerConfig *NewHttpTransportLayerConfig();
    }
};

#endif
