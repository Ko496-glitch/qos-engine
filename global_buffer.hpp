
#pragma once
#include<new>
#include<utility>
#include<cassert>
#include<type_trait>
#include "lib::packet.hpp"
#include "lib::egresss_buffer.hpp"
#include "lib::rb_tree.hpp"
#include "lib::policy.hpp"
#include<chrono>

namespace lib{
  constexpr std::size_t max_queue = 10;
  constexpr std::size_t global_capacity = 30 * 1024;
  constexpr std::size_t packet_size = std::size(package);
  constexpr std::size_t IDLE_TIME_MAX = 5;

  inline std::uint64_t now()noexcept{
    using clock = std::chrono::steady_clock;
    return std::chrono::duration_cast<std::chrono::seconds>(clock::now().time_since_epoch()).count();
  }

}
