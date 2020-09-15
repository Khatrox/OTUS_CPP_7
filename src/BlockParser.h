//
// Created by xMellox on 15-Sep-20.
//

#ifndef OTUS_CPP_7_PARSER_H
#define OTUS_CPP_7_PARSER_H

#include <string>

struct BlockParser
{
    virtual ~BlockParser() = default;
    virtual void parse(const std::string& str) = 0;
};

#endif //OTUS_CPP_7_PARSER_H
