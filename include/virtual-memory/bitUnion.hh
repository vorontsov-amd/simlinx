
#pragma once
#include <bitset>
#include <concepts>
#include <cstdint>
#include <exception>
#include <iostream>
#include <type_traits>

template <size_t left_border, size_t right_border>
constexpr bool checkBorders() {
  static_assert(left_border >= right_border,
                "Left border must be greater than or equal to the "
                "right border.");
  return true;
}

template <uint64_t left_border, uint64_t right_border, typename storageT>
  requires(checkBorders<sizeof(storageT) * 8 - 1, left_border>() &&
           checkBorders<left_border, right_border>())
class bits {
  inline storageT mask() const {
    storageT mask_left = ((1ULL << (left_border + 1)) - 1);
    storageT mask_right = (right_border > 0) ? ((1ULL << right_border) - 1) : 0;
    return mask_left ^ mask_right;
  }

public:
  template <typename T>
    requires std::unsigned_integral<T>
  bits &operator=(T value) {
    store = (store & ~mask()) | (((storageT)value << right_border) & mask());
    return *this;
  };

  template <typename T>
    requires(std::unsigned_integral<T> &&
             checkBorders<sizeof(T) * 8, left_border - right_border + 1>())
  operator T() const {
    return static_cast<T>((store & mask()) >> right_border);
  }

  friend std::ostream &operator<<(std::ostream &os, const bits &bts) {
    os << std::endl
       << std::bitset<sizeof(bts.store) * 8>(bts.store & bts.mask());
    return os;
  }

public:
  storageT store;
};

#define BitUnion(name)                                                         \
  class name {                                                                 \
  public:                                                                      \
    using storageT = uint64_t;                                                 \
    template <uint64_t left_border, uint64_t right_border = left_border>       \
    using bits = bits<left_border, right_border, storageT>;                    \
                                                                               \
    friend std::ostream &operator<<(std::ostream &os,                          \
                                    const name &this_class) {                  \
      os << std::endl << std::bitset<sizeof(storage) * 8>(this_class.storage); \
      return os;                                                               \
    }                                                                          \
                                                                               \
    union {                                                                    \
      storageT storage = 0;

// clang-format off
#define endBitUnion };};
// clang-format on
