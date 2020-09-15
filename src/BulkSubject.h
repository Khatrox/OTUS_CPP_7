//
// Created by xMellox on 11-Sep-20.
//

#ifndef OTUS_CPP_7_BULKSUBJECT_H
#define OTUS_CPP_7_BULKSUBJECT_H

struct BulkListener;

struct BulkSubject
{
    virtual ~BulkSubject() = default;
    virtual void subscribe(BulkListener& listener) = 0;
    virtual void unsubscribe(BulkListener& listener) = 0;
};


#endif //OTUS_CPP_7_BULKSUBJECT_H
