#ifndef CCYY_MATH_INDICES_H_
#define CCYY_MATH_INDICES_H_

#include <iostream>

namespace ccyy {
namespace math {

  /**
   * @brief 
   * 
   * @tparam Args 
   * @param args 
   */
  template<typename... Args>
    void print(Args... args) {
      (std::cout << ... << args) << std::endl;
    }
  

  template<std::size_t... Idx>
    struct Indices {

      Indices() : n(sizeof...(Idx)) { }

      // template<std::size_t... I>
      // auto pp() -> decltype(I...) {

      // }

      std::size_t n;


    };

    // Indices<0, 9, 1> idx;
    // 

    // template<std::size_t... _Idx>
    // std::ostream &operator<<(std::ostream &os, const Indices<_Idx...> &idx)
    // {
    //   for (std::size_t i = 0; i != idx.__n; ++i) {
    //     os << i << "  " << idx.operator[](i);
    //   }
    // }

} // namespace math
} // namespace ccyy

#endif