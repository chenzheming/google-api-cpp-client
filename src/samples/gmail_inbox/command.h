#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string>

namespace command {
    using std::string;

    int retrieve(int argc, char *argv[], const string &cache_filename);
    int show(const string &cache_filename);
}

#endif
