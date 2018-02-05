#include <sstream>

#include "../../debug/register-string.hpp"
#include "push-two-bytes.hpp"
#include "../../gameboy.hpp"

PushTwoBytes::PushTwoBytes(CpuRegisterPointer cpuRegister): ConstantTimeInstruction(16, 0, 1), cpuRegister(cpuRegister) {
}

void PushTwoBytes::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.mmu.pushTwoBytesToStack(gameboy.cpu, gameboy.cpu.twoBytesRegister(cpuRegister));
}

std::string PushTwoBytes::toString() const {
  std::ostringstream result;

  result << "PUSH " << registerString(cpuRegister, false, false);

  return result.str();
}
