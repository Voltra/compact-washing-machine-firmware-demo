#pragma once
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <cstdint>

enum class RincingRpms : std::uint8_t {
  ZERO,
  FOUR_HUNDRED,
  SIX_HUNDRED,
  EIGHT_HUNDRED,
  THOUSAND,
  THOUSAND_TWO_HUNDRED,
  THOUSAND_FOUR_HUNDRED,
};

constexpr auto rincingRpmsBits = bitsRequiredForOptions<RincingRpms>();