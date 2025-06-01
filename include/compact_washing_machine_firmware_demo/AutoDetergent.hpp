#pragma once
#include <compact_washing_machine_firmware_demo/utils.hpp>

enum class AutoDetergent : bool {
  NO,
  YES,
};

constexpr auto autoDetergentBits = bitsRequiredForOptions<AutoDetergent>();
