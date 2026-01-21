#pragma once
#include<new>
#include<utility>
#include<cassert>
#include<type_trait>
#include "lib::packet.hpp"
#include "lib::egresss_buffer.hpp"
#include "rb_tree.hpp"
#include "lib::policy.hpp"
#include "lib::global_queue.hpp"
#include "lib::queue.hpp"
using u64 = uint64_t;

namespace lib{

  struct schedule_entity{
      u64 weight;
      u64 vruntime;
      u64 run_node;
      u64 sum_exec_runtime
  };

  struct task_struct{
    std::size_t pid;
    std::size_t  
      
  };

  class scheduler{
    

    public:
      
      scheduler() noexcept = default;

      void enqueu_sched(){

      }

      void deque_sched(){
        
      }

      schedule_entity* pick_next(){
        return find_vruntime();
      }

      void update_vruntime()noexcept{


      }

    

      

  };


}




