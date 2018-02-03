#include <sstream>

#include "../../debug/register-string.hpp"
#include "unsigned-registers-addition.hpp"
#include "../../gameboy.hpp"

UnsignedRegistersAddition::UnsignedRegistersAddition(
  CpuRegisterPointer cpuRegister,
  bool carry,
  bool low
):
  Instruction(4, 0, 1),
  low(low),
  cpuRegister(cpuRegister),
  additionInstruction(carry)
{
}

void UnsignedRegistersAddition::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setSubtractFlag(false);

  const auto added = gameboy.cpu.singleByteRegister(cpuRegister, low);

  additionInstruction.execute(gameboy, &added);
}

std::string UnsignedRegistersAddition::toString() const {
  std::ostringstream result;

  result << additionInstruction.mnemonic() << registerString(cpuRegister, true, low);

  return result.str();
}
