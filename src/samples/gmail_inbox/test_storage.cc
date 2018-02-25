#include <iostream>
#include <sstream>

#include "storage.h"

using namespace googleapis::util;

void validate(string &cache, const string &expected)
{
    if (cache != expected)
    {
        std::cout << "Fail" << std::endl;
        return;
    }

    std::cout << "Pass" << std::endl;
}

int main(int argc, char *argv[])
{
    Storage s("storage_test_file");
    std::cout << "On init: ";
    s.manipulate(std::bind(validate, std::placeholders::_1, ""));

    s.append(__func__);
    std::cout << "On 1st append: ";
    s.manipulate(std::bind(validate, std::placeholders::_1, __func__));

    s.append(__FILE__);

    std::ostringstream total;
    total << __func__ << __FILE__;

    std::cout << "On 2nd append: ";
    s.manipulate(std::bind(validate, std::placeholders::_1, total.str()));

    s.commit();
    std::cout << "On commit: ";
    s.manipulate(std::bind(validate, std::placeholders::_1, total.str()));

    s.load();
    std::cout << "On 1st load: ";
    s.manipulate(std::bind(validate, std::placeholders::_1, total.str()));

    s.clear();
    std::cout << "On clear: ";
    s.manipulate(std::bind(validate, std::placeholders::_1, ""));

    s.load();
    std::cout << "On 2nd load: ";
    s.manipulate(std::bind(validate, std::placeholders::_1, total.str()));

    return 0;
}
