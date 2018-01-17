#include "../../debug/register-string.hpp"
#include "a-rotate-right.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

RotateRightA::RotateRightA():
  Instruction(4, 0, 1),
  standardRotateRight(&Cpu::af, false)
{
}

void RotateRightA::execute(Gameboy &gameboy, const uint8_t *data) const {
  standardRotateRight.execute(gameboy, data);
}

std::string RotateRightA::toString() const {
  return "RRA";
}
