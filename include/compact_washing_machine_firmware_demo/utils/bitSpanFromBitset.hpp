#pragma once
#include <bitset>
#include <cstdlib>
#include <span>

namespace firmware::details {
template<std::size_t Bits>
using span_for_bitset = std::span<typename std::bitset<Bits>::reference, Bits>;

template<std::size_t Bits> constexpr span_for_bitset<Bits> bitSpanFromBitset(std::bitset<Bits> &bitset)
{
  using bitset_type = std::bitset<Bits>;
  using span_type = span_for_bitset<Bits>;

  struct iterator
  {
    bitset_type &bits;
    std::size_t index = 0;

    constexpr bool operator==(const iterator &rhs)
    {
      return index == rhs.index && std::addressof(bits) == std::addressof(rhs.bits);
    }

    constexpr decltype(auto) operator*() { return bits[index]; }

    constexpr decltype(auto) operator++()
    {
      ++index;
      return *this;
    }
  };

  struct container
  {
    bitset_type &bits;

    auto begin() { return iterator{ bits }; }

    auto end() { return iterator{ bits, bits.size() }; }
  };

  return span_type{ container{ bitset } };
}
}// namespace firmware::details