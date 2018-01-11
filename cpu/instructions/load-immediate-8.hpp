#ifndef LOAD_IMMEDIATE_8_HPP
#define LOAD_IMMEDIATE_8_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct LoadImmediate8: Instruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  LoadImmediate8(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) override;
  std::string toString() override;
};

#endif
