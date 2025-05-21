
#pragma once
#include "cache/fullyAssociative.hh"
#include <cstdint>
#include <optional>

using Addr = uint64_t;

struct TLBEntry {
  Addr vpn;
  Addr ppn;
};

class TLB : public FullyAssociativeCache<TLBEntry> {
  Addr constexpr offsetMask() const { return ((1U << 12) - 1); }

public:
  std::optional<Addr> translate(Addr va) {
    TLBEntry *entry = lookup(va & ~offsetMask());
    if (entry) {
      return entry->ppn | (va & offsetMask());
    }
    return {};
  }

  void insert(Addr va, Addr pa) {
    TLBEntry entry{va & ~offsetMask(), pa & ~offsetMask()};
    FullyAssociativeCache::insert(entry, va & ~offsetMask());
  }
};