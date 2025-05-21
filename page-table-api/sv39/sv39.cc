#include "sv39.hh"

inline Sv39PageTableBuilder::Addr Sv39PageTableBuilder::NormalizeVPN(Addr vpn) {
  return vpn & ((1ULL << 27) - 1);
}

inline Sv39PageTableBuilder::Addr Sv39PageTableBuilder::NormalizePPN(Addr ppn) {
  return ppn & ((1ULL << 44) - 1);
}

void Sv39PageTableBuilder::SetRootPPN(Addr ppn) {
  ppn = NormalizePPN(ppn);
  Reg satp;
  asm("csrrs %[dest], satp, x0" : [dest] "=r"(satp)); // read satp
  satp |= ppn;
  asm("csrrw x0, satp, %[value]" ::[value] "r"(satp)); // write satp
}

void Sv39PageTableBuilder::FirstLevelPtCnfg(Addr vpn, Addr ppn,
                                            PTE_type pte_type) {
  vpn = NormalizeVPN(vpn);
  ppn = NormalizePPN(ppn);

  Reg satp;
  Addr *first_level_pte;
  asm("csrrs %[dest], satp, x0" : [dest] "=r"(satp)); // read satp
  first_level_pte = (Addr *)(((satp & saptMaskPPN) << 12) + ((vpn >> 18)) << 3);
  *first_level_pte = (ppn << 10) | (0b1111 << 4) | (pte_type << 1) | 0b1;
}

void Sv39PageTableBuilder::SecondLevelPtCnfg(Addr vpn, Addr ppn,
                                             PTE_type pte_type) {
  vpn = NormalizeVPN(vpn);
  ppn = NormalizePPN(ppn);

  Reg satp;
  Addr *first_level_pte;
  Addr *second_level_pte;
  Addr vpn2mask = ((1ULL << 27) - 1) ^ ((1ULL << 9) - 1);
  asm("csrrs %[dest], satp, x0" : [dest] "=r"(satp)); // read satp
  first_level_pte = (Addr *)(((satp & saptMaskPPN) << 12) + ((vpn >> 18)) << 3);
  if (((*first_level_pte >> 1) & 0b111) != NextLevel)
    return;
  second_level_pte =
      (Addr *)((((*first_level_pte) >> 10) << 12) + ((vpn & vpn2mask) << 3));
  *second_level_pte = (ppn << 10) | (0b1111 << 4) | (pte_type << 1) | 0b1;
}

void Sv39PageTableBuilder::ThirdLevelPtCnfg(Addr vpn, Addr ppn,
                                            PTE_type pte_type) {
  vpn = NormalizeVPN(vpn);
  ppn = NormalizePPN(ppn);

  Reg satp;
  Addr *first_level_pte;
  Addr *second_level_pte;
  Addr *third_level_pte;
  Addr vpn1mask = ((1ULL << 27) - 1) ^ ((1ULL << 9) - 1);
  Addr vpn0mask = 0x1ff;
  asm("csrrs %[dest], satp, x0" : [dest] "=r"(satp)); // read satp
  first_level_pte = (Addr *)(((satp & saptMaskPPN) << 12) + ((vpn >> 18)) << 3);
  if (((*first_level_pte >> 1) & 0b111) != NextLevel)
    return;
  second_level_pte = (Addr *)((((*first_level_pte) >> 10) << 12) +
                              (((vpn & vpn1mask) >> 9) << 3));
  if (((*second_level_pte >> 1) & 0b111) != NextLevel)
    return;
  third_level_pte =
      (Addr *)((((*second_level_pte) >> 10) << 12) + ((vpn & vpn0mask) << 3));
  *third_level_pte = (ppn << 10) | (0b1111 << 4) | (pte_type << 1) | 0b1;
}

void Sv39PageTableBuilder::EnableTranslation() {
  Reg satp;
  asm("csrrs %[dest], satp, x0" : [dest] "=r"(satp)); // read satp
  satp |= (0b1000ULL << 60);
  asm("csrrw x0, satp, %[value]" ::[value] "r"(satp)); // write satp
}

void Sv39PageTableBuilder::DisableTranslation() {
  Reg satp;
  asm("csrrs %[dest], satp, x0" : [dest] "=r"(satp)); // read satp
  satp &= ((1ULL << 60) - 1);
  asm("csrrw x0, satp, %[value]" ::[value] "r"(satp)); // write satp
}