#include <sstream>

#include "../../debug/register-string.hpp"
#include "copy-combined-register.hpp"
#include "../../gameboy.hpp"

CopyCombinedRegister::CopyCombinedRegister(CpuRegisterPointer to, CpuRegisterPointer from):
  ConstantTimeInstruction(8, 0, 1),
  from(from),
  to(to)
{
}

void CopyCombinedRegister::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setTwoBytesRegister(to, gameboy.cpu.twoBytesRegister(from));
}

std::string CopyCombinedRegister::toString() const {
  std::ostringstream result;

  result << "LD " << registerString(to, false, false) << ", " << registerString(from, false, false);

  return result.str();
}
