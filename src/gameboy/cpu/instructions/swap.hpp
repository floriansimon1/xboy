#ifndef SWAP_HPP
#define SWAP_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct Swap: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  Swap(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
