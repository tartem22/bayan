#include <iostream>

#include "cmd_line_parser.h"
#include "bayan/factory.h"

int main(int argc, const char *argv[])
{
    bayan::BayanFatory factory;

    std::vector<std::string> settings;
    settings.emplace_back("-i");
    settings.emplace_back("/home/tsikunov/Projects/BoostSharedMemory");
    settings.emplace_back("/home/tsikunov/Projects/BestBuddiesSimilarity");
    settings.emplace_back("-e");
    settings.emplace_back("/home/tsikunov/Projects/BestBuddiesSimilarity/build");
    settings.emplace_back("-l");
    settings.emplace_back("2");
    settings.emplace_back("-s");
    settings.emplace_back("5");
    settings.emplace_back("-m");
    settings.emplace_back("BestBuddiesSimilarity.*");
    settings.emplace_back("-b");
    settings.emplace_back("6");
    settings.emplace_back("-a");
    settings.emplace_back("crc32");

    argc = settings.size() + 1;
    for(int i = 1; i <= settings.size(); i++)
    {
        argv[i] = settings.at(i - 1).c_str();
    }

    cmd_parser::parse(argc, argv, &factory);

    std::shared_ptr<bayan::Bayan> duplicateFinder = factory.create();

    duplicateFinder->find();

    return 0;
}