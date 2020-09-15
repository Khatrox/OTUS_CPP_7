//
// Created by xMellox on 11-Sep-20.
//

#include <iostream>
#include "OutputBulk.h"
#include "BulkSubject.h"

OutputBulk::OutputBulk(BulkSubject& bulkSubject, std::ostream& p_output)
:
output{p_output}
{
    bulkSubject.subscribe(*this);
}

void OutputBulk::notifyExecute(const std::string &cmd)
{
    cmds.push_back(cmd);
}

void OutputBulk::notifyEnd()
{
    if(!cmds.empty())
    {
        output << "bulk: ";
        for (auto cmd_it = std::begin(cmds); cmd_it != std::end(cmds); ++cmd_it)
        {
            output << *cmd_it;
            if (std::next(cmd_it) != std::end(cmds))
            {
                output << ", ";
            }
            else
            {
                output << '\n';
            }
        }
    }

    cmds.clear();
}
