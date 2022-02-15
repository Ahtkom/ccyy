#include <math/algorithm/heuristic/SimulatedAnnealingSolver.h>

namespace ccyy {
namespace math {
namespace alg {

SimulatedAnnealingSolver::~SimulatedAnnealingSolver()
{
    destroy(curr_sol_);
    destroy(best_sol_);
}

void SimulatedAnnealingSolver::destroy(double **x)
{
    auto nVars = Solver::getNumOfVars();
    if (x != nullptr) {
        for (std::size_t i = 0; i != nVars; ++i) {
            if (x[i] != nullptr) {
                delete x[i];
                x[i] = nullptr;
            }
        }
        delete[] x;
        x = nullptr;
    }
}

void SimulatedAnnealingSolver::alloc(double **x)
{
    auto nVars = Solver::getNumOfVars();
    if (x == nullptr) {
        x = new[Solver::getNumOfVars()] double;
        for (std::size_t i = 0; i != nVars; ++i) {
            if (x[i] == nullptr) {
                x[i] = new double(0.0);
            }
        }
    }
}

void SimulatedAnnealingSolver::optimize()
{
    alloc(curr_sol_);
    alloc(best_sol_);

    while (true) {
        if (curr_val_ > best_val_) {

        } else {
            if (true) {

            }
        }
        best_sol_ = curr
    }
    

}

} // namespace alg
} // namespace math
} // namespace ccyy