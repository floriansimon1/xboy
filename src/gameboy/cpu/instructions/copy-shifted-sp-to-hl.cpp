#include "../../../debug/register-string.hpp"
#include "copy-shifted-sp-to-hl.hpp"
#include "../../gameboy.hpp"

CopyShiftedSpToHl::CopyShiftedSpToHl():
  ConstantTimeInstruction(12, 1, 1),
  additionInstruction(),
  copyInstruction(&Cpu::hl, &Cpu::sp)
{
}

void CopyShiftedSpToHl::execute(Gameboy &gameboy, const uint8_t *data) const {
  const auto originalSpValue = gameboy.cpu.sp;

  additionInstruction.execute(gameboy, data);
  copyInstruction.execute(gameboy, data);

  gameboy.cpu.sp = originalSpValue;
}

std::string CopyShiftedSpToHl::toString() const {
  return "LD HL, SP + r8";
}
