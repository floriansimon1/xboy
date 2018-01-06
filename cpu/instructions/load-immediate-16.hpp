#ifndef LOAD_IMMEDIATE_16_HPP
#define LOAD_IMMEDIATE_16_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct LoadImmediate16: Instruction {
  uint16_t Cpu::* const cpuRegister;

  LoadImmediate16(uint16_t Cpu::*cpuRegister);

  void execute(Gameboy &gameboy, const uint8_t *data) override;
};

#endif

