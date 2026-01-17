#pragma once
#include<new>
#include<utility>
#include<cassert>
#include<type_trait>
#include "lib::packet.hpp"
#include "lib::egresss_buffer.hpp"
#include "lib::rb_tree.hpp"
#include "lib::policy.hpp"
#include "lib::global_queue.hpp"

namespace lib{
  
  template<typename Drop_policy = Tail_drop>
  class Queue{
    private:
    std::queue<package>buffer_queue;
    std::size_t id;
    std::size_t packet_count = 0;
    std::size_t current_bytes = 0;
    std::size_t last_active{};
    std::size_t bytes_limit = 0;
    bool current_use = false;


    public:

    Queue(std::size_t int_)noexcept: id{id_}{};

    std::size_t get_id()noexcept{
      return this->id;
    }
    
    bool use()noexcept{
      return this->current_use;
    }

    
    bool empty()const{
      return buffer_queue.size() == 0;
    }

    void set_limit(std::size_t new_limit){this->queue.max_bytes = new_limit;}

    bool enqueue(const &pkt, )noexcept{
      if(!DropPolicy::allowed_enqueue()){
        return false;
      }
      buffer_queue.push(pkt);
      ++packet_count;
      this->current_bytes += pkg.pkt.byte_size;
      this->last_active = lib::auto();
      return true;
    }

    bool dequque()noexcept{
      package pkg = buffer_queue.front();
      buffer_queue.pop;
      --this->packet_count;    
      this->current_bytes -= pkg.pkt.byte_size;
      if(this->empty()){
        this->last_active = lib::auto();
      }
      return true;
    }


    std::size_t queue_size()const{
      return this->buffer_queue.size();
    }

    std::size_t percentage()noexcept{
      std::size_t max_bytes = gloabal_space/alive_queue;

      std::size_t percent_space = this->current_bytes/max_bytes;      
      return percent_space;
    }

    void reset()noexcept{
      this->packet_count = 0;
      this->current_bytes = 0;
      this->current_use = false;
      this->last_active = 0;
    }
    
  }
}
