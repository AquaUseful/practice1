#pragma once

#include <concepts>
#include <regex>
#include <stdexcept>
#include <string>

class UnparsibleString : public std::invalid_argument {
 public:
  UnparsibleString() : std::invalid_argument("String is not a valid number") {}
};

template <std::integral T>
auto parse(const std::regex& _reg, const std::string& _str) -> T {
  if (std::regex_match(_str, _reg)) {
    return std::move(static_cast<T>(std::stoll(_str)));
  } else {
    throw UnparsibleString();
  }
}

template <std::signed_integral T>
auto parseNumber(const std::string& _str) -> T {
  const std::regex reg("^[-+]?[0-9]+$");
  return parse<T>(reg, _str);
}

template <std::unsigned_integral T>
auto parseNumber(const std::string& _str) -> T {
  const std::regex reg("^\\+?[0-9]+$");
  return parse<T>(reg, _str);
}
