#include <sstream>

#include "../../../debug/register-string.hpp"
#include "dereference-single-register.hpp"
#include "../../gameboy.hpp"

DereferenceSingleRegister::DereferenceSingleRegister(
  CpuRegisterPointer source,
  const bool         sourceLow,
  CpuRegisterPointer destination,
  const bool         destinationLow
):
  ConstantTimeInstruction(8, 0, 1),
  source(source),
  sourceLow(sourceLow),
  destination(destination),
  destinationLow(destinationLow)
{
}

void DereferenceSingleRegister::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setSingleByteRegister(
    destination,
    destinationLow,
    gameboy.mmu[gameboy.cpu.singleByteRegister(source, sourceLow) + 0xff00]
  );
}

std::string DereferenceSingleRegister::toString() const {
  std::ostringstream result;

  result << "LD "
         << registerString(destination, true, destinationLow)
         << ", ("
         << registerString(source, true, sourceLow)
         << ')';

  return result.str();
}
