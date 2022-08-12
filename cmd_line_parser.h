#ifndef CMD_LINE_PARSER_H
#define CMD_LINE_PARSER_H

#include "bayan/factory.h"

namespace cmd_parser
{
    void parse(int argc, const char *argv[], bayan::BayanFatory *factory);
}
#endif // CMD_LINE_PARSER_H