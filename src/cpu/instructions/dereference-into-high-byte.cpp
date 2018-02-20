#include "dereference-high-byte.hpp"
#include "../../gameboy.hpp"

DereferenceIntoHighByte::DereferenceIntoHighByte():
  ConstantTimeInstruction(12, 1, 1),
  loadInstruction(&Cpu::af, false)
{
}

void DereferenceIntoHighByte::execute(Gameboy &gameboy, const uint8_t *data) const {
  const uint16_t address = 0xff00 + *data;

  loadInstruction.execute(gameboy, gameboy.mmu.memory + address);
}

std::string DereferenceIntoHighByte::toString() const {
  return "LDH (a8), A";
}
