#include<new>
#include<type_traits>
#include<utility>

namespace lib{
template<typename T,typename U, typename = void>
struct is_eq_comparable: std::false_type{};

template<typename T, typename U>
struct is_eq_comparable<T,U, std::void_t<decltype(declval<T>() == declval<U>())>>: std::true_type {};

template<typename T,typename U>
inline constexpr  bool is_eq_comparable_v = is_eq_comparable<T,U>::value;



struct nullopt_t{
  explicit  constexpr  nullopt_t(int){}
};

inline constexpr nullopt_t null_opt{0};


template<typename T>
class optional;


template<typename T>
struct is_optional: std::false_type{};


template<typename U>
struct is_optional<optional<U>>: std::true_type{};


template<typename T>
inline constexpr bool is_optional_v = is_optional<T>::value;
}


