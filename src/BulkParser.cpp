//
// Created by xMellox on 11-Sep-20.
//

#include "BulkParser.h"
#include "SimpleParser.h"

BulkParser::BulkParser(std::size_t p_execCommands)
:
execCommands{p_execCommands},
parser{std::make_unique<SimpleParser>(*this)}
{

}

void BulkParser::passInput(const std::string& input)
{
    if (parser)
    {
        parser->parse(input);
    }
}

std::size_t BulkParser::getExecCommands() const noexcept
{
    return execCommands;
}

void BulkParser::setParser(std::unique_ptr<BlockParser> newParser)
{
    parser = std::move(newParser);
}

Bulk& BulkParser::getBulk()
{
    return bulk;
}

void BulkParser::endBulk()
{
    if(bulk.getSize() != 0)
    {
        bulk.exec();
        bulk.clear();
    }
}
