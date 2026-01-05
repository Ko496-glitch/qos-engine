#pragma once
#include<utility>
#include<new>
#include<type_traits>
#include "lib::type_trait.hpp" // for eq_comparable type trait


template<typename T>
class optional{
  std::aligned_storage_t<sizeof(T), alignof(T)> storage;
    // storage here will be our array for current object slot space.
  bool engaged;// Flag for either we have a value or not;

  T *ptr()noexcept{
    return reinterpret_cast<T*>(storage);
  }

  const T* ptr()const noexcept{
    return reinterpret_cast<const T*>(storage);
  }

  public:

  void clear(){
    if(this->engaged){
      ptr()->~T();
      this->engaged = false;
    }
  }

  optional() noexcept : engaged(false){}//default constructor

  ~optional(){
    clear();
  }


  // Copy Constructor --- ----------------------------------
  template<typename U = T, typename =  std::enable_if_t<std::is_copy_constructible_v<U>>>
  optional(const optional& other) noexcept : engaged(false){
    if(other.engaged){
      new (storage)T(*other.storage);
      this->engaged = true;
    }
  }

  //Move Constructor ----------------------------------------
  template<typename U = T, typename = std::enable_if_t<std::is_move_constructible_v<U>>>
  optional(optional&& other) noexcept : engaged(false){
    if(other.engaged){
      this->engaged = true;
      new(storage)T(std::move(*other.ptr()));
      other.engaged = false;
    }
  }


  // Copy operator= ------------------------------------------------------------------------
  optional operator=(const optional& other)noexcept{
    if(this == &other)return *this;


    if(this->engaged && other.engaged){
      *this->ptr() = *other.ptr();
    }

    else if(!this->engaged && other.engaged){
      new(&storage)T(*other.ptr());
    }

    else if(this->engaged && !other.engaged){
      clear();
    }

    else{
      return *this;
    }
  }

  //Move operator= --------------------------------------------------------------------------
  optional & operator=(optional&& other)noexcept(std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>){

    if(this == &other)return *this;

    if(this->engaged && other.engaged){
      *this->ptr() = std::move(*other.ptr());
      other.clear();
    }

    else if(this->engaged && !other.engaged){
      this->clear();
    }

    else if(!this->engaged && !other.engaged){
      return *this;
    }

    else{
      new(&storage)T(std::move(*other.ptr()));
      this->engaged = true;
      other.clear();
    }
    return *this;
  }



  // Observers -----------------------------------------
  bool has_value()const noexcept{
    return this->engaged;
  }

  explicit operator bool()const noexcept{
    return this->engaged;
  }

  T& operator*()noexcept {
    return *this->ptr();
  }

  const T& operator*() const noexcept {
    return *this->ptr();
  }

  T* operator->() noexcept {
    return this->ptr();
  }

  const T* operator->() const noexcept {
    return this->ptr();
  }



  #if 0
  Modifiers
    1)swap
    2)reset
    3)emplace
  #endif

  void swap(optional&other)noexcept(std::is_nothrow_swappable_v<T> && std::is_nothrow_move_constructible_v<T>) {

    if(this->engaged && other.engaged){
      std::swap(*this->ptr(), *other.ptr());
    }
    else if(this->engaged && !other.engaged){
      new(&other.storage)T(std::move(*this->ptr()));
      other.engaged = true;
      this->clear();
    }
    else if(!this->engaged && other.engaged){
      new(&this->storage)T(std::move(*other.ptr()));
      this->engaged = true;
      other.clear();
    }
  }


  void reset()noexcept (std::is_nothrow_destructible_v<T>){

    if(this->engaged){
      this->clear();
    }
  }

  template<typename... Ts, typename = std::enable_if_t<std::is_constructible_v<T,Ts...>>>
  T& emplace(Ts&&... args) noexcept(std::is_nothrow_constructible_v<T,Ts...>){
    if(this->engaged)this->clear();
    new(&this->storage)T(std::forward<Ts>(args)...);
    this->engaged = true;
    return *this->ptr();
  }



