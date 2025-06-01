#pragma once
#include <bitset>
#include <compact_washing_machine_firmware_demo/utils.hpp>
#include <concepts>
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <ranges>
#include <span>
#include <type_traits>

template<class OptionsEnum, class MessageType> struct parse
{
  static_assert(std::is_enum_v<OptionsEnum>, "OptionsEnum must be an enum");
  static_assert(is_unsigned_integral_v<MessageType>, "MessageType must be unsigned integers");

  using message_bitset = std::bitset<bits_per_byte * sizeof(MessageType)>;
  using message_span = std::span<typename message_bitset::reference, message_bitset::count()>;

  constexpr static auto bitsRequired = bitsRequiredForOptions<OptionsEnum>();
  constexpr static auto bytesRequired = bytesRequiredFor(bitsRequired);

  using option_bitset = std::bitset<bitsRequired>;
  using option_span = std::span<typename option_bitset::reference, option_bitset::count()>;
  using option_int_type = IntMessageType<bytesRequired>;

  constexpr static std::size_t firstBitPosition() { return 0; }

  constexpr static std::size_t lastBitPosition() { return 0; }

  constexpr std::optional<OptionsEnum> it([[maybe_unused]] MessageType message) { return it(message_span(message)); }

  constexpr std::optional<OptionsEnum> it(message_bitset messageBitset)
  {
    constexpr option_span subspan = message_span(messageBitset).subspan(firstBitPosition(), lastBitPosition());

    option_bitset bits{};

    // We want to convert a subrange of std::span<std::bitset::reference> into
    // a std::bitset of the exact needed size
    for (auto &&[bit, index] : std::views::all(subspan) | std::views::zip(std::views::iota(0))) {
      bits.set(index, bit);
    }

    return it(bits);
  }

  constexpr std::optional<OptionsEnum> it([[maybe_unused]] option_bitset bits) { return std::nullopt; }
};

// TODO: Write specialization in the enum files