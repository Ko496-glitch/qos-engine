#include<string>
#include<new>
#include<cassert>
#include<utility>
#include<type_traits>


template<typename T, std::size_t N>
struct ingress_port{
  std::string port_name;
  std::uint16_t port_id;
  bool trust_dscp;
  std::uint8_t default_dscp;
  std::uint16_t speed;
};


