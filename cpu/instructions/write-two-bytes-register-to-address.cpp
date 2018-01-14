#include <sstream>

#include "write-two-bytes-register-to-address.hpp"
#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"

WriteTwoBytesRegisterToAddress::WriteTwoBytesRegisterToAddress(CpuRegisterPointer cpuRegister):
  Instruction(20, 2, 1),
  cpuRegister(cpuRegister)
{
}

void WriteTwoBytesRegisterToAddress::execute(Gameboy &gameboy, const uint8_t *data) const {
  const auto address = *reinterpret_cast<const uint16_t*>(data);

  gameboy.mmu.memory[address + 1] = gameboy.cpu.singleByteRegister(cpuRegister, false);
  gameboy.mmu.memory[address]     = gameboy.cpu.singleByteRegister(cpuRegister, true);
}

std::string WriteTwoBytesRegisterToAddress::toString() const {
  std::ostringstream result;

  result << "LD (a16), " << registerString(cpuRegister, false, false);

  return result.str();
}

