#pragma once
#include "utils.hpp"
#include <bitset>
#include <compact_washing_machine_firmware_demo/parser.hpp>
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <mpark/patterns.hpp>
#include <optional>

namespace firmware {
enum class AutoDetergent : bool {
  NO,
  YES,
};
constexpr auto autoDetergentBits = bitsRequiredForOptions<AutoDetergent>();

template<> struct parser<AutoDetergent>
{
  constexpr static std::optional<AutoDetergent> parse(std::bitset<autoDetergentBits> bits)
  {
    using namespace mpark::patterns;
    using details::transcodeEnumOption;
    using details::fallbackEnumPattern;
    auto value = bits.to_ulong();

    return match(value)(transcodeEnumOption(AutoDetergent::NO),
      transcodeEnumOption(AutoDetergent::YES),
      fallbackEnumPattern<AutoDetergent>());
  }
};
}// namespace firmware
