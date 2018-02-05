#include <sstream>

#include "../../debug/flag-string.hpp"
#include "relative-jump-flag.hpp"
#include "../../gameboy.hpp"

RelativeJumpFlag::RelativeJumpFlag(bool conditional, unsigned short flag, bool negate):
  Instruction(8, 1, 1),
  conditional(conditional),
  negate(negate),
  flag(flag)
{
}

void RelativeJumpFlag::execute(Gameboy &gameboy, const uint8_t *data) const {
  if (shouldJump(gameboy)) {
    gameboy.cpu.pc += *reinterpret_cast<const int8_t *>(data);
  }
}

unsigned short RelativeJumpFlag::ticks(Gameboy &gameboy) const {
  if (shouldJump(gameboy)) {
    return 12;
  }

  return 8;
}

bool RelativeJumpFlag::shouldJump(Gameboy &gameboy) const {
  return !conditional || gameboy.cpu.flagHasValue(flag, !negate);
}

std::string RelativeJumpFlag::toString() const {
  std::ostringstream result;

  result << "JR"
         << (negate ? " N" : " ")
         << flagString(flag)
         << ", r8";

  return result.str();
}
