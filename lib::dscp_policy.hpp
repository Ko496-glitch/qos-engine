#pragma once
#include "lib::packet.hpp"
#include "global_buffer.hpp"
#include "lib::packet.hpp"


namespace lib{

  enum class dscp_class{
    CS,
    AF,
    EF,
    BE,
    UNKNOWN
  };

  struct dscp_info{
    dscp_class family;
    uint8_t level;


    dscp_info classify(uint8_t dscp)noexcept{
      dscp &= 0x3f;
      if(dscp == 46){
        return{dscp_class::EF, 0};
      }
      else if()
    }
  }
}
