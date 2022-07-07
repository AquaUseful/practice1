#pragma once

#include <concepts>
#include <cstddef>
#include <deque>
#include <iterator>
#include <memory>

#include "ContigiousIterator.hpp"
#include "RandomGen.hpp"

template <std::integral T, typename Alloc = std::allocator<T>>
requires std::same_as<T, typename Alloc::value_type>
class Solution {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ContigiousIterator<T>;
  using const_iterator = const ContigiousIterator<T>;
  using difference_type = typename iterator::difference_type;
  using size_type = std::size_t;
  using bounds_type = std::pair<T, T>;

  using allocator_type = Alloc;

  Solution() = delete;
  Solution(const Solution&) = delete;
  Solution(Solution&&) noexcept = default;

  explicit Solution(size_type _size, bounds_type _bounds)
      : m_size(_size), m_bounds(_bounds), m_processed(false) {
    m_initial = m_allocator.allocate(m_size);
    randomize();
    m_result = m_allocator.allocate(m_size);
  }

  auto operator=(const Solution&) = delete;
  auto operator=(Solution&&) noexcept -> Solution& = default;

  virtual ~Solution() {
    std::destroy_n(m_initial, m_size);
    m_allocator.deallocate(m_initial, m_size);

    std::destroy_n(m_result, m_size);
    m_allocator.deallocate(m_result, m_size);
  }

  void randomize() {
    for (size_type i(0); i < m_size; ++i) {
      std::construct_at(m_initial + i,
                        RandomGen<value_type>::instance().generate(
                            m_bounds.first, m_bounds.second));
    }
    m_processed = false;
  }

  void process() {
    m_result[m_size - 1] = m_initial[m_size - 1];
    for (std::ptrdiff_t i(m_size - 2); i >= 0; --i) {
      m_result[i] = m_initial[i] + m_result[i + 1];
    }
    m_processed = true;
  }

  auto initialCBegin() const -> const_iterator {
    return const_iterator(m_initial);
  }
  auto initialCEnd() const -> const_iterator {
    return const_iterator(m_initial + m_size);
  }

  auto resultBegin() -> iterator {
    checkAndProcess();
    return iterator(m_result);
  }
  auto resultEnd() -> iterator {
    checkAndProcess();
    return iterator(m_result + m_size);
  }

 private:
  void checkAndProcess() {
    if (!m_processed) {
      process();
    }
  }

  value_type* m_initial;
  value_type* m_result;
  size_type m_size;
  allocator_type m_allocator;
  bool m_processed;
  bounds_type m_bounds;
};
