#pragma once
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <cstdint>

enum class RincingRounds : std::uint8_t {
  NONE,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
};

constexpr auto rincingRoundsBits = bitsRequiredForOptions<RincingRounds>();