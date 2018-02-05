#ifndef ADD_MEMORY_BYTE_TO_REGISTER_HPP
#define ADD_MEMORY_BYTE_TO_REGISTER_HPP

#include "../constant-time-instruction.hpp"
#include "unsigned-immediate-addition.hpp"
#include "../cpu.hpp"

struct AddMemoryByteToRegister: ConstantTimeInstruction {
  const UnsignedImmediateAddition additionInstruction;
  CpuRegisterPointer              pointerRegister;

  AddMemoryByteToRegister(CpuRegisterPointer pointerRegister, bool carry);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
