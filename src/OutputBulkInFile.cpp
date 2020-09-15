//
// Created by xMellox on 11-Sep-20.
//

#include <chrono>
#include "OutputBulkInFile.h"
#include "BulkSubject.h"

OutputBulkInFile::OutputBulkInFile(BulkSubject& bulkSubject)
{
    bulkSubject.subscribe(*this);
}

void OutputBulkInFile::notifyExecute(const std::string &cmd)
{
    if(cmds.empty())
    {
        const auto now = std::chrono::system_clock::now().time_since_epoch();
        const auto time = std::chrono::duration_cast<std::chrono::seconds>(now).count();
        std::string file_name = "bulk";
        file_name += std::to_string(time);
        lastFileName = file_name;

        outputBulkFile.open(file_name);
    }

    cmds.push_back(cmd);
}

void OutputBulkInFile::notifyEnd()
{
    for(auto cmd_it = std::begin(cmds); cmd_it != std::end(cmds); ++cmd_it)
    {
        outputBulkFile << *cmd_it;
        if (std::next(cmd_it) != std::end(cmds))
        {
            outputBulkFile << ", ";
        }
        else
        {
            outputBulkFile << '\n';
        }
    }

    cmds.clear();
    outputBulkFile.close();
}

std::string OutputBulkInFile::getPathLastFile() const
{
    return lastFileName;
}

