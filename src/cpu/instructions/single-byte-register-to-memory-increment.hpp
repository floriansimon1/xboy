#ifndef SINGLE_BYTE_REGISTER_TO_MEMORY_INCREMENT_HPP
#define SINGLE_BYTE_REGISTER_TO_MEMORY_INCREMENT_HPP

#include "single-byte-register-to-memory.hpp"

struct SingleByteRegisterToMemoryIncrement: ConstantTimeInstruction {
  SingleByteRegisterToMemory dereferenceInstruction;
  const short                sign;

  SingleByteRegisterToMemoryIncrement(
    CpuRegisterPointer memoryPointer,
    CpuRegisterPointer cpuRegister,
    short sign,
    bool low
  );

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
