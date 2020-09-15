//
// Created by xMellox on 11-Sep-20.
//

#ifndef OTUS_CPP_7_OUTPUTBULK_H
#define OTUS_CPP_7_OUTPUTBULK_H

#include <iostream>
#include <string>
#include <list>
#include "BulkListener.h"

struct BulkSubject;

struct OutputBulk : BulkListener
{
    OutputBulk(BulkSubject& bulkSubject, std::ostream& p_output = std::cout);
    void notifyExecute(const std::string& cmd) override;
    void notifyEnd() override;

private:
    std::ostream& output;
    std::list<std::string> cmds;

};


#endif //OTUS_CPP_7_OUTPUTBULK_H
