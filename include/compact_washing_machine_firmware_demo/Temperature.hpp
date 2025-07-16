#pragma once
#include "utils.hpp"
#include <bitset>
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <cstdint>
#include <mpark/patterns.hpp>
#include <optional>

namespace firmware {
enum class Temperature : std::uint8_t {
  ZERO_C,
  TWENTY_C,
  THIRTY_C,
  FOURTY_C,
  FIFTY_C,
  SIXTY_C,
};
constexpr auto temperatureBits = bitsRequiredForOptions<Temperature>();


template<> struct parser<Temperature>
{
  constexpr static std::optional<Temperature> parse(std::bitset<temperatureBits> bits)
  {
    using namespace mpark::patterns;
    using details::transcodeEnumOption;
    using details::fallbackEnumPattern;
    auto value = bits.to_ulong();

    return match(value)(transcodeEnumOption(Temperature::ZERO_C),
      transcodeEnumOption(Temperature::TWENTY_C),
      transcodeEnumOption(Temperature::THIRTY_C),
      transcodeEnumOption(Temperature::FOURTY_C),
      transcodeEnumOption(Temperature::FIFTY_C),
      transcodeEnumOption(Temperature::SIXTY_C),
      fallbackEnumPattern<Temperature>());
  }
};
}// namespace firmware
