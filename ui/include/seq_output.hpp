#pragma once

#include <concepts>
#include <numeric>
#include <string>

#include "ui_concepts.hpp"

template <std::forward_iterator T>
requires Stringfyible<typename T::value_type>
auto seqToString(const T &_begin, const T &_end, const std::string &_sep = ", ",
                 const char &_prefix = '[', const char &_suffix = ']')
    -> std::string {
  const auto fold = [&_sep](const std::string &a,
                            const typename T::value_type b) {
    return a + _sep + std::to_string(b);
  };
  std::string result =
      _prefix +
      std::accumulate(std::next(_begin), _end, std::to_string(*_begin), fold) +
      _suffix;
  return std::move(result);
}
