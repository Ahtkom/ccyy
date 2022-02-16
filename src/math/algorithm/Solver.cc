#include <math/algorithm/Solver.h>

namespace ccyy {
namespace math {
namespace alg {

Solver::~Solver()
{
    destoryCurrentSolution();
    destoryBestSolution();
}

void Solver::printResult() const
{
    for (std::size_t i = 0; i != getNumOfVars(); ++i) {
        std::cout << *best_sol_[i] << std::endl;
    }
}

void Solver::allocCurrentSolution()
{
    if (curr_sol_ == nullptr) {
        auto nVars = getNumOfVars();
        curr_sol_ = new double *[nVars];
        for (std::size_t i = 0; i != nVars; ++i) {
            curr_sol_[i] = new double(0.0);
        }
    }
}

void Solver::allocBestSolution()
{
    if (best_sol_ == nullptr) {
        auto nVars = getNumOfVars();
        best_sol_ = new double *[nVars];
        for (std::size_t i = 0; i != nVars; ++i) {
            best_sol_[i] = new double(0.0);
        }
    }
}

void Solver::destoryCurrentSolution()
{
    if (curr_sol_ != nullptr) {
        auto nVars = getNumOfVars();
        for (std::size_t i = 0; i != nVars; ++i) {
            if (curr_sol_[i] != nullptr) {
                delete curr_sol_[i];
                curr_sol_[i] = nullptr;
            }
        }
        delete[] curr_sol_;
        curr_sol_ = nullptr;
    }
}

void Solver::destoryBestSolution()
{
    if (best_sol_ != nullptr) {
        auto nVars = getNumOfVars();
        for (std::size_t i = 0; i != nVars; ++i) {
            if (best_sol_[i] != nullptr) {
                delete best_sol_[i];
                best_sol_[i] = nullptr;
            }
        }
        delete[] best_sol_;
        best_sol_ = nullptr;
    }
}


void Solver::copy(double **ori, double **tar, std::size_t n)
{
    for (std::size_t i = 0; i != n; ++i) {
        *ori[i] = *tar[i];
    }
}

void Solver::updateBestSolution()
{
    copy(best_sol_, curr_sol_, getNumOfVars());
    updateBestVal();
}

void Solver::updateCurrentVal()
{
    curr_val_ = getObjFunc()(curr_sol_);
}

void Solver::updateBestVal()
{
    best_val_ = getObjFunc()(best_sol_);
}

} // namespace alg
} // namespace math
} // namespace ccyy