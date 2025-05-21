#pragma once
#include "utils/warning.h"
#include <concepts>
#include <cstdint>
#include <span>
#include <vector>

namespace simlinx {

  using byte = uint8_t;
  using word = uint16_t;
  using dword = uint32_t;
  using qword = uint64_t;

  class RAM final {
  public:
    std::vector<uint8_t> raw_ram;

  public:
    using size_type = unsigned long long;

  public:
    constexpr RAM(size_type ram_size) : raw_ram(ram_size) {}

    std::span<uint8_t> get_memory(size_type allocate_size, size_type offset) {
      BAD_IMPLEMENTED("");
      return std::span<uint8_t>(raw_ram).subspan(offset, allocate_size);
    }

    template <std::unsigned_integral T> constexpr T load(size_type addr) {
      T result{};
      load(addr, result);
      return result;
    }

    constexpr void load(size_type addr, std::unsigned_integral auto &value) {
      for (auto i = 0uz; i < sizeof(value); ++i) {
        value |= static_cast<std::decay_t<decltype(value)>>(raw_ram[addr + i])
                 << 8 * i;
      }
    }

    constexpr void store(size_type addr, std::unsigned_integral auto value) {
      for (auto i = 0uz; i < sizeof(value); ++i) {
        raw_ram[addr + i] = 0xFF & value;
        value >>= 8;
      }
    }

    constexpr byte &operator[](size_type addr) { return raw_ram[addr]; }

    constexpr byte operator[](size_type addr) const {
      return const_cast<RAM *>(this)->operator[](addr);
    }
  };
} // namespace simlinx

constexpr auto operator""_KB(unsigned long long size) { return size * 1024; }

constexpr auto operator""_MB(unsigned long long size) {
  return size * 1024 * 1024;
}

constexpr auto operator""_GB(unsigned long long size) {
  return size * 1024 * 1024 * 1024;
}