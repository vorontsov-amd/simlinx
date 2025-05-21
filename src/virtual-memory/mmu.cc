
#include "virtual-memory/mmu.hh"
#include "cpu/core.hh"

namespace simlinx {

  MMU::MMU(Core &_core) : core(_core), walker(_core, *this){};

  Addr MMU::translate(Addr va, MemoryMode mode) {
    std::optional<Addr> pa;
    if (core.CSRs[CSRRegister::satp] >> 60 == 8U) {
      // std::cout << "MMU: va memory enabled" << std::endl;
      if (mode == MemoryMode::READ) {
        pa = tlbR.translate(va);
      }
      if (mode == MemoryMode::WRITE) {
        pa = tlbW.translate(va);
      }
      if (mode == MemoryMode::EXEC) {
        pa = tlbX.translate(va);
      }

      if (pa.has_value()) {
        // return pa.value();
      } else {
        // std::cout << "Starting walker" << std::endl;
        Addr walk_pa;
        PageFault fault = walker.walk(va, &walk_pa, mode);
        // std::cout << "=================================" << std::endl;
        assert(fault == PageFault::NoFault);
        pa = walk_pa;
        // return walk_pa;
      }
    } else {
      // std::cout << "MMU: va memory disabled" << std::endl;
      pa = va;
    }

    // std::cout << "MMU: " << std::hex << pa.value() << std::endl;

    return pa.value();
  }
} // namespace simlinx