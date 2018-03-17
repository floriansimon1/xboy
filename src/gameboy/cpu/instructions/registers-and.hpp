#ifndef REGISTER_AND_HPP
#define REGISTER_AND_HPP

#include "./immediate-and.hpp"
#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct RegistersAnd: ConstantTimeInstruction {
  const bool         low;
  CpuRegisterPointer cpuRegister;

  RegistersAnd(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    const ImmediateAnd andInstruction;
};

#endif
