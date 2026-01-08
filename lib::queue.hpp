#pragma once
#include<new>
#include<utility>
#include<cassert>
#include<type_trait>
#include "lib::packet.hpp"
#include "lib::egresss_buffer.hpp"
#include "lib::rb_tree.hpp"
#include "lib::policy.hpp"

namespace lib{
  constexpr std::size_t max_queue = 10;
  constexpr std::size_t global_capacity = 30 * 1024;
  constexpr std::size_t alive_queue = 1;
  std::size_t packet_size = std::size(lib::packet);

  template<typename T,typename policy_type = lib::wfq ,typename Drop_polciy = lib::Tail_drop>
  class queue{
    std::queue<packet>buffer_queue;
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
      packet temp_packet = buffer_queue.front();
      //buffer_queue.pop_front();

      if(DropPolicy::allowed_deqeueu()){
        return false;
      }
      buffer_queue.pop_front();
      ++this->packet_count;
      this->current_bytes -= packet_size;
      return temp_packet;
    }

    bool empty()const{
      return buffer_queue.size() == 0;
    }
    
  }
}
