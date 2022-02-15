#ifndef CCYY_MATH_ALGORITHM_OPTIMIZESTATE_H_
#define CCYY_MATH_ALGORITHM_OPTIMIZESTATE_H_

namespace ccyy {
namespace math {
namespace alg {

enum class OptimizeState
{
    ERROR = -2,
    INFEASIBLE,
    FEASIBLE,
    OPTIMAL
};

} // namespace alg
} // namespace math
} // namespace ccyy

#endif