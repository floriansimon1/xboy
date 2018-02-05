#include <sstream>

#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"
#include "registers-and.hpp"

RegistersAnd::RegistersAnd(CpuRegisterPointer cpuRegister, bool low):
  Instruction(4, 0, 1),
  low(low),
  cpuRegister(cpuRegister),
  andInstruction()
{
}

void RegistersAnd::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  andInstruction.execute(gameboy, &value);
}

std::string RegistersAnd::toString() const {
  std::ostringstream result;

  result << "AND " << registerString(cpuRegister, true, low);

  return result.str();
}
