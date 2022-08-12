#include <gtest/gtest.h>

#include "cmd_line_parser.h"
#include "bayan/factory.h"

TEST(duplicate_finder, basic_test_1)
{
    bayan::BayanFatory factory;

    std::vector<std::string> settings;
    settings.emplace_back("-i");
    settings.emplace_back("../test_data");
    settings.emplace_back("-e");
    settings.emplace_back("../test_data/test_data_2/test_data_22");
    settings.emplace_back("-l");
    settings.emplace_back("4");
    settings.emplace_back("-s");
    settings.emplace_back("5");
    settings.emplace_back("-m");
    settings.emplace_back("*eq.*");
    settings.emplace_back("-b");
    settings.emplace_back("6");
    settings.emplace_back("-a");
    settings.emplace_back("crc32");

    int argc = settings.size() + 1;
    const char *argv[100];
    for (int i = 1; i <= settings.size(); i++)
    {
        argv[i] = settings.at(i - 1).c_str();
    }

    cmd_parser::parse(argc, argv, &factory);

    std::shared_ptr<bayan::Bayan> duplicateFinder = factory.create();

    duplicateFinder->find();
}

// #include <fstream>
// TEST(duplicate_finder, basic_test_2)
// {
//     std::ifstream file;
//     std::string path = "/home/tsikunov/cpp_projects/bayan/test_data/test0.txt";
//     if (!file.is_open())
//         file.open(path, std::ios::binary);
//     char *buffer = new char[23];
//     while (!file.eof())
//     {
//         memset(buffer, '\0', 23);
//         file.read(buffer, 23);
//         if (file.eof())
//         {
//             std::cout << "EOF" << std::endl;
//         }
//     }
// }