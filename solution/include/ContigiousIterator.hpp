#pragma once

#include <iterator>

template <typename T>
class ContigiousIterator {
 public:
  using iterator_category = std::contiguous_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;

  ContigiousIterator() : m_ptr(nullptr) {}
  explicit ContigiousIterator(value_type* _ptr) : m_ptr(_ptr) {}
  ContigiousIterator(const ContigiousIterator& _it) : m_ptr(_it.m_ptr) {}

  ~ContigiousIterator() = default;

  auto operator*() const -> reference { return *m_ptr; }
  auto operator->() const -> pointer { return m_ptr; }
  auto operator[](difference_type _n) const -> reference {
    return *(*this + _n);
  }

  auto operator++() -> ContigiousIterator& {
    ++m_ptr;
    return *this;
  }
  auto operator--() -> ContigiousIterator& {
    --m_ptr;
    return *this;
  }
  auto operator++(int) const -> ContigiousIterator {
    ContigiousIterator tmp(*this);
    ++(*this);
    return tmp;
  }
  auto operator--(int) const -> ContigiousIterator {
    ContigiousIterator tmp(*this);
    --(*this);
    return tmp;
  }

  auto operator+=(difference_type _rhs) -> ContigiousIterator& {
    m_ptr += _rhs;
    return *this;
  }
  auto operator-=(difference_type _rhs) -> ContigiousIterator& {
    m_ptr -= _rhs;
    return *this;
  }

  auto operator-(const ContigiousIterator& _rhs) const -> difference_type {
    return m_ptr - _rhs.m_ptr;
  }

  auto operator+(difference_type _rhs) const -> ContigiousIterator {
    return ContigiousIterator(m_ptr + _rhs);
  }
  auto operator-(difference_type _rhs) const -> ContigiousIterator {
    return ContigiousIterator(m_ptr - _rhs);
  }
  friend auto operator+(difference_type _lhs, ContigiousIterator _rhs)
      -> ContigiousIterator {
    return _rhs + _lhs;
  }
  friend auto operator-(difference_type _lhs, ContigiousIterator _rhs)
      -> ContigiousIterator {
    return _rhs - _lhs;
  }

  auto operator==(const ContigiousIterator _rhs) const -> bool {
    return m_ptr == _rhs.m_ptr;
  }
  auto operator!=(const ContigiousIterator _rhs) const -> bool {
    return m_ptr != _rhs.m_ptr;
  }
  auto operator>(const ContigiousIterator& _rhs) const -> bool {
    return m_ptr > _rhs.m_ptr;
  }
  auto operator<(const ContigiousIterator& _rhs) const -> bool {
    return m_ptr < _rhs.m_ptr;
  }
  auto operator>=(const ContigiousIterator& _rhs) const -> bool {
    return m_ptr >= _rhs.m_ptr;
  }
  auto operator<=(const ContigiousIterator& _rhs) const -> bool {
    return m_ptr <= _rhs.m_ptr;
  }

 private:
  pointer m_ptr;
};
