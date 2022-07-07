#pragma once

#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include <utility>

#include "string_parse.hpp"
#include "ui_concepts.hpp"

template <Inputable<std::istream> T>
auto requestInput(const std::string &_promt, const std::string &_err_msg,
                  std::istream &_istr = std::cin,
                  std::ostream &_ostr = std::cout) -> T {
  T a;
  for (;;) {
    _ostr << _promt << std::flush;
    _istr >> a;
    if (_istr.good()) {
      return std::move(a);
    }
    _ostr << _err_msg << std::endl;
    _istr.clear();
    _istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

template <std::integral T>
auto requestIntegralInput(
    const std::string &_promt, const std::string &_err_msg,
    const std::pair<T, T> &_bounds = {std::numeric_limits<T>::min(),
                                      std::numeric_limits<T>::max()},
    std::istream &_istr = std::cin, std::ostream &_ostr = std::cout) -> T {
  for (;;) {
    const auto user_input = requestInput<std::string>(
        _promt + " (" + std::to_string(_bounds.first) + " - " +
            std::to_string(_bounds.second) + ") ",
        _err_msg, _istr, _ostr);
    try {
      const T num = parseNumber<T>(user_input);
      if ((num >= _bounds.first) && (num <= _bounds.second)) {
        return std::move(num);
      } else {
        _ostr << _err_msg << std::endl;
        _istr.clear();
        _istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    } catch (UnparsibleString) {
      _ostr << _err_msg << std::endl;
      _istr.clear();
      _istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}
