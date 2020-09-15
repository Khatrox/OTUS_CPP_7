//
// Created by xMellox on 15-Sep-20.
//

#include "SimpleParser.h"
#include "DynamicParser.h"
#include "BulkParser.h"
#include "WrongScopeException.h"

SimpleParser::SimpleParser(BulkParser &p_bulkParser)
:
bulkParser{p_bulkParser}
{

}

bool SimpleParser::isTimeToEndBulk() const noexcept
{
    return bulkParser.getBulk().getSize() == bulkParser.getExecCommands();
}

void SimpleParser::parse(const std::string& str)
{
    if(str == "}")
    {
        throw WrongScopeException("Can't parse dublicate }");
    }

    if(str == "{")
    {
        bulkParser.endBulk();
        bulkParser.setParser(std::make_unique<DynamicParser>(bulkParser));
    }
    else
    {
        auto& bulk = bulkParser.getBulk();
        bulk.addCmd(str);
        if(isTimeToEndBulk())
        {
            bulkParser.endBulk();
        }
    }
}