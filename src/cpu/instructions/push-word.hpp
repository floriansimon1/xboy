#ifndef PUSH_WORD_HPP
#define PUSH_WORD_HPP

#include "../cpu.hpp"
#include "../constant-time-instruction.hpp"

struct PushWord: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  PushWord(CpuRegisterPointer cpuRegister);
};

#endif
