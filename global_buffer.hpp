
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
  constexpr std::size_t packet_size = std::size(package);
}
