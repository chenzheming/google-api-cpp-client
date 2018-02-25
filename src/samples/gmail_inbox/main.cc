#include <iostream>
#include <sstream>
#include <memory>

#include "googleapis/base/port.h"

#include "command.h"

static const char *SUB_COMMAND_RETRIEVE = "retrieve";
static const char *SUB_COMMAND_SHOW = "show";
static const char *CACHE_FILENAME = "gmail_inbox_cache";

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        if (0 == strcasecmp(argv[1], SUB_COMMAND_RETRIEVE))
        {
            std::ostringstream oss;

            oss << argv[0] << " " << argv[1];

            std::unique_ptr<char> cmd(strdup(oss.str().c_str()));

            argv[1] = cmd.get();

            return command::retrieve(argc - 1, argv + 1, CACHE_FILENAME);
        }
        else if (0 == strcasecmp(argv[1], SUB_COMMAND_SHOW))
        {
            return command::show(CACHE_FILENAME);
        }
        else
        {
            std::cout << "Unidentified sub-command: " << argv[1] << std::endl;
        }
    }

    std::cout << "Usage:" << std::endl;
    std::cout << "1. " << argv[0] << " {" << SUB_COMMAND_RETRIEVE << " ...}: retrieve messages from gmail" << std::endl;
    std::cout << "2. " <<argv[0] << " {" << SUB_COMMAND_SHOW << "}: show cached messages"<< std::endl;

    return -1;
}
