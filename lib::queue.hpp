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
  
  template<typename T, typename Drop_polciy = Tail_drop>
  class queue{

    std::queue<package>buffer_queue;
    std::size_t packet_count = 0;
    std::size_t current_bytes = 0;
    
    public:

    bool enqueue(const &pkt, )noexcept{
      if(!DropPolicy::allowed_enqueue()){
        return false;
      }
      buffer_queue.push(pkt);
      ++packet_count;
      this->current_bytes += packet_size;
    }

    bool dequque()noexcept{
      package temp_packet = buffer_queue.front();
      //buffer_queue.pop_front();

      if(!DropPolicy::allowed_deqeueu()){
        return false;
      }
      buffer_queue.pop_front();
      --this->packet_count;
      this->current_bytes -= packet_size;
      return temp_packet;
    }

    bool empty()const{
      return buffer_queue.size() == 0;
    }

    std::size_t size()const{
      return this->buffer_queue.size();
    }

    std::size_t percentage()noexcept{
      std::size_t max_bytes = gloabal_space/alive_queue;

      std::size_t percent_space = this->current_bytes/max_bytes;      
      return percent_space;
    }
    
  }
}
