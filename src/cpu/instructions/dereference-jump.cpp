#include "../../debug/register-string.hpp"
#include "dereference-jump.hpp"
#include "../../gameboy.hpp"

DereferenceJump::DereferenceJump():
  ConstantTimeInstruction(4, 0, 1),
  jumpInstruction(false)
{
}

void DereferenceJump::execute(Gameboy &gameboy, const uint8_t *) const {
  jumpInstruction.execute(gameboy, gameboy.mmu.memory + gameboy.cpu.hl);
}

std::string DereferenceJump::toString() const {
  return "JP (HL)";
}
