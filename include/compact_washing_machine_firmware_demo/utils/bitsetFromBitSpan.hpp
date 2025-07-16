#pragma once
#include <bitset>
#include <cstdlib>
#include <ranges>
#include <span>

namespace firmware::details {
template<class T, std::size_t Extent> using bitset_for_span = std::bitset<std::span<T, Extent>::size()>;

template<class T, std::size_t Extent> constexpr auto bitsetFromBitSpan(std::span<T, Extent> span)
{
  using bitset_type = bitset_for_span<T, Extent>;

  bitset_type bits{};

  // We want to convert a subrange of std::span<std::bitset::reference> into
  // a std::bitset of the exact needed size
  for (auto &&[bit, index] : std::views::all(span) | std::views::zip(std::views::iota(0))) { bits.set(index, bit); }

  return bits;
}
}// namespace firmware::details