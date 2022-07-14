#ifndef CCYY_UTIL_TYPE_HELPER_H_
#define CCYY_UTIL_TYPE_HELPER_H_

#include <type_traits>

namespace ccyy {

// Sign modifications.

// Primary template.
/// Define a member type alias \c type to \c _TType if the boolean constant
/// is true else \c _FType.
template <bool, typename _TType, typename _FType>
struct enable_if_else
{ using type = _TType; };

// Partial specialization.
template <typename _TType, typename _FType>
struct enable_if_else<false, _TType, _FType>
{ using type = _FType; };

// Type relations.

/// is_same
template <typename...>
struct is_same : public std::false_type
{ };

template <typename _T1, typename _T2, typename... _Types>
struct is_same<_T1, _T2, _Types...>
    : public enable_if_else<is_same<_T1, _T2>::value, is_same<_T2, _Types...>,
          std::false_type>::type
{ };

template <typename _T1, typename _T2>
struct is_same<_T1, _T2> : public std::false_type
{ };

template <typename _Tp>
struct is_same<_Tp, _Tp> : public std::true_type
{ };

/// is_same_primitive
template <typename... _Types>
struct is_same_primitive
    : public is_same<typename std::remove_cv<
          typename std::remove_reference<_Types>::type>::type...>
{ };

// Sfinae-friendly common_type implementation:

/// is_callable
// Primary template.
template <typename _Tp, typename = void>
struct is_callable : public std::false_type
{ };

// For function pointer.
template <typename _Ret, typename... _Args>
struct is_callable<_Ret(_Args...)> : public std::true_type
{ };

// For member function pointer.
template <typename _Tp, typename _Ret, typename... _Args>
struct is_callable<_Ret (_Tp::*)(_Args...)> : public std::true_type
{ };

// For reference of member function pointer.
template <typename _Tp, typename _Ret, typename... _Args>
struct is_callable<_Ret (_Tp::*&)(_Args...)> : public std::true_type
{ };

// For class (including its pointer and reference) that provides operator().
template <typename _Tp>
struct is_callable<_Tp,
    std::void_t<typename is_callable<
        decltype(&std::remove_pointer<typename std::remove_reference<
                     _Tp>::type>::type::operator())>::type>>
    : public std::true_type
{ };

/// Use SFINAE to determine if the type \c _Tp has a member named \c MEMBER
#define has_member(MEMBER)                                                     \
  template <typename _Tp, typename = void>                                     \
  struct has_member_##MEMBER : public std::false_type                          \
  { };                                                                         \
  template <typename _Tp>                                                      \
  struct has_member_##MEMBER<_Tp, std::void_t<decltype(_Tp::MEMBER)>>          \
      : public std::true_type                                                  \
  { };

// ? I would prefer to use the below which is not possible since a default
// ? typename parameter can not come after variadic parameters
// template<typename _Tp>
//   struct __has_member_##MEMBER
//   : public enable_if_else<bool_v<decltype(_Tp::##MEMBER)>,
//       std::true_type, std::false_type>::type
//   { };

#if __cplusplus >= 201703L
template <typename _Tp>
inline constexpr bool is_callable_v = is_callable<_Tp>::value;

template <typename... _Types>
inline constexpr bool is_same_v = is_same<_Types...>::value;

template <typename... _Types>
inline constexpr bool is_same_primitive_v = is_same_primitive<_Types...>::value;

template <bool _Cond, typename _TType, typename _FType>
using enable_if_else_t = typename enable_if_else<_Cond, _TType, _FType>::type;
#endif // C++ 17

} // namespace ccyy

#endif // CCYY_UTIL_TYPE_HELPER_H_