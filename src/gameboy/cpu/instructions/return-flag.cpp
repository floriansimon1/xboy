#include <sstream>

#include "../../../debug/flag-string.hpp"
#include "return-flag.hpp"
#include "../../gameboy.hpp"

ReturnFlag::ReturnFlag(bool conditional, unsigned short flag, bool negate):
  Instruction(1, 1),
  conditional(conditional),
  negate(negate),
  flag(flag)
{
}

void ReturnFlag::execute(Gameboy &gameboy, const uint8_t *) const {
  if (shouldJump(gameboy)) {
    gameboy.cpu.returnFromFunction(gameboy);
  }
}

unsigned short ReturnFlag::ticks(Gameboy &gameboy) const {
  if (!conditional) {
    return 16;
  } else if (shouldJump(gameboy)) {
    return 20;
  }

  return 8;
}

bool ReturnFlag::shouldJump(Gameboy &gameboy) const {
  return !conditional || gameboy.cpu.flagHasValue(flag, !negate);
}

std::string ReturnFlag::toString() const {
  std::ostringstream result;

  result << "RET" << (negate ? " N" : " ") << flagString(flag);

  return result.str();
}
