#pragma once
#include "cache/basicBlockCache.hh"
#include "cpu/fault.hh"
#include "cpu/instruction.hh"
#include "ram/ram.hh"
#include "cpu/reg.hh"
#include "reg-file/csrRegFile.hh"
#include "virtual-memory/mmu.hh"
#include <array>
#include <cstdint>
#include <iomanip>

namespace simlinx {
  struct Core final {
  public:
    using reg_t = uint64_t;

  public:
    CSR CSRs;
    std::array<reg_t, 16> regs;
    reg_t pc_reg = 0U;
    RAM &mem;
    MMU mmu;
    BasicBlockCache icache;
    Fault fault = Fault::NoFault;
    uint64_t executedI = 0;

  public:
    void run(reg_t pc);
    void decode(uint32_t decodedBits, ISA::BasedInstruction &decodedInstr);
    Core(RAM &ram) : mem(ram), mmu(*this){};
    void dump() const {
      // clang-format off
      for (size_t i = 0; i < regs.size(); i++) {
        std::cout << "Reg" << std::left << std::setw(2) << std::setfill(' ') << i << ": " << 
        std::setw(20) << std::setfill(' ') << regs[i] << 
        std::hex << " | hex: " << std::setw(18) << std::setfill(' ') << regs[i] << 
        std::dec << " | bits: " << std::bitset<64>(regs[i]) <<  std::endl;
      }
      // clang-format on
    }

    enum Register {
      r0,
      r1,
      r2,
      r3,
      r4,
      r5,
      r6,
      r7,
      r8,
      r9,
      r10,
      r11,
      r12,
      r13,
      r14,
      r15
    };

  public:
    template <std::unsigned_integral T> T load_physical(RAM::size_type addr) {
      return mem.load<T>(addr);
    }

    template <std::unsigned_integral T> T load(RAM::size_type addr) {
      auto memory_mode =
          (addr == pc_reg) ? MemoryMode::EXEC : MemoryMode::WRITE;
      auto translated_addr = mmu.translate(addr, memory_mode);
      return load_physical<T>(translated_addr);
    }

    void load_physical(RAM::size_type addr,
                       std::unsigned_integral auto &value) {
      mem.load(addr, value);
    }

    void load(RAM::size_type addr, std::unsigned_integral auto &value) {
      auto memory_mode =
          (addr == pc_reg) ? MemoryMode::EXEC : MemoryMode::WRITE;
      auto translated_addr = mmu.translate(addr, memory_mode);
      load_physical(translated_addr, value);
    }

    void store_physical(RAM::size_type addr,
                        std::unsigned_integral auto value) {
      mem.store(addr, value);
    }

    void store(RAM::size_type addr, std::unsigned_integral auto value) {
      auto translated_addr = mmu.translate(addr, MemoryMode::READ);
      store_physical(translated_addr, value);
    }
  };
} // namespace simlinx

#include "cache/basicBlockCacheImpl.hh"