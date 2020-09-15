//
// Created by xMellox on 11-Sep-20.
//

#ifndef OTUS_CPP_7_BULKPARSER_H
#define OTUS_CPP_7_BULKCONTROLLER_H

#include "BulkParser.h"
#include "OutputBulk.h"
#include "OutputBulkInFile.h"

struct otus
{
    static void start(char** argv)
    {
        try
        {
            auto N = std::stoul(argv[1]);
            BulkParser bulkParser{N};
            OutputBulk outputBulk{bulkParser.getBulk()};
            OutputBulkInFile outputBulkInFile{bulkParser.getBulk()};

            std::string line;

            while(std::getline(std::cin,line))
            {
                std::cout << line << '\n';
                bulkParser.passInput(line);
            }
        }
        catch(const std::exception& error)
        {
            std::cout << error.what() << '\n';
        }

    }
};


#endif //OTUS_CPP_7_BULKPARSER_H