#if 0
Monadic Operations
1)and_then -> calls other function object, return std::optional<T>;
2)transform -> calls other function object, return whatever func  obj returns and wrap it to std::optional<T>;
3)or_else -> calls other function object, return whatever fnc
#endif


//1)
template<typename Callable,typename R = std::invoke_result_t<Callable,T&>,typename = std::enable_if_t<lib::is_optional_v<R>>>

R add_then(Callable&& f)& noexcept(std::is_nothrow_invocable_v<Callable, T&>){

  if(this->engaged){
    return std::invoke(std::forward<Callable>(f),*this->ptr());
  }
  return lib::null_opt;
}

template<typename Callable,typename R = std::invoke_result_t<Callable,T&&>,typename = std::enable_if_t<lib::is_optional_v<R>>>
R add_then(Callable&& f)&& noexcept(std::is_nothrow_invocable_v<Callable, T&&>){
  if(this->engaged){
    return std::invoke(std::forward<Callable>(f),std::move(*this->ptr()));
  }
  return lib::null_opt;
}

template<typename Callable, typename R = std::invoke_result_t<Callable,const T&>, typename = std::enable_if_t<lib::is_optional_v<R>>>
R add_then(Callable&& f)const & noexcept(std::is_nothrow_invocable_v<Callable, const T&>){
  if(this->engaged){
    return std::invoke(std::forward<Callable>(f), *this->ptr());
  }
  return lib::null_opt;
}


template<typename Callable,typename R = std::invoke_result_t<Callable,const T&&>,typename = std::enable_if_t<lib::is_optional_v<R>>>
R add_then(Callable&& f)const && noexcept(std::is_nothrow_invocable_v<Callable,const T&&>){
  if(this->engaged){
    return std::invoke(std::forward<Callable>(f), std::move(*this->ptr()));
  }
  return lib::null_opt;
}

//2) std::transform
template<typename Callable,typename R = std::invoke_result_t<Callable,T&>,typename = std::enable_if_t<!lib::is_optional_v<R>>>
R transform(Callable&& f)& noexcept(std::is_nothrow_invocable_v<Callable,T&>){

  if(this->has_value){
    return std::invoke(std::forward<Callable>(f), *this->ptr());
  }
  return lib::null_opt;
}
  
template<typename Callable,typename R = std::invoke_result_t<Callable,T&&> ,typename = std::enable_if_t<!lib::is_optional_v<R>>>
R transform(Callable&& f)&& noexcept(std::is_nothrow_invocable_v<Callable,T&&>){
  if(this->has_value){
    return std::invoke(std::forward<Callable>(f), std::move(*this->ptr()));
  }
  return lib::null_opt;
}

template<typename Callable,typename R = std::invoke_result_t<Callable,const T&>,typename = std::enable_if_t<!lib::is_optional_v<R>>>
R transform(Callable&& f)const & noexcept(std::is_nothrow_invocable_v<Callable,const T&>){
  if(this->has_value){
    return std::invoke(std::forward<Callable>(f),*this->ptr());
  }
  return lib::null_opt;
}

template<typename Callable,typename R = std::invoke_result_t<Callable,T&&>,typename = std::enable_if_t<!lib::is_optional_v<R>>>
R transform(Callable&& f)const && noexcept(std::is_nothrow_invocable_v<Callable,const T&&>){
  if(this->has_value){
    return std::invoke(std::forward<Callable>(f), std::move(*this->ptr()));
  }
  return lib::null_opt;
}



//3) or_else


template<typename Callable,typename R = std::invoke_result_t<Callable>,typename = std::enable_if_t<lib::is_optional_v<R>>>
R or_else(Callable&& f)& noexcept(std::is_nothrow_invocable_v<Callable>){
  if(this->has_value){
      return *this->ptr();
  }else{
    return std::invoke(std::forward<Callable>(f));
  }
  return lib::null_opt;
}

