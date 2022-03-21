#ifndef CCYY_UTIL_MACRO_H_
#define CCYY_UTIL_MACRO_H_

#define TO_STRING_METHOD         \
    std::string toString() const \
    {                            \
        std::ostringstream s;    \
        s << *this;              \
        return s.str();          \
    }

#endif