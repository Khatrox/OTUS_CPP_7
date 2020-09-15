//
// Created by xMellox on 15-Sep-20.
//

#ifndef OTUS_CPP_7_WRONGSCOPEEXCEPTION_H
#define OTUS_CPP_7_WRONGSCOPEEXCEPTION_H

#include <stdexcept>
struct WrongScopeException : std::exception
{
    WrongScopeException(const char* p_lit) noexcept
    :
    lit{p_lit}
    {

    }
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override
    {
        return lit;
    }

private:
    const char* lit;
};

#endif //OTUS_CPP_7_WRONGSCOPEEXCEPTION_H
