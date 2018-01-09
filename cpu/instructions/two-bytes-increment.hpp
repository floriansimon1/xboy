#ifndef TWO_BYTES_INCREMENT_HPP
#define TWO_BYTES_INCREMENT_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct TwoBytesIncrement: Instruction {
  CpuRegisterPointer cpuRegister;
  const short sign;

  TwoBytesIncrement(CpuRegisterPointer cpuRegister, short sign);

  void execute(Gameboy &gameboy, const uint8_t *data) override;
  std::string toString() override;
};

#endif

