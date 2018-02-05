#include <sstream>

#include "../../debug/flag-string.hpp"
#include "../../gameboy.hpp"
#include "jump.hpp"

Jump::Jump(bool conditional, unsigned short flag, bool negate):
  Instruction(1, 1),
  conditional(conditional),
  negate(negate),
  flag(flag)
{
}

void Jump::execute(Gameboy &gameboy, const uint8_t *data) const {
  if (shouldJump(gameboy)) {
    gameboy.cpu.pc = *reinterpret_cast<const uint16_t*>(data);
  }
}

unsigned short Jump::ticks(Gameboy &gameboy) const {
  if (conditional && !shouldJump(gameboy)) {
    return 16;
  }

  return 12;
}

bool Jump::shouldJump(Gameboy &gameboy) const {
  return !conditional || gameboy.cpu.flagHasValue(flag, !negate);
}

std::string Jump::toString() const {
  std::ostringstream result;

  if (!conditional) {
    return "JP a16";
  }

  result << "JP"
         << (negate ? " N" : " ")
         << flagString(flag)
         << ", a16";

  return result.str();
}
