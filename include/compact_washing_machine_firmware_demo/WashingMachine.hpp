#pragma once
#include <bitset>
#include <compact_washing_machine_firmware_demo/IntMessageType.hpp>
#include <compact_washing_machine_firmware_demo/parser.hpp>
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <cstdlib>
#include <optional>
#include <tuple>
#include <type_traits>
#include <utility>

namespace firmware {
template<class FirstOption, class... Options> struct WashingMachine
{
  static_assert(std::is_enum_v<FirstOption> && (std::is_enum_v<Options> && ...), "Options must be an enum class");

  using options_type = std::tuple<FirstOption, Options...>;
  using parse_result_type = std::tuple<std::optional<FirstOption>, std::optional<Options>...>;

  constexpr static auto optionsCount = std::tuple_size_v<options_type>;
  constexpr static auto bitsRequired =
    firmware::bitsRequiredForOptions<FirstOption>() + (firmware::bitsRequiredForOptions<Options>() + ...);
  constexpr static auto bytesRequired = bytesRequiredFor(bitsRequired);

  using message_type = IntMessageType<bytesRequired>;
  using message_bitset = std::bitset<bytesRequired * bits_per_byte>;

  template<class F> constexpr static void for_each_option_type(const F &func)
  {
    constexpr auto seq = std::index_sequence_for<FirstOption, Options...>();

    for_each(seq, [&]<auto I> { func.template operator()<std::tuple_element_t<I, options_type>, I>(); });
  }

  constexpr static std::optional<options_type> parse(message_type message) { return parse(message_bitset{ message }); }

  constexpr static std::optional<options_type> parse(message_bitset bits)
  {
    parse_result_type parseResults{};

    constexpr auto bitSpan = details::bitSpanFromBitset(bits);
    std::size_t offset = 0;

    for_each_option_type([&]<class OptionsEnum, auto I>() {
      std::size_t length = bitsRequiredForOptions<OptionsEnum>();
      constexpr auto optionBitSpan = bitSpan.subspan(offset, length);
      constexpr auto bitset = details::bitsetFromBitSpan(optionBitSpan);
      std::get<I>(parseResults) = parser<OptionsEnum>::parse(bitset);
      offset += length;
    });


    constexpr auto seq = std::index_sequence_for<FirstOption, Options...>();

    constexpr bool everythingWasParsed = all_of(seq, [&]<auto I> { return std::get<I>(parseResults).has_value(); });

    if (!everythingWasParsed) {
      return std::nullopt;
    }

    options_type result{};

    for_each_option_type([&]<class OptionsEnum, auto I>() {
      std::get<I>(result) = std::get<I>(parseResults).value();
    });

    return result;
  }
};
}// namespace firmware