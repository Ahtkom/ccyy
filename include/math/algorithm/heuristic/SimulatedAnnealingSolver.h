#ifndef CCYY_MATH_ALGORITHM_SIMULATEDANNEALINGSOLVER_H_
#define CCYY_MATH_ALGORITHM_SIMULATEDANNEALINGSOLVER_H_

#include <math/algorithm/Solver.h>

#include <iostream>
#include <math.h>
#include <time.h>

namespace ccyy {
namespace math {
namespace alg {

class SimulatedAnnealingSolver : public Solver
{
public:
    SimulatedAnnealingSolver(
        const func::MathFunction &func,
        std::size_t markov_length = 10000,
        double initial_temperature = 100,
        double attenuation_factor = 0.99
    ) : Solver(func),
        markov_length_(markov_length),
        temperature_(initial_temperature),
        attenuation_factor_(attenuation_factor)
    {
        srand(time(NULL));
    }

    ~SimulatedAnnealingSolver() = default;

    void optimize() override;

    void log() override;

    double bestVal() const { return best_val_; }
    
protected:
    double getRand() const;
    double currVal() const { return curr_val_; }
    double currTemperature() const { return temperature_; }
    double markovLength() const { return markov_length_; }

    bool leaveCurrentRegion() const;

    void updateCurrentSolution() override;
    void updateTemperature();

private:
    std::size_t markov_length_;

    double temperature_;

    double attenuation_factor_;
};

} // namespace alg
} // namespace math
} // namespace ccyy


#endif