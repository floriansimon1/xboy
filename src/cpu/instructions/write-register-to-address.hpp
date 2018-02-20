#ifndef WRITE_REGISTER_TO_ADDRESS_HPP
#define WRITE_REGISTER_TO_ADDRESS_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct WriteRegisterToAddress: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  WriteRegisterToAddress(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
