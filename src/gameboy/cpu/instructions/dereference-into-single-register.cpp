#include <sstream>

#include "dereference-into-single-register.hpp"
#include "../../../debug/register-string.hpp"
#include "../../gameboy.hpp"

DereferenceIntoSingleRegister::DereferenceIntoSingleRegister(
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

void DereferenceIntoSingleRegister::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.mmu[gameboy.cpu.singleByteRegister(source, sourceLow) + 0xff00];

  gameboy.cpu.setSingleByteRegister(destination, destinationLow, value);
}

std::string DereferenceIntoSingleRegister::toString() const {
  std::ostringstream result;

  result << "LD ("
         << registerString(destination, true, destinationLow)
         << "), "
         << registerString(source, true, sourceLow);

  return result.str();
}
