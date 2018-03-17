#ifndef POP_WORD_HPP
#define POP_WORD_HPP

#include "../cpu.hpp"
#include "../constant-time-instruction.hpp"

struct PopWord: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  PopWord(CpuRegisterPointer cpuRegister);
};

#endif
