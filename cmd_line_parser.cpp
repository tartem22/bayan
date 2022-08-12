#include "cmd_line_parser.h"

#include <boost/program_options.hpp>

namespace po = boost::program_options;

void cmd_parser::parse(int argc, const char *argv[], bayan::BayanFatory *factory)
{
    po::options_description desc{"Options"};
    desc.add_options()("help,h", "Help")
    ("included,i", po::value<std::vector<std::string>>()->multitoken()->notifier(std::bind(&bayan::BayanFatory::setIncludedDirectories, factory, std::placeholders::_1)), "Directories included in the scan")
    ("excluded,e", po::value<std::vector<std::string>>()->multitoken()->notifier(std::bind(&bayan::BayanFatory::setExcludedDirectories, factory, std::placeholders::_1)), "Directories excluded from scanning")
    ("lavel,l", po::value<int>()->default_value(0)->notifier(std::bind(&bayan::BayanFatory::setScanningLavel, factory, std::placeholders::_1)), "Scanning lavel")
    ("min_size,s", po::value<int>()->default_value(1)->notifier(std::bind(&bayan::BayanFatory::setMinSize, factory, std::placeholders::_1)), "Minimum file size, bytes")
    ("file_masks,m", po::value<std::vector<std::string>>()->multitoken()->notifier(std::bind(&bayan::BayanFatory::setFileMasks, factory, std::placeholders::_1)), "File masks")
    ("block_size,b", po::value<int>()->notifier(std::bind(&bayan::BayanFatory::setBlockSize, factory, std::placeholders::_1)), "Block size")
    ("hash,a", po::value<std::string>()->notifier(std::bind(&bayan::BayanFatory::setHashingAlgorithm, factory, std::placeholders::_1)), "Hashing algorithm");

    po::variables_map vm;
    po::store(parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
}