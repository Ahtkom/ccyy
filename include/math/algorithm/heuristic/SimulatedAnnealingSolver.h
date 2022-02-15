#ifndef CCYY_MATH_ALGORITHM_SIMULATEDANNEALINGSOLVER_H_
#define CCYY_MATH_ALGORITHM_SIMULATEDANNEALINGSOLVER_H_

#include <math/algorithm/Solver.h>

namespace ccyy {
namespace math {
namespace alg {

class SimulatedAnnealingSolver : public Solver
{
public:
    SimulatedAnnealingSolver(const func::MathFunction &func) :
        Solver(func),
        curr_val_(0.0),
        best_val_(-999999.0),
        curr_sol_(nullptr),
        best_sol_(nullptr)
    {}

    ~SimulatedAnnealingSolver();

    void optimize() override;

    void log() override;

private:
    void destroy(double **);

    void alloc(double **);

private:
    double curr_val_;
    double best_val_;
    double **curr_sol_;
    double **best_sol_;
};

} // namespace alg
} // namespace math
} // namespace ccyy


#endif