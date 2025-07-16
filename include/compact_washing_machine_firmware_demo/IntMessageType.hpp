#pragma once
#include <cstdint>
#include <cstdlib>

namespace firmware {
namespace details {
  template<std::size_t Bytes> struct IntMessageTypeImpl;
}

template<std::size_t Bytes> using IntMessageType = typename details::IntMessageTypeImpl<Bytes>::type;
}// namespace firmware

template<> struct firmware::details::IntMessageTypeImpl<1>
{
  using type = std::uint8_t;
};

template<> struct firmware::details::IntMessageTypeImpl<2>
{
  using type = std::uint16_t;
};

template<> struct firmware::details::IntMessageTypeImpl<4>
{
  using type = std::uint32_t;
};

template<> struct firmware::details::IntMessageTypeImpl<8>
{
  using type = std::uint64_t;
};

template<> struct firmware::details::IntMessageTypeImpl<0>
{
  using type = IntMessageType<1>;
};

template<> struct firmware::details::IntMessageTypeImpl<3>
{
  using type = IntMessageType<4>;
};

template<> struct firmware::details::IntMessageTypeImpl<5>
{
  using type = IntMessageType<8>;
};

template<> struct firmware::details::IntMessageTypeImpl<6>
{
  using type = IntMessageType<8>;
};

template<> struct firmware::details::IntMessageTypeImpl<7>
{
  using type = IntMessageType<8>;
};