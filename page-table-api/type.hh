#pragma once
#define uint32_t unsigned int
#define uint64_t unsigned long long

typedef enum PTE_type : uint64_t {
  NextLevel = 0b000,
  RO = 0b001,
  RW = 0b011,
  XO = 0b100,
  RX = 0b101,
  RWX = 0b111
} PTE_type;