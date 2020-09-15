//
// Created by xMellox on 11-Sep-20.
//

#include "Bulk.h"
#include "BulkListener.h"
#include <algorithm>

void Bulk::subscribe(BulkListener& listener)
{
    auto it = std::find(std::begin(listeners),std::end(listeners),&listener);
    if(it == std::end(listeners))
    {
        listeners.push_back(&listener);
    }
}

void Bulk::unsubscribe(BulkListener& listener)
{
    auto it = std::find(std::begin(listeners),std::end(listeners),&listener);
    if(it != std::end(listeners))
    {
        listeners.erase(it);
    }
}

void Bulk::addCmd(const std::string& cmd)
{
    cmds.push_back(cmd);
}

void Bulk::exec()
{
    for(const auto & cmd : cmds)
    {
      exec(cmd);
      notifyCmdExecuted(cmd);
    }
}

void Bulk::clear()
{
    cmds.clear();
    notifyBulkEnd();
}

void Bulk::exec(const std::string &cmd)
{

}

void Bulk::notifyCmdExecuted(const std::string& cmd)
{
    for(const auto i : listeners)
    {
        i->notifyExecute(cmd);
    }
}

void Bulk::notifyBulkEnd()
{
    for(const auto i : listeners)
    {
        i->notifyEnd();
    }
}

std::size_t Bulk::getSize() const noexcept
{
    return cmds.size();
}


