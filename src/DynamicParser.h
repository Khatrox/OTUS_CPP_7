//
// Created by xMellox on 15-Sep-20.
//

#ifndef OTUS_CPP_7_DYNAMICPARSER_H
#define OTUS_CPP_7_DYNAMICPARSER_H


#include "BlockParser.h"
struct BulkParser;

struct DynamicParser : BlockParser
{
    explicit DynamicParser(BulkParser& p_bulkParser);
    void parse(const std::string& str) override;

private:
    BulkParser& bulkParser;
    std::size_t scope_counter;
};



#endif //OTUS_CPP_7_DYNAMICPARSER_H
