#include "cache/basicBlockCache.hh"
#include "cpu/core.hh"

namespace simlinx {
  BasicBlock<> *BasicBlockCache::createNewBlock(Core &core) {
    // std::cout << "created new block" << std::endl;
    insert(BasicBlock<>(core, core.pc_reg), core.pc_reg);
    // dump();
    // std::cout << "--created new block--" << std::endl;
    return getLastInserted();
  }
  BasicBlock<> *BasicBlockCache::createNewBlock(Core &core, uint64_t pc) {
    insert(BasicBlock<>(core, pc), pc);
    return getLastInserted();
  }
} // namespace simlinx