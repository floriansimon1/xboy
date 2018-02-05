#include <sstream>

#include "../../debug/register-string.hpp"
#include "write-immediate-to-address.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

WriteImmediateToAddress::WriteImmediateToAddress(CpuRegisterPointer pointerRegister):
  ConstantTimeInstruction(12, 1, 1),
  pointerRegister(pointerRegister)
{
}

void WriteImmediateToAddress::execute(Gameboy &gameboy, const uint8_t *data) const {
  const auto address = *reinterpret_cast<const uint16_t*>(gameboy.cpu.twoBytesRegister(pointerRegister));

  gameboy.mmu.memory[address] = *data;
}

std::string WriteImmediateToAddress::toString() const {
  std::ostringstream result;

  result << "LD (" << registerString(pointerRegister, false, false) << "), d8";

  return result.str();
}
