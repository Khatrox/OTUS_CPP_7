//
// Created by xMellox on 15-Sep-20.
//

#ifndef OTUS_CPP_7_SIMPLEPARSER_H
#define OTUS_CPP_7_SIMPLEPARSER_H

#include "BlockParser.h"
struct BulkParser;

struct SimpleParser : BlockParser
{
    explicit SimpleParser(BulkParser& p_bulkParser);
    void parse(const std::string& str) override;

private:
    bool isTimeToEndBulk() const noexcept;

    BulkParser& bulkParser;
};


#endif //OTUS_CPP_7_SIMPLEPARSER_H
