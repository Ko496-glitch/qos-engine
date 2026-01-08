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
      std::size_t next_id = 2;
      std::vector<Queue>queues;

    public:
    
    Queue_manager()noexcept: queues.push_back(Queue(1));

    Queue default_queue()noexcept{
      return this->queues.front();
    }

    Queue* create_queue()noexcept{
       
     for(int i{1};i<queues.size();++i){
       if(!queues[i]->current_use)continue;
        
     } 

      Queue temp = new queue(++id);
       queues.push(temp);
       ++alive_queue;

       std::size_t new_limit 
    }

    

    void delete_queue(Queue& q)noexcept{
      std::size_t index = q->id;


    }
    std::size_t Num_queue()noexcept{
      return queues.size();
    }

    void shrink_size(const&package pkg)noexcept{
      if(current_bytes + pkg.pkt.current_bytes >= max_capacity)return;

    }
      
  };

} 
