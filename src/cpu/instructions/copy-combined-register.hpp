#ifndef COPY_COMBINED_REGISTER_HPP
#define COPY_COMBINED_REGISTER_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct CopyCombinedRegister: ConstantTimeInstruction {
  CpuRegisterPointer from;
  CpuRegisterPointer to;

  CopyCombinedRegister(CpuRegisterPointer to, CpuRegisterPointer from);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
