#include <compact_washing_machine_firmware_demo/compact_washing_machine_firmware_demo.hpp>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <magic_enum/magic_enum.hpp>
#include <type_traits>

namespace std {
template <class... Ts>
auto format_as(std::tuple<Ts...> tuple) {
  return fmt::format("{{{}}}", fmt::join(tuple, ", "));
}
}

namespace firmware {
template<class Enum>
auto format_as(Enum value)
  requires std::is_enum_v<Enum>
{
  return std::pair{fmt::underlying(value), magic_enum::enum_name(value)};
}
}// namespace firmware

template<class Enum, auto Index>
void printEnumInfos(auto bitsForOptions)
  requires std::is_enum_v<Enum>
{
  fmt::println(
    "{}: {} needs {} bits to represent its options", Index, magic_enum::enum_type_name<Enum>(), bitsForOptions);
}

int main()
{
  using namespace firmware;

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

  fmt::println("");
  fmt::println("enum: {}", WashingMachineMode::SMART_AI);
  fmt::println("parse: {}", *WM::parse(WM::message_type{0}));
  return 0;
}