#ifndef CCYY_UTIL_ILLEGALARGUMENTEXCEPTION_H_
#define CCYY_UTIL_ILLEGALARGUMENTEXCEPTION_H_

#include <util/CCYYException.h>

namespace ccyy {
namespace util {
    
class IllegalArgumentException : public CCYYException
{
public:
    IllegalArgumentException(const std::string &func, const std::string &msg)
        : CCYYException("IllegalArgumentException", func, msg)
    {}

    ~IllegalArgumentException() noexcept override {}
};

    
} // namespace util
} // namespace ccyy


#endif