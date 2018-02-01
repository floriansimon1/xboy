#ifndef SUBTRACT_MEMORY_BYTE_TO_REGISTER_HPP
#define SUBTRACT_MEMORY_BYTE_TO_REGISTER_HPP

#include "unsigned-registers-subtraction.hpp"
#include "../instruction.hpp"
#include "../cpu.hpp"

struct SubtractMemoryByteToRegister: Instruction {
  const UnsignedRegistersSubtraction subtractionInstruction;

  CpuRegisterPointer pointerRegister;
  bool               carry;

  SubtractMemoryByteToRegister(
    CpuRegisterPointer pointerRegister,
    bool carry
  );

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
