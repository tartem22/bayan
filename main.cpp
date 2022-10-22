#include <iostream>

#include "cmd_line_parser.h"
#include "bayan/factory.h"

void test_crc32()
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
    const char *argv[settings.size()];
    for (int i = 1; i <= settings.size(); i++)
    {
        argv[i] = settings.at(i - 1).c_str();
    }

    cmd_parser::parse(argc, argv, &factory);

    std::shared_ptr<bayan::Bayan> duplicateFinder = factory.create();

    bayan::EqualFileNames duplicates = duplicateFinder->find();

    for (const auto &dupl : duplicates)
    {
        for (const auto &e : dupl)
        {
            std::cout << e << "\t";
        }
        std::cout << std::endl;
    }
}

void test_md5()
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
    settings.emplace_back("md5");

    int argc = settings.size() + 1;
    const char *argv[settings.size()];
    for (int i = 1; i <= settings.size(); i++)
    {
        argv[i] = settings.at(i - 1).c_str();
    }

    cmd_parser::parse(argc, argv, &factory);

    std::shared_ptr<bayan::Bayan> duplicateFinder = factory.create();

    bayan::EqualFileNames duplicates = duplicateFinder->find();

    for (const auto &dupl : duplicates)
    {
        for (const auto &e : dupl)
        {
            std::cout << e << "\t";
        }
        std::cout << std::endl;
    }
}

void workflow(int argc, const char *argv[])
{
    bayan::BayanFatory factory;

    cmd_parser::parse(argc, argv, &factory);

    std::shared_ptr<bayan::Bayan> duplicateFinder = factory.create();

    bayan::EqualFileNames duplicates = duplicateFinder->find();

    for (const auto &dupl : duplicates)
    {
        for (const auto &e : dupl)
        {
            std::cout << e << "\t";
        }
        std::cout << std::endl;
    }
}

int main(int argc, const char *argv[])
{
    try
    {
        workflow(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
