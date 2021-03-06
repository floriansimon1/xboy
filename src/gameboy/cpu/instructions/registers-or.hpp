#ifndef REGISTER_OR_HPP
#define REGISTER_OR_HPP

#include "./immediate-or.hpp"
#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct RegistersOr: ConstantTimeInstruction {
  const bool         low;
  CpuRegisterPointer cpuRegister;

  RegistersOr(CpuRegisterPointer cpuRegister, bool low, bool exclusive);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    const ImmediateOr orInstruction;
};

#endif
