#include <compact_washing_machine_firmware_demo/compact_washing_machine_firmware_demo.hpp>

int factorial(int input) noexcept
{
  int result = 1;

  while (input > 0) {
    result *= input;
    --input;
  }

  return result;
}
