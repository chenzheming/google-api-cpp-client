#include <unistd.h>
#include <ctime>

#include <iomanip>
#include <iostream>
#include <memory>

#include "googleapis/client/util/status.h"
#include "googleapis/strings/strcat.h"

#include "encription.h"
#include "inbox.h"
#include "new_http_transport_layer_config.h"
#include "storage.h"

#include "command.h"

namespace command {

    using namespace googleapis;

namespace retrieval_option {

    using client::StatusCanceled;
    using client::StatusInvalidArgument;
    using client::StatusOk;

    static util::Status filename_validate(const string &filename)
    {
        if (filename.find("/") != string::npos)
        {
            return StatusInvalidArgument("A filename cannot contain '/'");
        }
        else if (("." == filename) || (".." == filename))
        {
            return StatusInvalidArgument(StrCat("A filename cannot be '", filename, "'"));
        }

        return StatusOk();
    }

    static util::Status time_validate(const string &time, size_t len, const string &fmt)
    {
        if (time.length() == len)
        {
            std::istringstream iss(time);
            tm t;

            iss >> std::get_time(&t, fmt.c_str());
            if (!iss.fail() && iss.eof())
            {
                return StatusOk();
            }
        }

        return StatusInvalidArgument(StrCat("Invalid time: ", time));
    }

    static util::Status option_parse(int argc, char *argv[], string &secret_path, string &credential_filename, string &after, string &before)
    {
        int c;
        util::Status status;

        while (-1 != (c = getopt(argc, argv, "s:c:f:t:")))
        {
            switch (c)
            {
                case 's':
                    secret_path = optarg;
                    break;

                case 'c':
                    credential_filename = optarg;
                    status = filename_validate(credential_filename);
                    if (!status.ok())
                    {
                        return status;
                    }
                    break;

                case 'f':
                    after = optarg;
                    status = time_validate(after, strlen("YYYY/MM/DD"), "%Y/%m/%d");
                    if (!status.ok())
                    {
                        return status;
                    }
                    break;

                case 't':
                    before = optarg;
                    status = time_validate(before, strlen("YYYY/MM/DD"), "%Y/%m/%d");
                    if (!status.ok())
                    {
                        return status;
                    }
                    break;

                default:
                    return  StatusInvalidArgument("Invalid option");
            }
        }

        if (secret_path.empty())
        {
            return StatusInvalidArgument("Client secret file unspecified");
        }

        return StatusOk();
    }

    static void usage_print(const char *basename)
    {
        std::cout << "Usage: " << std::endl;
        std::cout << basename << " -s secret_path [-c credential_filename] [-f date_from]  [-t date_to]" << std::endl;
        std::cout << "-s: specifying the client secret file in json format" << std::endl;
        std::cout << "-c: optional, specifying the filename saving the credentials between runs" << std::endl;
        std::cout << "-f: optional, specifying the start of the retrieval period in YYYY/MM/DD format" << std::endl;
        std::cout << "-t: optional, specifying the end of the retrieval period in YYYY/MM/DD format" << std::endl;
        std::cout << "e.g. " << basename << " -s secret.json -c credential -f 2018/02/01 -t 2018/02/28" << std::endl;
    }
}

    int retrieve(int argc, char *argv[], const string &cache_filename)
    {
        if (1 == argc)
        {
            retrieval_option::usage_print(argv[0]);
            return -1;
        }

        util::Status status;

        string secret_path;
        string credential_filename;
        string after;
        string before;

        status = retrieval_option::option_parse(argc, argv, secret_path, credential_filename, after, before);
        if (!status.ok())
        {
            std::cout << "Retrieval option error:" << std::endl << status.error_message() << std::endl;
            retrieval_option::usage_print(argv[0]);
            return -1;
        }

        std::unique_ptr<client::HttpTransportLayerConfig> config(util::NewHttpTransportLayerConfig());

        status = gmail::Inbox::init(*config, secret_path);
        if (!status.ok())
        {
            std::cout << "Initialize error:" << std::endl << status.error_message() << std::endl;
            return -1;
        }

        util::Storage storage(cache_filename);
        gmail::Inbox inbox;

        status = inbox.message_retrieve(credential_filename, after, before,
                                        [&storage](const string &text){storage.append(text);});
        if (!status.ok())
        {
            std::cout << "Retrieve error:" << std::endl << status.error_message() << std::endl;
            return -1;
        }

        storage.manipulate(util::encrypt);
        storage.commit();

        std::cout << "Done!" << std::endl;

        return 0;
    }

    int show(const string &cache_filename)
    {
        util::Storage storage(cache_filename);

        storage.load();
        std::cout << storage.manipulate(util::decrypt) << std::endl;

        return 0;
    }
}
