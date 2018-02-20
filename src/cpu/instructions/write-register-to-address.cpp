#include <sstream>

#include "../../debug/register-string.hpp"
#include "write-register-to-address.hpp"
#include "../../gameboy.hpp"

WriteRegisterToAddress::WriteRegisterToAddress(CpuRegisterPointer cpuRegister, bool low):
  ConstantTimeInstruction(16, 2, 1),
  cpuRegister(cpuRegister),
  low(low)
{
}

void WriteRegisterToAddress::execute(Gameboy &gameboy, const uint8_t *data) const {
  const auto address = *reinterpret_cast<const uint16_t*>(data);

  gameboy.mmu.memory[address] = gameboy.cpu.singleByteRegister(cpuRegister, low);
}

std::string WriteRegisterToAddress::toString() const {
  std::ostringstream result;

  result << "LD (a16), " << registerString(cpuRegister, true, low);

  return result.str();
}
