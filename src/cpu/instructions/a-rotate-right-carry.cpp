#include "../../debug/register-string.hpp"
#include "a-rotate-right-carry.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

RotateRightCarryA::RotateRightCarryA():
  ConstantTimeInstruction(4, 0, 1),
  standardRotateRightCarry(&Cpu::af, false)
{
}

void RotateRightCarryA::execute(Gameboy &gameboy, const uint8_t *data) const {
  standardRotateRightCarry.execute(gameboy, data);
}

std::string RotateRightCarryA::toString() const {
  return "RRCA";
}
