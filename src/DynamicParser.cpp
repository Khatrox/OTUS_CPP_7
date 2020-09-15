//
// Created by xMellox on 15-Sep-20.
//

#include "DynamicParser.h"
#include "BulkParser.h"
#include "SimpleParser.h"

DynamicParser::DynamicParser(BulkParser &p_bulkParser)
:
bulkParser{p_bulkParser},
scope_counter{1} // by default 1 case we creates this object when received "{"
{

}


void DynamicParser::parse(const std::string &str)
{
    if(str == "{")
    {
        scope_counter += 1;
    }
    else if(str == "}")
    {
        scope_counter -= 1;
        if(scope_counter == 0)
        {
            bulkParser.endBulk();
            bulkParser.setParser(std::make_unique<SimpleParser>(bulkParser));
        }
    }
    else
    {
        auto& bulk = bulkParser.getBulk();
        bulk.addCmd(str);
    }
}
