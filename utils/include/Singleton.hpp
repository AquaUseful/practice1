#pragma once

template <typename T>
class Singleton {
 public:
  Singleton(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  auto operator=(const Singleton&) = delete;
  auto operator=(Singleton&&) = delete;

  static auto instance() -> T& {
    static T instance;
    return instance;
  }

 protected:
  Singleton() = default;
  virtual ~Singleton() = default;
};
