#ifndef __ENCRIPTION_H__
#define __ENCRIPTION_H__

#include <string>

namespace googleapis {
namespace util {
    using std::string;

    string &encrypt(string &text);
    string &decrypt(string &text);
}
}

#endif
