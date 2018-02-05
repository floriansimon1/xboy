#ifndef SINGLE_BYTE_REGISTER_TO_MEMORY_HPP
#define SINGLE_BYTE_REGISTER_TO_MEMORY_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct SingleByteRegisterToMemory: Instruction {
  CpuRegisterPointer memoryPointer;
  CpuRegisterPointer cpuRegister;
  const bool         low;

  SingleByteRegisterToMemory(CpuRegisterPointer memoryPointer, CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
