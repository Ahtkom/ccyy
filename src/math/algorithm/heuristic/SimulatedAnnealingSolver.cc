#include <math/algorithm/heuristic/SimulatedAnnealingSolver.h>

namespace ccyy {
namespace math {
namespace alg {

void SimulatedAnnealingSolver::optimize()
{
    allocCurrentSolution();
    allocBestSolution();
    updateCurrentVal();

    while (currTemperature() > 1e-3) {
        for (std::size_t i = 0; i != markovLength(); ++i) {
            if (currVal() > bestVal()) {
                updateBestSolution();
            } else if (leaveCurrentRegion()) {
                updateBestSolution();
            }
            updateCurrentSolution();
        }
        updateTemperature();
        // std::cout << currTemperature() << " " << bestVal() << std::endl;
    }
    // printResult();
}

void SimulatedAnnealingSolver::log()
{
    std::cout << "I'm the log.\n";
}

void SimulatedAnnealingSolver::updateCurrentSolution()
{
    auto nVars = getNumOfVars();
    for (std::size_t i = 0; i != nVars; ++i) {
        *curr_sol_[i] = getRand();
    }
    updateCurrentVal();
}

inline
double SimulatedAnnealingSolver::getRand() const
{
    return rand() % (10000) / (float)(10000);
}

bool SimulatedAnnealingSolver::leaveCurrentRegion() const
{
    return getRand() < exp((currVal() / bestVal() - 1) / currTemperature());
}

inline
void SimulatedAnnealingSolver::updateTemperature()
{
    temperature_ *= attenuation_factor_;
}


} // namespace alg
} // namespace math
} // namespace ccyy