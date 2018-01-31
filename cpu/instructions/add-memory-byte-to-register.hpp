#ifndef ADD_MEMORY_BYTE_TO_REGISTER_HPP
#define ADD_MEMORY_BYTE_TO_REGISTER_HPP

#include "unsigned-registers-addition.hpp"
#include "../instruction.hpp"
#include "../cpu.hpp"

struct AddMemoryByteToRegister: Instruction {
  const UnsignedRegistersAddition additionInstruction;

  CpuRegisterPointer pointerRegister;
  CpuRegisterPointer targetRegister;
  bool               low;

  AddMemoryByteToRegister(
    CpuRegisterPointer pointerRegister,
    CpuRegisterPointer targetRegister,
    bool low
  );

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif