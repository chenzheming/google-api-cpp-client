#include <fstream>

#include "storage.h"

namespace googleapis {
namespace util {

    Storage::Storage(const string &filename): filename_(filename)
    {
    }

    void Storage::append(const string &text)
    {
        cache_.append(text);
    }

    void Storage::clear()
    {
        cache_.clear();
    }

    void Storage::commit()
    {
        std::ofstream ofs(filename_, std::ofstream::out);

        ofs << cache_;

        ofs.close();
    }

    void Storage::load()
    {
        std::ifstream ifs(filename_, std::ifstream::in);

        ifs >> cache_;

        ifs.close();
    }

    const string &Storage::manipulate(std::function<void(string &)> cb)
    {
        cb(cache_);

        return cache_;
    }

}
}
