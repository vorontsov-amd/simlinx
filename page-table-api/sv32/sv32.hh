
// FOR RISCV32
// WARNING: DO NOT USE ANY EXTERNAL LIBS
#pragma once
#include "../type.hh"

class Sv32PageTableBuilder {
public:
  using Addr = uint32_t;
  using Reg = uint32_t;

  uint32_t page_offset = 12;
  Addr saptMaskPPN = 0x003fffff;

  void FirstLevelPtCnfg(Addr vpn, Addr ppn, PTE_type pte_type);
  void SecondLevelPtCnfg(Addr vpn, Addr ppn, PTE_type pte_type);
  void ThirdLevelPtCnfg(Addr vpn, Addr ppn, PTE_type pte_type);
  void EnableTranslation();
  void DisableTranslation();
  void SetRootPPN(Addr ppn);

private:
  inline Addr NormalizeVPN(Addr vpn);
  inline Addr NormalizePPN(Addr ppn);
};