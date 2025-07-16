#pragma once
#include "utils.hpp"
#include <bitset>
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <compact_washing_machine_firmware_demo/utils/bitSpanFromBitset.hpp>
#include <compact_washing_machine_firmware_demo/utils/bitsetFromBitSpan.hpp>
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <ranges>
#include <span>
#include <type_traits>

namespace firmware {
template<class OptionsEnum> struct parser
{
  static_assert(std::is_enum_v<OptionsEnum>, "OptionsEnum must be an enum");

  constexpr static auto bitsRequired = bitsRequiredForOptions<OptionsEnum>();

  using option_bitset = std::bitset<bitsRequired>;

  constexpr static std::optional<OptionsEnum> parse([[maybe_unused]] option_bitset messageBitset)
  {
    return std::nullopt;
  }
};
}// namespace firmware

// TODO: Write specialization in the enum files