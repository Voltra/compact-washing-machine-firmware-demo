#pragma once
#include <cstdint>
#include <cstdlib>

namespace utils {
template<std::size_t Bytes> struct IntMessageTypeImpl;
}

template<std::size_t Bytes> using IntMessageType = typename utils::IntMessageTypeImpl<Bytes>::type;

template<> struct utils::IntMessageTypeImpl<1>
{
  using type = std::uint8_t;
};

template<> struct utils::IntMessageTypeImpl<2>
{
  using type = std::uint16_t;
};

template<> struct utils::IntMessageTypeImpl<4>
{
  using type = std::uint32_t;
};

template<> struct utils::IntMessageTypeImpl<8>
{
  using type = std::uint64_t;
};

template<> struct utils::IntMessageTypeImpl<0>
{
  using type = IntMessageType<1>;
};

template<> struct utils::IntMessageTypeImpl<3>
{
  using type = IntMessageType<4>;
};

template<> struct utils::IntMessageTypeImpl<5>
{
  using type = IntMessageType<8>;
};

template<> struct utils::IntMessageTypeImpl<6>
{
  using type = IntMessageType<8>;
};

template<> struct utils::IntMessageTypeImpl<7>
{
  using type = IntMessageType<8>;
};