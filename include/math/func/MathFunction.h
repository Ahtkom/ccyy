#ifndef CCYY_MATH_FUNC_MATHFUNCTION_H_
#define CCYY_MATH_FUNC_MATHFUNCTION_H_

#include <functional>

namespace ccyy {
namespace math {
namespace func {

class MathFunction
{
public:
    MathFunction() = default;

    template<std::size_t N>
    explicit MathFunction(std::function<double(std::array<double, N>)> func) :
        n_vars_(N),
        func_(nullptr)
    {}

    MathFunction(std::function<double(double **, std::size_t)> func,
                 std::size_t n_vars) :
        n_vars_(n_vars),
        func_(func)
    {}

    ~MathFunction() = default;

    double operator()(double **vars) const { return func_(vars, n_vars_); }

    std::function<double(double **, std::size_t)> getObjFunc() const { return func_; }

    std::size_t getNumOfVars() const { return n_vars_; }

private:
    std::size_t n_vars_;

    std::function<double(double **, std::size_t)> func_;
};

} // namespace func
} // namespace math
} // namespace ccyy

#endif

