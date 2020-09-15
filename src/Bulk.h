//
// Created by xMellox on 11-Sep-20.
//

#ifndef OTUS_CPP_7_BULK_H
#define OTUS_CPP_7_BULK_H

#include "BulkSubject.h"
#include <string>
#include <set>
#include <list>


struct Bulk : BulkSubject
{
    void subscribe(BulkListener& listener) override;
    void unsubscribe(BulkListener& listener) override;

    void addCmd(const std::string& cmd);
    void exec();
    void clear();

    std::size_t getSize() const noexcept;
private:

    void exec(const std::string& cmd);
    void notifyCmdExecuted(const std::string& cmd);
    void notifyBulkEnd();

    std::list<std::string> cmds;
    std::list<BulkListener*> listeners;
};


#endif //OTUS_CPP_7_BULK_H
