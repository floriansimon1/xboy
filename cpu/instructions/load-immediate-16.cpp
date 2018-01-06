#include "load-immediate-16.hpp"
#include "../../gameboy.hpp"

LoadImmediate16::LoadImmediate16(uint16_t Cpu::*cpuRegister):
  Instruction(12, 2, 2),
  cpuRegister(cpuRegister)
{
}

void LoadImmediate16::execute(Gameboy &gameboy, const uint8_t *data) {
  gameboy.cpu.*cpuRegister = *reinterpret_cast<const uint16_t*>(data);
}