template<typename Callable,typename R = std::invoke_result_t<Callable>,typename = std::enable_if_t<lib::is_optional_v<R>>>

R or_else(Callable&& f)&& noexcept (std::is_nothrow_invocable_v<Callable>){
  if(this->has_value){
    return *this->ptr();
  }else{
    return std::invoke(std::forward<Callable>(f));
  }
  return lib::null_opt;
}


template<typename Callable,typename R = std::invoke_result_t<Callable>,typename = std::enable_if_t<lib::is_optional_v<R>>>

R or_else(Callable&& f) const & noexcept (std::is_nothrow_invocable_v<Callable>){
  if(this->has_value){
    return *this->ptr();
  }else{
    return std::invoke(std::forward<Callable>(f));
  }
  return lib::null_opt;

}

template<typename Callable,typename R = std::invoke_result_t<Callable>,typename = std::enable_if_t<lib::is_optional_v<R>>>
R or_else(Callable&& f) const && noexcept(std::is_nothrow_invocable_v<Callable>){
  if(this->has_value){
    return *this->ptr;
  }else{
    return std::invoke(std::forward<Callable>(f));
  }
  return lib::null_opt;
}


};


  #if 0
  Non Memeber functios
  operator==         done
  operator!=         done
  operator<          done
  operator<=         done
  operator>          done
  operator>=         done
  #endif

  //1)
  template<typename T,typename U, typename = std::enable_if_t<lib::is_eq_comparable_v<T,U>>>
  bool operator==(const optional<T>&a, const optional<U>&b)noexcept (noexcept(*a.ptr() == *b.ptr())) {

    if(a.engaged && b.engaged){
      return *a.ptr() == *b.ptr();
    }

    else if(!a.engaged && !b.engaged){
      return true;
    }
    return false;
  }


  //2)
  template<typename T, typename U, typename = std::enable_if_t<lib::is_eq_comparable_v<T,U>>>
  bool operator!=(const optional<T>&a, const optional<U>&b)noexcept (noexcept(*a.ptr() != *b.ptr())){
    if(a.engaged && b.engaged){
      return *a.ptr() != *b.ptr();
    }
    else if(!a.engaged && !b.engaged){
      return false;
    }
    return false;
  }

  //3)
  template<typename T,typename U,typename  = std::enable_if_t<lib::is_eq_comparable_v<T,U>>>
  bool operator<=(const optional<T>&a,const optional<U>&b)noexcept (noexcept(*a.ptr() <= *b.ptr())){

    if(a.engaged && b.enaged){
      return *a.ptr() <= *b.ptr();
    }
    else if(!a.engaged && !b.engaged){
      return true;
    }

    else if(a.engaged && !b.engaged){
      return false;
    }
    return true;
  }

  template<typename T, typename U, typename = std::enable_if_t<lib::is_eq_comparable_v<T,U>>>
  bool operator>(const optional<T>&a,const optional<U>&b)noexcept (noexcept(*a.ptr() > *b.ptr())){
    if(a.engaged  && b.engaged){
      return *a.ptr() > *b.ptr();
    }
    else if(!a.engaged && b.engaged){
      return false;
    }
    else if(a.engaged && !b.engaged){
      return true;
    }
    return false;
  }

 template<typename T, typename U, typename = std::enable_if_t<lib::is_eq_comparable_v<T,U>>>
  bool operator>=(const optional<T>&a,const optional<U>&b)noexcept (noexcept(*a.ptr() >= *b.ptr())){
    if(a.engaged  && b.engaged){
      return *a.ptr() >= *b.ptr();
    }
    else if(!a.engaged && b.engaged){
      return false;
    }
    else if(a.engaged && !b.engaged){
      return true;
    }
    return true;
  } 
