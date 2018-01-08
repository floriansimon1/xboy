#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>

#include "instructions-table.hpp"

struct Gameboy;

struct Cpu {
  InstructionsTable table;

  unsigned long long ticks;

  uint16_t af;
  uint16_t bc;
  uint16_t de;
  uint16_t hl;

  uint16_t pc;
  uint16_t sp;

  void reset();

  Cpu();

  void process(Gameboy &gameboy);
};

typedef uint16_t Cpu::* const CpuRegisterPointer;

#endif

