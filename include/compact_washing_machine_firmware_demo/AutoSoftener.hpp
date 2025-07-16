#pragma once
#include "utils.hpp"
#include <bitset>
#include <compact_washing_machine_firmware_demo/parser.hpp>
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <mpark/patterns.hpp>
#include <optional>

namespace firmware {
enum class AutoSoftener : bool {
  NO,
  YES,
};
constexpr auto autoSoftenerBits = bitsRequiredForOptions<AutoSoftener>();

template<> struct parser<AutoSoftener>
{
  constexpr static std::optional<AutoSoftener> parse(std::bitset<autoSoftenerBits> bits)
  {
    using namespace mpark::patterns;
    using details::transcodeEnumOption;
    using details::fallbackEnumPattern;
    auto value = bits.to_ulong();

    return match(value)(transcodeEnumOption(AutoSoftener::NO),
      transcodeEnumOption(AutoSoftener::YES),
      fallbackEnumPattern<AutoSoftener>());
  }
};
}// namespace firmware
