#ifndef UNSIGNED_REGISTERS_SUBTRACTION_HPP
#define UNSIGNED_REGISTERS_SUBTRACTION_HPP

#include "./unsigned-immediate-subtraction.hpp"
#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct UnsignedRegistersSubtraction: ConstantTimeInstruction {
  const bool         low;
  CpuRegisterPointer cpuRegister;

  UnsignedRegistersSubtraction(
    CpuRegisterPointer cpuRegister,
    bool carry,
    bool low
  );

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    UnsignedImmediateSubtraction subtractionInstruction;
};

#endif
