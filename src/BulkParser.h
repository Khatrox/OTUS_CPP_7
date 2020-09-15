//
// Created by xMellox on 11-Sep-20.
//

#ifndef OTUS_CPP_7_BULKPARSER_H
#define OTUS_CPP_7_BULKPARSER_H

#include <memory>
#include "Bulk.h"
#include "BlockParser.h"

struct BulkParser
{
    explicit BulkParser(std::size_t p_execCommands);
    void passInput(const std::string& input);
    Bulk& getBulk();
    std::size_t getExecCommands() const noexcept;
    void setParser(std::unique_ptr<BlockParser> newParser);
    void endBulk();

private:
    std::size_t execCommands;
    std::unique_ptr<BlockParser> parser;
    Bulk bulk;
};


#endif //OTUS_CPP_7_BULKPARSER_H
