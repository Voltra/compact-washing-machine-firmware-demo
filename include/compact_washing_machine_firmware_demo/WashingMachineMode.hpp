#pragma once
#include "utils.hpp"
#include <bitset>
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <cstdint>
#include <mpark/patterns.hpp>
#include <optional>


namespace firmware {
enum class WashingMachineMode : uint8_t {
  SMART_AI,
  ARIEL_COLD_CLEAN,
  ARIEL_FRESH_CLEAN,
  ARIEL_ULTIMATE_CLEAN,
  PET_ACCESSORIES,
  PLUSHIES,
  ANTI_MITES,
  ANTI_ALLERGIES,
  ANTI_SMELL,
  CLEANSING,
  SHOES,
  WHITENING,
  CACHEMIRE,
  DIVING_SUIT,
  SKIING_SUIT,
  COTTON,
  COTTON_20C,
  BED_SPREAD,
  DENIM_JEANS,
  DELICATE,
  DELICATE_COLORS,
  MASK_CLEANSING,
  STAIN_REMOVAL_COLORS,
  TUMBLING,
  WHOOL,
  BED_STUFF,
  LINGERIE,
  SWIMMING_SUITS,
  TABLE_CLOTH,
  DELICATE_TABLE_CLOTH,
  QUICK_TUMBLE_CLEANSING,
  PANTS,
  TOWELS,
  FRESH_MASKS,
  QUICK_15_MINUTES,
  DRAPES,
  RINCE,
  BACKPACK,
  SILK,
  SYNTHETIC,
  CHOCOLATE_STAINS,
  FRUIT_STAINS,
  BLOOD_STAINS,
  WINE_STAINS,
  CARPET,
  TENNIS_TIE_BREAK,
  TECHNICAL_STRETCHY_FABRIC,
  PERFECT_WHITE,
  FLUFFY_VEST,
  TECHNICAL_VEST,
  BRAND_NEW_CLOTHES,
  DARK_CLOTHES,
  ECO_40C_60C,
  REMOVE_ANIMAL_HAIR,
  REMOVE_STAINS,
};
constexpr auto washingMachineModeBits = firmware::bitsRequiredForOptions<WashingMachineMode>();

template<> struct parser<WashingMachineMode>
{
  constexpr static std::optional<WashingMachineMode> parse(std::bitset<washingMachineModeBits> bits)
  {
    using namespace mpark::patterns;
    using details::transcodeEnumOption;
    using details::fallbackEnumPattern;
    auto value = bits.to_ulong();

    return match(value)(transcodeEnumOption(WashingMachineMode::SMART_AI),
      transcodeEnumOption(WashingMachineMode::ARIEL_COLD_CLEAN),
      transcodeEnumOption(WashingMachineMode::ARIEL_FRESH_CLEAN),
      transcodeEnumOption(WashingMachineMode::ARIEL_ULTIMATE_CLEAN),
      transcodeEnumOption(WashingMachineMode::PET_ACCESSORIES),
      transcodeEnumOption(WashingMachineMode::PLUSHIES),
      transcodeEnumOption(WashingMachineMode::ANTI_MITES),
      transcodeEnumOption(WashingMachineMode::ANTI_ALLERGIES),
      transcodeEnumOption(WashingMachineMode::ANTI_SMELL),
      transcodeEnumOption(WashingMachineMode::CLEANSING),
      transcodeEnumOption(WashingMachineMode::SHOES),
      transcodeEnumOption(WashingMachineMode::WHITENING),
      transcodeEnumOption(WashingMachineMode::CACHEMIRE),
      transcodeEnumOption(WashingMachineMode::DIVING_SUIT),
      transcodeEnumOption(WashingMachineMode::SKIING_SUIT),
      transcodeEnumOption(WashingMachineMode::COTTON),
      transcodeEnumOption(WashingMachineMode::COTTON_20C),
      transcodeEnumOption(WashingMachineMode::BED_SPREAD),
      transcodeEnumOption(WashingMachineMode::DENIM_JEANS),
      transcodeEnumOption(WashingMachineMode::DELICATE),
      transcodeEnumOption(WashingMachineMode::DELICATE_COLORS),
      transcodeEnumOption(WashingMachineMode::MASK_CLEANSING),
      transcodeEnumOption(WashingMachineMode::STAIN_REMOVAL_COLORS),
      transcodeEnumOption(WashingMachineMode::TUMBLING),
      transcodeEnumOption(WashingMachineMode::WHOOL),
      transcodeEnumOption(WashingMachineMode::BED_STUFF),
      transcodeEnumOption(WashingMachineMode::LINGERIE),
      transcodeEnumOption(WashingMachineMode::SWIMMING_SUITS),
      transcodeEnumOption(WashingMachineMode::TABLE_CLOTH),
      transcodeEnumOption(WashingMachineMode::DELICATE_TABLE_CLOTH),
      transcodeEnumOption(WashingMachineMode::QUICK_TUMBLE_CLEANSING),
      transcodeEnumOption(WashingMachineMode::PANTS),
      transcodeEnumOption(WashingMachineMode::TOWELS),
      transcodeEnumOption(WashingMachineMode::FRESH_MASKS),
      transcodeEnumOption(WashingMachineMode::QUICK_15_MINUTES),
      transcodeEnumOption(WashingMachineMode::DRAPES),
      transcodeEnumOption(WashingMachineMode::RINCE),
      transcodeEnumOption(WashingMachineMode::BACKPACK),
      transcodeEnumOption(WashingMachineMode::SILK),
      transcodeEnumOption(WashingMachineMode::SYNTHETIC),
      transcodeEnumOption(WashingMachineMode::CHOCOLATE_STAINS),
      transcodeEnumOption(WashingMachineMode::FRUIT_STAINS),
      transcodeEnumOption(WashingMachineMode::BLOOD_STAINS),
      transcodeEnumOption(WashingMachineMode::WINE_STAINS),
      transcodeEnumOption(WashingMachineMode::CARPET),
      transcodeEnumOption(WashingMachineMode::TENNIS_TIE_BREAK),
      transcodeEnumOption(WashingMachineMode::TECHNICAL_STRETCHY_FABRIC),
      transcodeEnumOption(WashingMachineMode::PERFECT_WHITE),
      transcodeEnumOption(WashingMachineMode::FLUFFY_VEST),
      transcodeEnumOption(WashingMachineMode::TECHNICAL_VEST),
      transcodeEnumOption(WashingMachineMode::BRAND_NEW_CLOTHES),
      transcodeEnumOption(WashingMachineMode::DARK_CLOTHES),
      transcodeEnumOption(WashingMachineMode::ECO_40C_60C),
      transcodeEnumOption(WashingMachineMode::REMOVE_ANIMAL_HAIR),
      transcodeEnumOption(WashingMachineMode::REMOVE_STAINS),
      fallbackEnumPattern<WashingMachineMode>());
  }
};
}// namespace firmware
