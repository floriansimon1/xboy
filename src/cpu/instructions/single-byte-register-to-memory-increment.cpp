#include <sstream>

#include "single-byte-register-to-memory-increment.hpp"
#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"

SingleByteRegisterToMemoryIncrement::SingleByteRegisterToMemoryIncrement(
  CpuRegisterPointer memoryPointer,
  CpuRegisterPointer cpuRegister,
  short sign,
  bool low
):
  Instruction(8, 0, 1),
  dereferenceInstruction(memoryPointer, cpuRegister, low),
  sign(sign)
{
}

void SingleByteRegisterToMemoryIncrement::execute(Gameboy &gameboy, const uint8_t *data) const {
  dereferenceInstruction.execute(gameboy, data);

  gameboy.cpu.*(dereferenceInstruction.memoryPointer) += sign;
}

std::string SingleByteRegisterToMemoryIncrement::toString() const {
  std::ostringstream result;

  const auto signChar = sign == -1 ? '-' : '+';

  result << "LD (" << registerString(dereferenceInstruction.memoryPointer, false, false) << signChar << ')'
         << ", " << registerString(dereferenceInstruction.cpuRegister, true, true);

  return result.str();
}
