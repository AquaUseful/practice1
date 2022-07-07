#pragma once

#include <concepts>
#include <random>

#include "Singleton.hpp"

template <std::integral T>
class RandomGen : public Singleton<RandomGen<T>> {
  friend class Singleton<RandomGen<T>>;

 public:
  using value_type = T;
  using random_dev_type = std::random_device;
  using random_gen_type = std::mt19937_64;
  using distribution_type = std::uniform_int_distribution<value_type>;

  RandomGen(const RandomGen&) = delete;
  RandomGen(RandomGen&&) = delete;

  auto operator=(const RandomGen&) = delete;
  auto operator=(RandomGen&&) = delete;

  void reseed() { m_random_gen.seed(m_random_dev()); }
  auto generate(const value_type& _min, const value_type& _max) -> value_type {
    distribution_type distrib(_min, _max);
    return distrib(m_random_gen);
  }

 private:
  RandomGen() : m_random_dev(), m_random_gen() { reseed(); };

  virtual ~RandomGen() = default;

  random_dev_type m_random_dev;
  random_gen_type m_random_gen;
};
