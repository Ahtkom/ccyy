#ifndef CCYY_MATH_ALGORTIHM_SOLVER_H_
#define CCYY_MATH_ALGORTIHM_SOLVER_H_

#include <math/func/MathFunction.h>
#include <math/algorithm/OptimizeState.h>

namespace ccyy {
namespace math {
namespace alg {

class Solver
{
public:
    Solver(const func::MathFunction &func) :
        obj_func_(func),
        state_(OptimizeState::INFEASIBLE)
    {}

    virtual ~Solver() = default;

    virtual void optimize() = 0;

    virtual void log() = 0;

protected:
    void setObjFunc(const func::MathFunction &func) { obj_func_ = func; }

    const func::MathFunction &getObjFunc() const { return obj_func_; }

    std::size_t getNumOfVars() const { return getObjFunc().getNumOfVars(); }

private:
    func::MathFunction obj_func_;

    OptimizeState state_;
};

} // namespace alg
} // namespace math
} // namespace ccyy

#endif 