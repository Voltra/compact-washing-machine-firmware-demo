#pragma once
#include <compact_washing_machine_firmware_demo/utils.hpp>

enum class AutoSoftener : bool {
  NO,
  YES,
};

constexpr auto autoSoftenerBits = bitsRequiredForOptions<AutoSoftener>();
