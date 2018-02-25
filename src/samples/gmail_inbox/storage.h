#ifndef __STORAGE_H__
#define __STORAGE_H__

#include <functional>
#include <string>

namespace googleapis {
namespace util {
    using std::string;

    class Storage {
    public:
            Storage(const string &filename);

            void append(const string &text);
            void clear();
            void commit();
            void load();
            const string &manipulate(std::function<void(string &)> cb);

    private:
            string filename_;
            string cache_;
    };
}
}

#endif
