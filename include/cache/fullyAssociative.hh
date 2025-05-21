#pragma once
#include "stat/statistic.hh"
#include <array>
#include <cstdint>
#include <iostream>
#include <stack>
#include <unordered_map>

template <typename StorageT, uint64_t Size = 40, typename KeyT = uint64_t,
          uint64_t Alignas = 64>
class FullyAssociativeCache : public Statistic {
private:
  /// MAYBE: alignas(std::hardware_destructive_interference_size)
  alignas(Alignas) std::array<StorageT, Size> alignedArray;

  std::array<KeyT, Size> alignedIndexes;
  std::unordered_map<KeyT, uint64_t> indexes;
  std::stack<uint64_t> freeIndexesStack;
  uint64_t roundRobinInd = 0;

public:
  FullyAssociativeCache() {
    for (int64_t i = Size - 1; i >= 0; i--) {
      freeIndexesStack.push(i);
    }
  }
  //__builtin_prefetch
  void insert(StorageT value, KeyT key) {
    if (!freeIndexesStack.empty()) [[unlikely]] {
      roundRobinInd = freeIndexesStack.top();
      freeIndexesStack.pop();
    } else [[likely]] {
      roundRobinInd = (roundRobinInd + 1) % Size;
      indexes.erase(alignedIndexes[roundRobinInd]);
    }
    alignedArray[roundRobinInd] = value;
    alignedIndexes[roundRobinInd] = key;
    indexes[key] = roundRobinInd;
  }
  StorageT *lookup(KeyT key) {
    if (indexes.find(key) != indexes.end()) {
      hit++;
      return &alignedArray[indexes[key]];
    }
    miss++;
    return nullptr;
  }

  inline StorageT *getLastInserted() { return &alignedArray[roundRobinInd]; }

  void dump() const {
    std::cout << "Dumping cache: \n";
    uint16_t indx = 0;
    for (const auto &[key, val] : indexes) {
      alignedArray[val].dump(indx);
      indx++;
    }
  }
};