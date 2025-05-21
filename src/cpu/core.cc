#include "cpu/core.hh"
#include "cpu/cpu.hh"
#include "cpu/execute.gen.hh"
#include <bitset>
#include <chrono>
#include <iostream>
#include <print>

namespace simlinx {

  void Core::run(Core::reg_t pc) {
    pc_reg = pc;
    regs[2] = 900_KB;
    regs[0] = 0;
    BasicBlock<> *bb;
    Fault fault = Fault::NoFault;

    auto start = std::chrono::high_resolution_clock::now();
    while (true && fault == Fault::NoFault && this->fault == Fault::NoFault) {
      bb = icache.lookup(pc_reg);
      if (!bb)
        bb = icache.createNewBlock(*this);
      fault = bb->execute(*this);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Faults bb: " << (fault != Fault::NoFault) << " core fault: " << (this->fault != Fault::NoFault) << std::endl;

    std::cout << "Hit: " << icache.getHit() << " Miss: " << icache.getMiss()
              << std::endl;
    std::cout << "Execution time: " << duration.count() << " microseconds"
              << std::endl;
    std::cout << "Instructions executed: " << executedI << std::endl;
    std::cout << "MIPS: " << float(executedI) / float(duration.count())
              << std::endl;

    if ((fault != Fault::NoFault || this->fault != Fault::NoFault) &&
        regs[Core::Register::a0])
      exit(regs[Core::Register::a0]);
  }
} // namespace simlinx