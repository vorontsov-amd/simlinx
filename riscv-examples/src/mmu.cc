#include "../../page-table-api/sv39/sv39.hh"

void InitMMU() {
  Sv39PageTableBuilder builder;
  builder.SetRootPPN(0x0);
  builder.FirstLevelPtCnfg(0x10, 0x1, NextLevel);
  builder.SecondLevelPtCnfg(0x10, 0x2, NextLevel);
  builder.ThirdLevelPtCnfg(0x10, 0x10, XO);
  builder.ThirdLevelPtCnfg(0xe1, 0xe1, RW);
  builder.ThirdLevelPtCnfg(0xe0, 0xe0, RW);
  builder.ThirdLevelPtCnfg(0xa0, 0xa0, RW);
  builder.ThirdLevelPtCnfg(0xb0, 0xa0, RW);
  builder.EnableTranslation();
}

int main() {
  InitMMU();
  
  
  int* p1 = (int*)0xa0001;
  int* p2 = (int*)0xb0001;
  
  *p1 = 0;
  *p2 = 1;
  
  if (*p1 != *p2) {
     while (1)
     {
        /* code */
     }
     
  }
  return 0;
}

