#include <sstream>

#include "../../debug/flag-string.hpp"
#include "../../gameboy.hpp"
#include "call.hpp"

FastCall::FastCall(bool conditional, unsigned short flag, bool negate):
  ConstantTimeInstruction(16, 0, 1)
{
}

void FastCall::execute(Gameboy &gameboy, const uint8_t *data) const {
  if (shouldJump(gameboy)) {
    gameboy.mmu.pushTwoBytesToStack(gameboy.cpu, gameboy.cpu.pc);

    gameboy.cpu.pc = *reinterpret_cast<const uint16_t*>(data);
  }
}

unsigned short FastCall::ticks(Gameboy &gameboy) const {
  if (conditional && !shouldJump(gameboy)) {
    return 24;
  }

  return 12;
}

bool FastCall::shouldJump(Gameboy &gameboy) const {
  return !conditional || gameboy.cpu.flagHasValue(flag, !negate);
}

std::string FastCall::toString() const {
  std::ostringstream result;

  if (!conditional) {
    return "CALL a16";
  }

  result << "CALL"
         << (negate ? " N" : " ")
         << flagString(flag)
         << ", a16";

  return result.str();
}
