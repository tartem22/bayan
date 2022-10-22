#include <gtest/gtest.h>

#include "cmd_line_parser.h"
#include "bayan/factory.h"

TEST(duplicate_finder, test_src32)
{
    bayan::BayanFatory factory;

    std::vector<std::string> settings;
    settings.emplace_back("-i");
    settings.emplace_back("/test_data");
    settings.emplace_back("-e");
    settings.emplace_back("/test_data/test_data_2/test_data_22");
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

    std::vector<std::vector<std::string>> expected;
    expected.push_back(std::vector<std::string>());
    expected.at(0).push_back("/test_data/test_data_1/test_data_11/test_data_111/test1.txt");
    expected.at(0).push_back("/test_data/test_data_1/test_data_11/test1.txt");
    expected.at(0).push_back("/test_data/test_data_1/test1.txt");
    expected.push_back(std::vector<std::string>());
    expected.at(1).push_back("/test_data/test_data_1/test_data_12/test0.txt");
    expected.at(1).push_back("/test_data/test0.txt");

    EXPECT_EQ(duplicates, expected);
}

TEST(duplicate_finder, test_md5)
{
    bayan::BayanFatory factory;

    std::vector<std::string> settings;
    settings.emplace_back("-i");
    settings.emplace_back("/test_data");
    settings.emplace_back("-e");
    settings.emplace_back("/test_data/test_data_2/test_data_22");
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

    std::vector<std::vector<std::string>> expected;
    expected.push_back(std::vector<std::string>());
    expected.at(0).push_back("/test_data/test_data_1/test_data_11/test_data_111/test1.txt");
    expected.at(0).push_back("/test_data/test_data_1/test_data_11/test1.txt");
    expected.at(0).push_back("/test_data/test_data_1/test1.txt");
    expected.push_back(std::vector<std::string>());
    expected.at(1).push_back("/test_data/test_data_1/test_data_12/test0.txt");
    expected.at(1).push_back("/test_data/test0.txt");

    EXPECT_EQ(duplicates, expected);
}
