#include <sstream>

#include "../../../debug/register-string.hpp"
#include "../../gameboy.hpp"
#include "pop-word.hpp"

PopWord::PopWord(CpuRegisterPointer cpuRegister): ConstantTimeInstruction(12, 0, 1), cpuRegister(cpuRegister) {
}

void PopWord::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setTwoBytesRegister(cpuRegister, gameboy.mmu.popWordFromStack(gameboy));
}

std::string PopWord::toString() const {
  std::ostringstream result;

  result << "POP " << registerString(cpuRegister, false, false);

  return result.str();
}
