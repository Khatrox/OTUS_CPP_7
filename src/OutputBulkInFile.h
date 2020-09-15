//
// Created by xMellox on 11-Sep-20.
//

#ifndef OTUS_CPP_7_OUTPUTBULKINFILE_H
#define OTUS_CPP_7_OUTPUTBULKINFILE_H

#include <string>
#include <list>
#include <fstream>
#include "BulkListener.h"

struct BulkSubject;

struct OutputBulkInFile : BulkListener
{
    explicit OutputBulkInFile(BulkSubject& bulkSubject);
    void notifyExecute(const std::string& cmd) override;
    void notifyEnd() override;
    std::string getPathLastFile() const;

private:

    std::ofstream outputBulkFile;
    std::string lastFileName;
    std::list<std::string> cmds;

};


#endif //OTUS_CPP_7_OUTPUTBULKINFILE_H
