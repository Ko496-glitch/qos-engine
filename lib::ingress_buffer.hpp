#pragma once
#include<new>
#include<utility>
#include<type_traits>
#include "lib::packet.hpp"
#include "lib::egress_buffer.hpp"
#include "lib::ingress_port.hpp"

namespace lib{
  template<typename T, std::size_t Capacity_ = N ,typename Container = std::array(T,Capacity_)>
  class ingress_buffer{
  
  std::size_t tail_;
  std::size_t head_;
  std::size_t size_;
  Container storage_; 
  
    public:
  constexpr ingress_buffer()noexcept : tail_(0), head_(0), size_(0){}
  ~ingress_buffer(){
    while(this->size_ > 0){ 
      storage_[head_]~.T();
      this->head_ = (this->head_ + 1)%Capacity_;
      --this->size_;
    }
  }
  
    constexpr std::size_t size()const noexcept{return this->size_;}
    constexpr std::size_t capacity() const noexcept{return this->Capacity_;}
    constexpr bool empty() const noexcept{return this->size_ == 0;}             
    constexpr bool full() const noexcept{return this->size_ == this->Capacity_;}   

    bool push(package&& ppt){
    if(this->size_ == Capacity_){
      return false;
    }  
    storage_[tail_] = std::move(ppt);
    this->tail_ = (this->tail_ + 1)%Capacity_; 
    ++this->size_;
    return true;
  }

  std::optional<package> pop(){
    if(this->size_ == 0){
      return std::nullopt;
    }
    package ppt = std::move(this->storage_[head_]);
    this->head_ = (this->head_ + 1)%Capacity_;
    --this->size_;
    return ppt;
  }

  void dscp_check(const ingress_port& port, package& ppt){
    if(!port.trust_dscp){
      ppt.meta.internal_dscp = port.default_dscp;
      return;
      }else{
        std::uint8_t top3 = (ppt.pkt.external_dscp >>5)&0b111;
        ppt.meta.internal_dscp =  top3;
      }
    } 
  };
}
