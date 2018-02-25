#include <iostream>

#include "encription.h"

using namespace googleapis::util;

int main(int argc, char *argv[])
{
    std::string raw(argv[0]);

    std::string encrypted(raw);
    encrypt(encrypted);
    std::cout << "On encription: ";
    if (encrypted == raw)
    {
        std::cout << "Fail"  << std::endl;
        return -1;
    }

    std::cout << "Pass" << std::endl;

    std::string decrypted(encrypted);
    decrypt(decrypted);
    std::cout << "On decription: ";
    if (decrypted != raw)
    {
        std::cout << "Fail" << std::endl;
        return -1;
    }

    std::cout << "Pass" << std::endl;

    return 0;
}
