#pragma once
#include "utils.hpp"
#include <bitset>
#include <compact_washing_machine_firmware_demo/parser.hpp>
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <cstdint>
#include <mpark/patterns.hpp>
#include <optional>

namespace firmware {
enum class RincingRpms : uint8_t {
  ZERO,
  FOUR_HUNDRED,
  SIX_HUNDRED,
  EIGHT_HUNDRED,
  THOUSAND,
  THOUSAND_TWO_HUNDRED,
  THOUSAND_FOUR_HUNDRED,
};
constexpr auto rincingRpmsBits = bitsRequiredForOptions<RincingRpms>();

template<> struct parser<RincingRpms>
{
  constexpr static std::optional<RincingRpms> parse(std::bitset<rincingRpmsBits> bits)
  {
    using namespace mpark::patterns;
    using details::transcodeEnumOption;
    using details::fallbackEnumPattern;
    auto value = bits.to_ulong();

    return match(value)(transcodeEnumOption(RincingRpms::ZERO),
      transcodeEnumOption(RincingRpms::FOUR_HUNDRED),
      transcodeEnumOption(RincingRpms::SIX_HUNDRED),
      transcodeEnumOption(RincingRpms::EIGHT_HUNDRED),
      transcodeEnumOption(RincingRpms::THOUSAND),
      transcodeEnumOption(RincingRpms::THOUSAND_TWO_HUNDRED),
      transcodeEnumOption(RincingRpms::THOUSAND_FOUR_HUNDRED),
      fallbackEnumPattern<RincingRpms>());
  }
};
}// namespace firmware
