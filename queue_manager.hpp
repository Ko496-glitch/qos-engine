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
#include "lib::queue.hpp"
#include<chrono>


inline std::uint64_t now()noexcept{
  using clock = std::chrono::steady_clock;
  return std::chrono::duration_cast<std::chrono::seconds>(clock::now().time_since_epoch()).count();

}

#if 0
This will handle following task;

1) slicing from global_space
2) enqueue and dequeue from any given queue;
3) keep track of alive_queue wrt max_queue 
4) construct and deconstruct queue.
5) cal hash for different flows

#endif

namespace lib{
  constexpr std::size_t alive_queue = 1;
  
  template<typename T>
  class Queue_manager{
    private:
      std::size_t next_id = 2; // next_id for queues identification
      std::array<Queue>queues; // for acitve queue_id list
      std::vector<std::size_t>free_slots; // for free free_slots
      std::size_t nxt_slot;
      std::size_t IDLE_MAX_TIME = 5;
    public:
    Queue_manager()noexcept: queues.push_back(Queue(1));

    Queue default_queue()noexcept{
      return this->queues.front();
    }

       
    std::size_t create_queue()noexcept{
      std::size_t index;
      if(!free_slots.empty()){
        index = free_slots.back();
        free_slots.pop_back();
      }else{
        if(nxt_slot == max_queue){
          throw std::runtime_error("No more slots left, packet will be dropped");
        }
        index = next_slot++;
      }
      queues[index].current_use = true;
      ++alive_queue;
      recompute_limits();
      return index;
    }
    
    void clean_up()noexcept{
      auto current_time = now();
      for(int i{0};i<ts;++i){
        if(this->current_use)continue;
        if(queues[i].current_bytes == 0 && current_time - queues[i].last_active >= IDLE_MAX_TIME){
          delete_queue();
        }
      }
    }


    void delete_queue()noexcept{
      this->packet_count = 0;
      this->current_bytes = 0;
      this->current_use = false;
      --alive_queue;
      free_slots.push_back(this-id);
    }
    
    std::size_t Num_queue()noexcept{
      return queues.size();
    }

    void shrink_size(const&package pkg)noexcept{
      if(current_bytes + pkg.pkt.current_bytes >= max_capacity)return;

    }
      
  };

} 
