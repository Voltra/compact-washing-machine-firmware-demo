#pragma once
#include <compact_washing_machine_firmware_demo/utils.hpp>

enum class KeepFresh : bool {
  NO,
  YES,
};

constexpr auto keepFreshBits = bitsRequiredForOptions<KeepFresh>();
