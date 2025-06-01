#include <compact_washing_machine_firmware_demo/compact_washing_machine_firmware_demo.hpp>
#include <fmt/format.h>
#include <magic_enum/magic_enum.hpp>
#include <type_traits>

template<class Enum, auto Index>
void printEnumInfos(auto bitsForOptions)
  requires std::is_enum_v<Enum>
{
  fmt::println(
    "{}: {} needs {} bits to represent its options", Index, magic_enum::enum_type_name<Enum>(), bitsForOptions);
}

int main()
{
  using WM =
    WashingMachine<WashingMachineMode, RincingRounds, RincingRpms, Temperature, KeepFresh, AutoDetergent, AutoSoftener>;

  WM::for_each_option_type(
    []<class OptionType, auto I> { printEnumInfos<OptionType, I>(bitsRequiredForOptions<OptionType>()); });

  constexpr auto totalBits = WM::bitsRequired;

  constexpr auto totalBytes = WM::bytesRequired;


  fmt::println("");
  fmt::println("total amount of bits required: {}", totalBits);
  fmt::println("thus, {} bytes", totalBytes);
  fmt::println("therefore, the message type will be: {}", typeid(WM::message_type).name());
  return 0;
}