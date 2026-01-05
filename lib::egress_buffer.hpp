#pragma once
#include<new>
#include<type_traits>
#include<vector>
#include<utility>
#include<cassert>
#include "lib::type_trait.hpp"

namespace lib{
  template<typename T,std::size_t capacity_ = 1026,typename Policy = no_overflow,  typename Container = std::array<T,capacity_>>
    class egress_buffer{
    private:
      std::size_t head_; // pointer index to index that will be removed
      std::size_t tail_; // pointer index to free slot
      std::size_t size_; // current size of the array we will use
      Container storage_; // default is set to std::array
    

    
    public:
      constexpr egress_buffer()noexcept : head_(0),tail_(0),size_(0){}
      
void clear(){
        if(this->size_ != 0){
          ptr().~T();
        }
      }

      ~egress_buffer(){
        this->clear();
      }

      constexpr std::size_t size()const noexcept{return this->size_;}
      constexpr std::size_t capacity() const noexcept{return this->capacity_;}
      constexpr bool empty() const noexcept{return this->size_ == 0;}
      constexpr bool full() const noexcept{return this->size_ == this->capacity_;}
      
      
      /* 0 <= size <= capacity
       * tail_ = (head_ + size_) % capacityi_;  
       */
      
      bool push(T&& value) {
        if(this->size_ == this->capacity_){
          return false;
        }
        storage_[tail_] = std::move(value);
        this->tail_ = (tail_+1)%capacity_;
        this->size_++;
        return true;
      }

      bool pop(T& out) {
        if(this->size_ == 0){
          return false;
        }
        out = std::move(storage_[head_]);
        this->head_ = (head_+ 1)%capacity_;
        --this->size_;
        return true;
      }
  

  };

  struct no_overflow(){};
  struct tail_drop(){};
  struct overwrite(){};
  
  

};
