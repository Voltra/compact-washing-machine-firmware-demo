#pragma once
#include "utils.hpp"
#include <bitset>
#include <compact_washing_machine_firmware_demo/parser.hpp>
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <cstdint>
#include <mpark/patterns.hpp>
#include <optional>


namespace firmware {
enum class RincingRounds : uint8_t {
  NONE,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
};
constexpr auto rincingRoundsBits = bitsRequiredForOptions<RincingRounds>();

template<> struct parser<RincingRounds>
{
  constexpr static std::optional<RincingRounds> parse([[maybe_unused]] std::bitset<rincingRoundsBits> bits)
  {
    using namespace mpark::patterns;
    using details::transcodeEnumOption;
    using details::fallbackEnumPattern;
    auto value = bits.to_ulong();

    return match(value)(transcodeEnumOption(RincingRounds::NONE),
      transcodeEnumOption(RincingRounds::ONE),
      transcodeEnumOption(RincingRounds::TWO),
      transcodeEnumOption(RincingRounds::THREE),
      transcodeEnumOption(RincingRounds::FOUR),
      transcodeEnumOption(RincingRounds::FIVE),
      fallbackEnumPattern<RincingRounds>());
  }
};
}// namespace firmware
