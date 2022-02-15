#include <ccyy.h>

#include <iostream>


double my_func(double **x, std::size_t n)
{
    double sum = 10;
    for (std::size_t i = 0; i != n; ++i) {
        sum += -(*x[i] - 1) * (*x[i] - 1);
    }
    return sum;
}

using namespace std;
int main(int, char **)
{
    using namespace ccyy;

    math::func::MathFunction f(std::function<double(double **, std::size_t)>(my_func), 10);

    math::alg::HeuristicSolver hSolver();

    return 0;
}
