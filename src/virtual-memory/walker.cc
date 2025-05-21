#include "virtual-memory/walker.hh"
#include "cpu/core.hh"
#include "virtual-memory/mmu.hh"

namespace simlinx {
  PageWalker::PageWalker(Core &_core, MMU &_mmu)
      : core(_core), mmu(_mmu),
        rootAddr((_core.CSRs[CSRRegister::satp] & ((1ULL << 44) - 1)) *
                 pageSize){};

  PageFault PageWalker::walk(Addr va, Addr *pa, MemoryMode mode) {
    uint64_t a = rootAddr;
    int i = levels - 1;
    uint64_t PTEAddr;
    uint64_t shift;
    uint64_t pte;

    std::cout << "Page walker: translating va " << std::hex << va << " "
              << std::bitset<64>(va) << std::endl;

    while (1) {
      switch (i) {
      case (2):
        shift = 30;
        break;
      case (1):
        shift = 21;
        break;
      case (0):
        shift = 12;
        break;
      }
      std::cout << "level: " << i << std::endl;
      std::cout << "Prev PTEAddr: " << std::hex << a << " "
                << std::bitset<64>(a) << std::endl
                << "gap in block " << std::hex
                << ((va >> shift) & ((1U << 9) - 1)) << " "
                << std::bitset<64>(((va >> shift) & ((1U << 9) - 1)))
                << std::endl
                << "PTEAddr " << std::hex
                << a + ((va >> shift) & ((1U << 9) - 1)) * PTESize << " "
                << std::bitset<64>(a +
                                   ((va >> shift) & ((1U << 9) - 1)) * PTESize)
                << std::endl;

      PTEAddr = a + ((va >> shift) & ((1U << 9) - 1)) * PTESize;
      pte = core.load_physical<uint64_t>(PTEAddr);

      std::cout << "pte " << std::hex << pte << " " << std::bitset<64>(pte)
                << std::endl
                << "(pte >> 10) " << std::hex << (pte >> 10) << " "
                << std::bitset<64>((pte >> 10)) << std::endl
                << "(pte >> 10) * pageSize" << std::hex
                << (pte >> 10) * pageSize << " "
                << std::bitset<64>((pte >> 10) * pageSize) << std::endl;

      if ((pte & vbit) == 0) {
        std::cout << "PageFault::InvalidPage" << std::endl;
        return PageFault::InvalidPage;
      }

      if (((pte & rbit) == 0) && ((pte & wbit) == wbit)) {
        std::cout << "PageFault::WButNotR" << std::endl;
        return PageFault::WButNotR;
      }

      if (((pte & rbit) == rbit) || ((pte & xbit) == xbit)) {
        break;
      }

      i = i - 1;
      if (i < 0) {
        std::cout << "PageFault::ILessThenZero" << std::endl;
        return PageFault::ILessThenZero;
      }

      a = (pte >> 10) * pageSize;
      std::cout << "a: " << std::hex << a << std::endl;
      std::cout << "---------------------------------" << std::endl;
    }

    if ((mode == MemoryMode::READ && (pte & rbit) == 0) ||
        (mode == MemoryMode::WRITE && (pte & wbit) == 0) ||
        (mode == MemoryMode::EXEC && (pte & xbit) == 0)) {
      std::cout << "PageFault::AccessType" << std::endl;
      return PageFault::AccessType;
    }

    // if((i > 0) && (((pte >> 10) & 0x3ff) != 0))
    // return PageFault::SuperPage;

    if ((pte & abit) == 0)
      return PageFault::AccessBit;

    if ((mode == MemoryMode::WRITE) && ((pte & dbit) == 0))
      return PageFault::DirtyBit;

    std::cout << "pte: " << std::hex << pte << std::endl;
    *pa = ((pte << 2) & ~((1U << 12) - 1)) | (va & ((1U << 12) - 1));
    // if(i > 0)
    // {
    // 	pa |= va & 0x3ff000;
    // 	pa |= (uint64_t)(pte & 0xfff00000) << 2;
    // }
    // else
    // 	pa |= (uint64_t)(pte & 0xfffffc00) << 2;
    if ((pte & rbit) == rbit)
      mmu.tlbR.insert(va, *pa);
    if ((pte & wbit) == wbit)
      mmu.tlbW.insert(va, *pa);
    if ((pte & xbit) == xbit)
      mmu.tlbX.insert(va, *pa);

    std::cout << "Walker:: Translated va:" << std::hex << va << " to pa:" << *pa
              << std::endl;
    return PageFault::NoFault;
  }

} // namespace simlinx