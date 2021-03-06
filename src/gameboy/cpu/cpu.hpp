#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>

#include "instructions-table.hpp"
#include "../types.hpp"

struct Gameboy;
struct Cpu;

typedef uint16_t Cpu::* const CpuRegisterPointer;

struct Cpu {
  InstructionsTable table;
  Tick              ticks;

  bool interruptsEnabled = true;
  bool inInterrupt       = false;
  bool halted            = false;

  uint16_t af;
  uint16_t bc;
  uint16_t de;
  uint16_t hl;

  uint16_t pc;
  uint16_t sp;

  static const unsigned short zeroFlag      = 7;
  static const unsigned short carryFlag     = 4;
  static const unsigned short subtractFlag  = 6;
  static const unsigned short halfCarryFlag = 5;

  Cpu();

  void reset();

  void unhalt();
  void returnFromFunction(Gameboy &gameboy);
  void call(Gameboy &gameboy, uint16_t address);

  void process(Gameboy &gameboy);

  bool anyFlagSet() const;
  bool getZeroFlag() const;
  bool getCarryFlag() const;
  bool getSubtractFlag() const;
  bool getHalfCarryFlag() const;
  bool onlyFlagSet(unsigned short flag) const;
  bool flagHasValue(unsigned short flag, bool value) const;

  void clearAllFlags();
  void setZeroFlag(bool enable);
  void setCarryFlag(bool enable);
  void setSubtractFlag(bool enable);
  void setHalfCarryFlag(bool enable);

  uint16_t twoBytesRegister(CpuRegisterPointer cpuRegister) const;
  void setTwoBytesRegister(CpuRegisterPointer cpuRegister, uint16_t value);
  uint8_t singleByteRegister(CpuRegisterPointer cpuRegister, bool low) const;
  void setSingleByteRegister(CpuRegisterPointer cpuRegister, bool low, uint8_t value);
};

#endif
