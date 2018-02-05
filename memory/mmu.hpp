#ifndef MMU_HPP
#define MMU_HPP

#include <cstdint>

struct Cpu;

struct Mmu {
  uint8_t memory[65536];

  void pushTwoBytesToStack(Cpu &cpu, uint16_t value);
  void pushByteToStack(Cpu &cpu, uint8_t value);
  uint16_t popTwoBytesFromStack(Cpu &cpu);
  uint8_t popByteFromStack(Cpu &cpu);

  void reset();
};

#endif
