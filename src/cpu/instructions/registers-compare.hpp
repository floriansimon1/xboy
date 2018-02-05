#ifndef REGISTERS_COMPARE_HPP
#define REGISTERS_COMPARE_HPP

#include "./immediate-compare.hpp"
#include "../instruction.hpp"
#include "../cpu.hpp"

struct RegistersCompare: Instruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  RegistersCompare(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    const ImmediateCompare compareInstruction;
};

#endif
