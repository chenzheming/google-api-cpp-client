#include "new_http_transport_layer_config.h"

namespace googleapis {
    namespace util {
        using client::HttpTransportLayerConfig;

        HttpTransportLayerConfig *NewHttpTransportLayerConfig()
        {
            auto *config = new HttpTransportLayerConfig;
            auto *factory = new client::CurlHttpTransportFactory(config);

            config->ResetDefaultTransportFactory(factory); // ownership of `factory` transferred

            return config;
        }
    }
};
