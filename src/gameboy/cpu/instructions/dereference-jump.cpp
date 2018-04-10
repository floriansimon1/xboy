#include "../../../debug/register-string.hpp"
#include "dereference-jump.hpp"
#include "../../gameboy.hpp"

DereferenceJump::DereferenceJump():
  ConstantTimeInstruction(4, 0, 1),
  jumpInstruction(false)
{
}

void DereferenceJump::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.mmu.read(gameboy, gameboy.cpu.hl);

  jumpInstruction.execute(gameboy, &value);
}

std::string DereferenceJump::toString() const {
  return "JP (HL)";
}
