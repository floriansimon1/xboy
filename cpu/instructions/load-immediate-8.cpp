#include <sstream>

#include "../../debug/register-string.hpp"
#include "load-immediate-8.hpp"
#include "../../gameboy.hpp"

LoadImmediate8::LoadImmediate8(CpuRegisterPointer cpuRegister, bool low):
  Instruction(8, 1, 1),
  cpuRegister(cpuRegister),
  low(low)
{
}

void LoadImmediate8::execute(Gameboy &gameboy, const uint8_t *data) {
  gameboy.cpu.setSingleByteRegister(cpuRegister, low, *data);
}

std::string LoadImmediate8::toString() {
  std::ostringstream result;

  result << "LD " << registerString(cpuRegister, true, low) << ", d8";

  return result.str();
}
