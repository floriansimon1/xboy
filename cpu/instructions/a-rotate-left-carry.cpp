#include "../../debug/register-string.hpp"
#include "a-rotate-left-carry.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

RotateLeftCarryA::RotateLeftCarryA():
  Instruction(4, 0, 1),
  standardRotateLeftCarry(&Cpu::af, false)
{
}

void RotateLeftCarryA::execute(Gameboy &gameboy, const uint8_t *data) const {
  standardRotateLeftCarry.execute(gameboy, data);
}

std::string RotateLeftCarryA::toString() const {
  return "RLCA";
}
