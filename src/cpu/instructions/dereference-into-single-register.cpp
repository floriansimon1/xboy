#include <sstream>

#include "dereference-into-single-register.hpp"
#include "../../debug/register-string.hpp"
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
  const auto dataPointer = gameboy.mmu.memory + 0xff00 + gameboy.cpu.singleByteRegister(source, sourceLow);

  *dataPointer = gameboy.cpu.singleByteRegister(destination, destinationLow);
}

std::string DereferenceIntoSingleRegister::toString() const {
  std::ostringstream result;

  result << "LD ("
         << registerString(destination, true, destinationLow)
         << "), "
         << registerString(source, true, sourceLow);

  return result.str();
}
