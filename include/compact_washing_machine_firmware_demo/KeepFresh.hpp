#pragma once
#include "utils.hpp"
#include <bitset>
#include <compact_washing_machine_firmware_demo/parser.hpp>
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <cstdint>
#include <mpark/patterns.hpp>
#include <optional>

namespace firmware {
enum class KeepFresh : bool {
  NO,
  YES,
};
constexpr auto keepFreshBits = bitsRequiredForOptions<KeepFresh>();

template<> struct parser<KeepFresh>
{
  constexpr static std::optional<KeepFresh> parse(std::bitset<keepFreshBits> bits)
  {
    using namespace mpark::patterns;
    using details::transcodeEnumOption;
    using details::fallbackEnumPattern;
    auto value = bits.to_ulong();

    return match(value)(
      transcodeEnumOption(KeepFresh::NO), transcodeEnumOption(KeepFresh::YES), fallbackEnumPattern<KeepFresh>());
  }
};
}// namespace firmware
