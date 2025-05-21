#pragma once
#include "cache/fullyAssociative.hh"
#include "cpu/instruction.hh"
#include "cpu/fault.hh"
#include <tuple>
#include <type_traits>

namespace simlinx {
  struct Core;

  using namespace ISA;
  template <uint32_t blockSize = 15>
    requires(blockSize > 0)
  class BasicBlock {
    std::array<BasedInstruction, blockSize> instructions;

  public:
    BasicBlock() = default;
    BasicBlock(Core &core, u_int64_t pc);
    Fault execute(Core &core);
    void dump(u_int32_t) const;
  };

  class BasicBlockCache : public FullyAssociativeCache<BasicBlock<>> {
  public:
    BasicBlock<> *createNewBlock(Core &core); // { insert(BasicBlock<>(core,
                                              // core.pc_reg), core.pc_reg); }
    BasicBlock<> *
    createNewBlock(Core &core,
                   uint64_t pc); // { insert(BasicBlock<>(core, pc), pc); }
  };
} // namespace simlinx