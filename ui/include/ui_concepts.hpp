#pragma once

#include <concepts>
#include <iostream>
#include <istream>
#include <string>

template <typename T, typename S>
concept Inputable = requires(T val, S stream) {
  stream >> val;
};

template <typename T>
concept Stringfyible = requires(T a) {
  { std::to_string(a) } -> std::same_as<std::string>;
};
