#include <sstream>

#include "unsigned-registers-subtraction.hpp"
#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"

UnsignedRegistersSubtraction::UnsignedRegistersSubtraction(
  CpuRegisterPointer cpuRegister,
  bool carry,
  bool low
):
  Instruction(4, 0, 1),
  low(low),
  cpuRegister(cpuRegister),
  subtractionInstruction(carry)
{
}

void UnsignedRegistersSubtraction::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto subtracted = gameboy.cpu.singleByteRegister(cpuRegister, low);

  subtractionInstruction.execute(gameboy, &subtracted);
}

std::string UnsignedRegistersSubtraction::toString() const {
  std::ostringstream result;

  result << subtractionInstruction.mnemonic() << ' ' << registerString(cpuRegister, true, low);

  return result.str();
}
