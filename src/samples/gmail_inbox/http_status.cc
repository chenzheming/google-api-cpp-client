/* Ported from Calendar Sample */

#include "googleapis/client/data/data_reader.h"
#include "http_status.h"

namespace googleapis {
namespace util {
    string http_error_parse(client::ClientServiceRequest *request)
    {
        std::ostringstream oss;

        const auto &response = *request->http_response();
        oss << "====  ERROR  ====" << std::endl;
        oss << "Status: " << response.status().error_message() << std::endl;

        if (response.transport_status().ok())
        {
            oss << "HTTP Status Code = " << response.http_code() << std::endl;
            oss << std::endl
                << response.body_reader()->RemainderToString() << std::endl;
        }

        oss << std::endl;

        return oss.str();
    }
}
}
