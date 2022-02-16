#ifndef CCYY_MATH_ALGORTIHM_SOLVER_H_
#define CCYY_MATH_ALGORTIHM_SOLVER_H_

#include <math/func/MathFunction.h>
#include <math/algorithm/OptimizeState.h>

#include <iostream>

namespace ccyy {
namespace math {
namespace alg {

class Solver
{
public:
    Solver(const func::MathFunction &func) :
        obj_func_(func),
        state_(OptimizeState::INFEASIBLE),
        curr_val_(0.0),
        best_val_(-999999.0),
        curr_sol_(nullptr),
        best_sol_(nullptr)
    {}

    virtual ~Solver();

    virtual void optimize() = 0;

    virtual void log() = 0;

    void setObjFunc(const func::MathFunction &func) { obj_func_ = func; }

    std::size_t getNumOfVars() const { return getObjFunc().getNumOfVars(); }

    const func::MathFunction &getObjFunc() const { return obj_func_; }

    void printResult() const;

protected:
    void allocCurrentSolution();
    void allocBestSolution();

    void destoryCurrentSolution();
    void destoryBestSolution();

    void copy(double **, double **, std::size_t);

    virtual void updateCurrentSolution() = 0;
    void updateCurrentVal();

    void updateBestSolution();
    void updateBestVal();

protected:
    func::MathFunction obj_func_;

    OptimizeState state_;

    double curr_val_;
    double best_val_;
    double **curr_sol_;
    double **best_sol_;
};

} // namespace alg
} // namespace math
} // namespace ccyy

#endif 