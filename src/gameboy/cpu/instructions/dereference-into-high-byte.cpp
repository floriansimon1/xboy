#include "dereference-into-high-byte.hpp"
#include "../../gameboy.hpp"

DereferenceIntoHighByte::DereferenceIntoHighByte():
  ConstantTimeInstruction(12, 1, 1)
{
}

void DereferenceIntoHighByte::execute(Gameboy &gameboy, const uint8_t *data) const {
  const uint16_t address = *data + 0xff00;

  gameboy.mmu.write(gameboy, address, gameboy.cpu.singleByteRegister(&Cpu::af, false));
}

std::string DereferenceIntoHighByte::toString() const {
  return "LDH (a8), A";
}
