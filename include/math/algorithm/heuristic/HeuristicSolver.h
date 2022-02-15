#ifndef CCYY_MATH_ALGORITHM_HEURISTICSOLVER_H_
#define CCYY_MATH_ALGORITHM_HEURISTICSOLVER_H_

#include <math/func/MathFunction.h>
#include <math/algorithm/Solver.h>
#include <iostream>
#include <memory>

namespace ccyy {
namespace math {
namespace alg {

class HeuristicSolver : public Solver
{
public:
    HeuristicSolver(const func::MathFunction &func) :
        Solver(func)
    {}

    ~HeuristicSolver();

    void optimize() override;

    void log() override;
};

} // namespace alg
} // namespace math
} // namespace ccyy

#endif