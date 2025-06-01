#pragma once
#include <cstdlib>
#include <magic_enum/magic_enum.hpp>
#include <type_traits>
#include <utility>

constexpr std::size_t bits_per_byte = 8;

template<class F, class T, T... Ts>
constexpr void for_each([[maybe_unused]] std::integer_sequence<T, Ts...>, const F &func)
{
  (func.template operator()<Ts>(), ...);
}

template<class F, class T, T... Ts>
constexpr bool any_of([[maybe_unused]] std::integer_sequence<T, Ts...>, const F &func)
{
  return (func.template operator()<Ts>() || ...);
}

template<class F, class T, T... Ts>
constexpr bool all_of([[maybe_unused]] std::integer_sequence<T, Ts...>, const F &func)
{
  return (func.template operator()<Ts>() && ...);
}

template<class F, class T, T... Ts> constexpr bool none_of(std::integer_sequence<T, Ts...> seq, const F &func)
{
  return !any_of(seq, func);
}

template<class T> constexpr bool is_unsigned_integral_v = std::is_unsigned_v<T> && std::is_integral_v<T>;

template<class T>
constexpr auto bitsRequiredForOptions(T numberOfOptions)
  requires is_unsigned_integral_v<T>
{
  auto remainder = numberOfOptions % 2;
  auto quotient = numberOfOptions / 2;
  return remainder ? quotient + T{ 1 } : quotient;
}

template<class Enum>
constexpr auto bitsRequiredForOptions()
  requires std::is_enum_v<Enum>
{
  return bitsRequiredForOptions(magic_enum::enum_count<Enum>());
}

template<class T>
constexpr auto bytesRequiredFor(T bits)
  requires is_unsigned_integral_v<T>
{
  auto leftovers = bits % bits_per_byte;
  auto minBytesRequired = bits / bits_per_byte;
  return leftovers ? minBytesRequired + 1 : minBytesRequired;
}