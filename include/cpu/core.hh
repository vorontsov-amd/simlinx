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
    std::array<reg_t, 32> regs;
    reg_t pc_reg = 0U;
    RAM &mem;
    MMU mmu;
    BasicBlockCache icache;
    Fault fault = Fault::NoFault;
    uint64_t executedI = 0;

  public:
    void run(reg_t pc);
    void decode(uint32_t decodedBits, ISA::BasedInstruction &decodedInstr, X86JitCompiller& gen);
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
      zero = 0,
      ra = 1,
      sp = 2,
      gp = 3,
      tp = 4,
      t0 = 5,
      t1 = 6,
      t2 = 7,
      s0 = 8,
      fp = 8,
      s1 = 9,
      a0 = 10,
      a1 = 11,
      a2 = 12,
      a3 = 13,
      a4 = 14,
      a5 = 15,
      a6 = 16,
      a7 = 17,
      s2 = 18,
      s3 = 19,
      s4 = 20,
      s5 = 21,
      s6 = 22,
      s7 = 23,
      s8 = 24,
      s9 = 25,
      s10 = 26,
      s11 = 27,
      t3 = 28,
      t4 = 29,
      t5 = 30,
      t6 = 31
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