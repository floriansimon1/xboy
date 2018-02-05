#include <sstream>

#include "../../debug/register-string.hpp"
#include "pop-two-bytes.hpp"
#include "../../gameboy.hpp"

PopTwoBytes::PopTwoBytes(CpuRegisterPointer cpuRegister): Instruction(12, 0, 1), cpuRegister(cpuRegister) {
}

void PopTwoBytes::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setTwoBytesRegister(cpuRegister, gameboy.mmu.popTwoBytesFromStack(gameboy.cpu));
}

std::string PopTwoBytes::toString() const {
  std::ostringstream result;

  result << "POP " << registerString(cpuRegister, false, false);

  return result.str();
}
