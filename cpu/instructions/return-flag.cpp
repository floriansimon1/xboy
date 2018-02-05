#include <sstream>

#include "../../debug/flag-string.hpp"
#include "return-flag.hpp"
#include "../../gameboy.hpp"

ReturnFlag::ReturnFlag(unsigned short flag, bool negate):
  Instruction(8, 1, 1),
  negate(negate),
  flag(flag)
{
}

void ReturnFlag::execute(Gameboy &gameboy, const uint8_t *) const {
  if (shouldJump(gameboy)) {
    gameboy.cpu.pc = gameboy.mmu.popTwoBytesFromStack(gameboy.cpu);
  }
}

unsigned short ReturnFlag::ticks(Gameboy &gameboy) const {
  if (shouldJump(gameboy)) {
    return 20;
  }

  return 8;
}

bool ReturnFlag::shouldJump(Gameboy &gameboy) const {
  return gameboy.cpu.flagHasValue(flag, !negate);
}

std::string ReturnFlag::toString() const {
  std::ostringstream result;

  result << "RET" << (negate ? " N" : " ") << flagString(flag);

  return result.str();
}
