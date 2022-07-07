#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

#include "Solution.hpp"
#include "seq_output.hpp"
#include "user_input.hpp"

auto main() -> int {
  using value_type = int;

  const auto size =
      requestIntegralInput<typename Solution<value_type>::size_type>(
          "Введите размер массива", "Недопустимый размер!", {1, 1000});
  const auto range_min = requestIntegralInput<value_type>(
      "Введите нижнюю границу диапазона случайных чисел",
      "Недопустимое число!");
  const auto range_max = requestIntegralInput<value_type>(
      "Введите верхнюю границу диапазона случайных чисел",
      "Недопустимое число!",
      {range_min, std::numeric_limits<value_type>::max()});
  Solution<value_type> sol(size, {range_min, range_max});
  std::cout << "Исходный массив: "
            << seqToString(sol.initialCBegin(), sol.initialCEnd()) << '\n';
  std::cout << "Преобразованный массив: "
            << seqToString(sol.resultBegin(), sol.resultEnd()) << '\n';
  return EXIT_SUCCESS;
}
