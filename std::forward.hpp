#include<iostream>
#include<utility>
#include<type_traits>
#include<cassert>


#if 0
This is the implementation of std::forward<T>(std::size_t value); We write two overalods one for lvalue another rvalue
#endif

//std::forwar(l-value) ---------------------------------------------------
template<typename T>
constexpr T&& my_forward(std::remove_reference_t<T>& x)noexcept{
  return static_cast<T&&>(x);
}


//std::forward(r-value) ---------------------------------------------------
template<typename T>
constexpr T&& my_forward(std::remove_reference_t<T>&&x)noexcept{
  static_assert(!std::is_lvalue_reference_v<T>,"lvalue reference to rvalue");
  return static_cast<T&&>(x);
}

#if 0
//This is the implementation of std::move(r-value/l-value). We will only need on overload because we dont have to preserve anything just change every call to a r-value object and we will be fine :)
#endif

// std::move(l-value/r-value);
// 
template<typename T>
constexpr std::remove_reference_t<T>&& my_move(T&& value)noexcept{
  return static_cast<std::remove_reference_t<T>&&>(value);
}
