#pragma once
#include <mpark/patterns.hpp>
#include <type_traits>

namespace firmware::details {
template<class Enum> decltype(auto) enumOptionPattern(Enum value)
{
  static_assert(std::is_enum_v<Enum>, "OptionsEnum must be an enum");
  return mpark::patterns::pattern(std::to_underlying(value));
}

template<class Enum> decltype(auto) transcodeEnumOption(Enum value)
{
  return enumOptionPattern(value) = [=] { return std::optional<Enum>{ value }; };
}

template<class Enum> decltype(auto) fallbackEnumPattern()
{
  return mpark::patterns::pattern(mpark::patterns::_) = [] { return std::optional<Enum>{ std::nullopt }; };
}
}// namespace firmware::details