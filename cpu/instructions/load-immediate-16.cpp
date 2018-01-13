#include <sstream>

#include "../../debug/register-string.hpp"
#include "load-immediate-16.hpp"
#include "../../gameboy.hpp"

LoadImmediate16::LoadImmediate16(CpuRegisterPointer cpuRegister):
  Instruction(12, 2, 1),
  cpuRegister(cpuRegister)
{
}

void LoadImmediate16::execute(Gameboy &gameboy, const uint8_t *data) const {
  gameboy.cpu.*cpuRegister = *reinterpret_cast<const uint16_t*>(data);
}

std::string LoadImmediate16::toString() const {
  std::ostringstream result;

  result << "LD " << registerString(cpuRegister, false, false) << ", d16";

  return result.str();
}
