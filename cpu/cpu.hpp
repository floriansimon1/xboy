#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>

#include "instructions-table.hpp"

struct Gameboy;
struct Cpu;

typedef uint16_t Cpu::* const CpuRegisterPointer;

struct Cpu {
  InstructionsTable table;

  unsigned long long ticks;

  uint16_t af;
  uint16_t bc;
  uint16_t de;
  uint16_t hl;

  uint16_t pc;
  uint16_t sp;

  static const short zeroFlag      = 7;
  static const short carryFlag     = 4;
  static const short subtractFlag  = 6;
  static const short halfCarryFlag = 5;

  Cpu();

  void reset();

  void process(Gameboy &gameboy);

  void setZeroFlag(bool enable);
  void setCarryFlag(bool enable);
  void setSubtractFlag(bool enable);
  void setHalfCarryFlag(bool enable);
  uint16_t twoBytesRegister(CpuRegisterPointer cpuRegister);
  uint8_t singleByteRegister(CpuRegisterPointer cpuRegister, bool low);
  void setSingleByteRegister(CpuRegisterPointer cpuRegister, bool low, uint8_t value);
};

#endif
