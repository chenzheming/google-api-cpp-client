#ifndef __HTTP_STATUS_H__
#define __HTTP_STATUS_H__

#include <string>
#include "googleapis/client/service/client_service.h"

namespace googleapis {
namespace util {
    using std::string;
    string http_error_parse(client::ClientServiceRequest *request);
}
}

#endif
