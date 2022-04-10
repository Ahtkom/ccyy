#ifndef CCYY_UTIL_MACRO_H_
#define CCYY_UTIL_MACRO_H_

#include <math.h>

#define PI 3.1415926535

constexpr double cosd(double x) { return cos(x / 180 * PI); }
constexpr double sind(double x) { return sin(x / 180 * PI); }

/**
 * @brief Macro expansion to a toString class method
 */
#define TO_STRING_METHOD_WITH_OSTREAM(CLASS_NAME)                        \
    friend std::ostream &operator<<(std::ostream &, const CLASS_NAME &); \
    std::string toString() const                                         \
    {                                                                    \
        std::ostringstream s;                                            \
        s << *this;                                                      \
        return s.str();                                                  \
    }

#endif
