#pragma once
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <cstdint>

enum class Temperature {
  ZERO_C,
  TWENTY_C,
  THIRTY_C,
  FOURTY_C,
  FIFTY_C,
  SIXTY_C,
};

constexpr auto temperatureBits = bitsRequiredForOptions<Temperature>();