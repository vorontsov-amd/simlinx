#pragma once
#include "cache/basicBlockCache.hh"
#include "cpu/core.hh"
#include "cpu/execute.gen.hh"

namespace simlinx {

  template <uint32_t blockSize>
    requires(blockSize > 0)
  BasicBlock<blockSize>::BasicBlock(Core &core, uint64_t pc) {
    auto basicBlockPC = pc;
    uint32_t instructionsItr = 0;
    BasedInstruction decodingInst;
    // std::cout << "Creating BasicBlock" << std::endl;
    do {
      auto decodedBits = core.mem.load<uint32_t>(basicBlockPC);
      core.decode(decodedBits, decodingInst);
      instructions[instructionsItr] = decodingInst;
      // std::cout << "PC: 0x" << std::hex << basicBlockPC << std::dec
      //           << " Decoding instruction: " << decodingInst.instrId
      //           << " EBB: " << decodingInst.isEBB() << std::endl;
      basicBlockPC += 4;
      instructionsItr++;
    } while (instructionsItr < blockSize - 1 && !decodingInst.isEBB());
    // std::cout << "End of creating BasicBlock" << std::endl;
    decodingInst.instrId = InstrId::EBBC;
    decodingInst.exec = executeEbbc;
    instructions[instructionsItr] = decodingInst;
  }

  template <uint32_t blockSize>
    requires(blockSize > 0)
  Fault BasicBlock<blockSize>::execute(Core &core) {
    auto inst = instructions[0];
    Fault fault = Fault::NoFault;

    if (inst.instrId == InstrId::NONE)
      return Fault::TheEndOfTask;
    auto prev_pc = core.pc_reg;
    instructions[0].exec(core, &instructions[0], &instructions[0]);

    if (core.fault != Fault::NoFault)
      fault = core.fault;
    return fault;
  }

  template <uint32_t blockSize>
    requires(blockSize > 0)
  void BasicBlock<blockSize>::dump(u_int32_t indx) const {
    std::cout << "BasicBlock:" << indx << std::endl;
    for (uint32_t i = 0; i < blockSize; i++) {
      std::cout << "Instruction:" << instructions[i].dumpName()
                << " addr: " << &instructions[i] << std::endl;
    }
    std::cout << "End of BasicBlock" << std::endl;
  }
} // namespace simlinx