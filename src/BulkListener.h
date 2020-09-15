//
// Created by xMellox on 11-Sep-20.
//

#ifndef OTUS_CPP_7_BULKLISTENER_H
#define OTUS_CPP_7_BULKLISTENER_H

struct BulkListener
{
    virtual ~BulkListener() = default;
    virtual void notifyExecute(const std::string& cmd) = 0;
    virtual void notifyEnd() = 0;
};

#endif //OTUS_CPP_7_BULKLISTENER_H
