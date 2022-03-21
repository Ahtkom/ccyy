#ifndef CCYY_UTIL_CCYYEXCEPTION_H_
#define CCYY_UTIL_CCYYEXCEPTION_H_

#include <stdexcept>
#include <string>

namespace ccyy {
namespace util {
    
class CCYYException : public std::runtime_error
{
public:
    CCYYException()
        :
        std::runtime_error("Unkown error")
    {}

    CCYYException(std::string const &msg)
        :
        std::runtime_error(msg)
    {}

    CCYYException(std::string const &name, std::string const &msg)
        :
        std::runtime_error(name + ": " + msg)
    {}

    ~CCYYException() = default;
};


} // namespace util
} // namespace ccyy


#endif