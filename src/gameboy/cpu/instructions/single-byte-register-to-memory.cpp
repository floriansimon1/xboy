#include <sstream>

#include "single-byte-register-to-memory.hpp"
#include "../../../debug/register-string.hpp"
#include "../../gameboy.hpp"

SingleByteRegisterToMemory::SingleByteRegisterToMemory(CpuRegisterPointer memoryPointer, CpuRegisterPointer cpuRegister, bool low):
  ConstantTimeInstruction(8, 0, 1),
  memoryPointer(memoryPointer),
  cpuRegister(cpuRegister),
  low(low)
{
}

void SingleByteRegisterToMemory::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto written = gameboy.cpu.singleByteRegister(cpuRegister, low);
  const auto address = gameboy.cpu.twoBytesRegister(memoryPointer);

  gameboy.mmu.write(gameboy, address, written);
}

std::string SingleByteRegisterToMemory::toString() const {
  std::ostringstream result;

  result << "LD (" << registerString(memoryPointer, false, false) << "), " << registerString(cpuRegister, true, low);

  return result.str();
}
