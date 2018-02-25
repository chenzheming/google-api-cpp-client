#include <algorithm>

#include "encription.h"

namespace googleapis {
namespace util {

    static const string::value_type KEY = 0xA5;

    static string &endec(string &text)
    {
        std::transform(text.cbegin(), text.cend(), text.begin(),
                       [](string::value_type c){return c ^ KEY;});

        return text;
    }

    string &encrypt(string &text)
    {
        return endec(text);
    }

    string &decrypt(string &text)
    {
        return endec(text);
    }
}
}
