#include <sstream>

#include "../../debug/register-string.hpp"
#include "copy-register.hpp"
#include "../../gameboy.hpp"

CopyRegister::CopyRegister(CpuRegisterPointer to, bool toLow, CpuRegisterPointer from, bool fromLow):
  Instruction(4, 0, 1),
  fromLow(fromLow),
  toLow(toLow),
  from(from),
  to(to)
{
}

void CopyRegister::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setSingleByteRegister(to, toLow, gameboy.cpu.singleByteRegister(from, fromLow));
}

std::string CopyRegister::toString() const {
  std::ostringstream result;

  result << "LD " << registerString(to, true, toLow) << ", " << registerString(from, true, fromLow);

  return result.str();
}
