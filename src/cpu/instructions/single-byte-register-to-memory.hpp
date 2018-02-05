#ifndef SINGLE_BYTE_REGISTER_TO_MEMORY_HPP
#define SINGLE_BYTE_REGISTER_TO_MEMORY_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct SingleByteRegisterToMemory: ConstantTimeInstruction {
  CpuRegisterPointer memoryPointer;
  CpuRegisterPointer cpuRegister;
  const bool         low;

  SingleByteRegisterToMemory(CpuRegisterPointer memoryPointer, CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
