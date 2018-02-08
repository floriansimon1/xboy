#include "return-from-interrupt.hpp"
#include "../../gameboy.hpp"

ReturnFromInterrupt::ReturnFromInterrupt():
  ConstantTimeInstruction(16, 0, 1),
  returnInstruction(false)
{
}

void ReturnFromInterrupt::execute(Gameboy &gameboy, const uint8_t *data) const {
  returnInstruction.execute(gameboy, data);

  gameboy.cpu.inInterrupt = false;
}

std::string ReturnFromInterrupt::toString() const {
  return "RETI";
}
