#include <sstream>

#include "../../../debug/register-string.hpp"
#include "../../gameboy.hpp"
#include "push-word.hpp"

PushWord::PushWord(CpuRegisterPointer cpuRegister): ConstantTimeInstruction(16, 0, 1), cpuRegister(cpuRegister) {
}

void PushWord::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.mmu.pushWordToStack(gameboy, gameboy.cpu.twoBytesRegister(cpuRegister));
}

std::string PushWord::toString() const {
  std::ostringstream result;

  result << "PUSH " << registerString(cpuRegister, false, false);

  return result.str();
}
