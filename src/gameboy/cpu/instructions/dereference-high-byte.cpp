#include "dereference-high-byte.hpp"
#include "../../gameboy.hpp"

DereferenceHighByte::DereferenceHighByte():
  ConstantTimeInstruction(12, 1, 1),
  loadImmediated8Instruction(&Cpu::af, false)
{
}

void DereferenceHighByte::execute(Gameboy &gameboy, const uint8_t *data) const {
  const uint16_t address = 0xff00 + *data;

  const uint8_t value = gameboy.mmu.read(gameboy, address);

  loadImmediated8Instruction.execute(gameboy, &value);
}

std::string DereferenceHighByte::toString() const {
  return "LDH A, (a8)";
}
