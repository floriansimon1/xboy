#include "../../../debug/register-string.hpp"
#include "a-rotate-left.hpp"
#include "../../gameboy.hpp"
#include "../../../bit.hpp"

RotateLeftA::RotateLeftA():
  ConstantTimeInstruction(4, 0, 1),
  standardRotateLeft(&Cpu::af, false)
{
}

void RotateLeftA::execute(Gameboy &gameboy, const uint8_t *data) const {
  standardRotateLeft.execute(gameboy, data);
}

std::string RotateLeftA::toString() const {
  return "RLA";
}
