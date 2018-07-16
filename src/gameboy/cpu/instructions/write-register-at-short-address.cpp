#include <sstream>

#include "write-register-at-short-address.hpp"
#include "../../../debug/register-string.hpp"
#include "../../gameboy.hpp"

WriteRegisterAtShortAddress::WriteRegisterAtShortAddress(
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

void WriteRegisterAtShortAddress::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.mmu.write(
    gameboy,
    0xff00 + gameboy.cpu.singleByteRegister(destination, destinationLow),
    gameboy.cpu.singleByteRegister(source, sourceLow)
  );
}

std::string WriteRegisterAtShortAddress::toString() const {
  std::ostringstream result;

  result << "LD "
         << "("
         << registerString(destination, true, destinationLow)
         << "), "
         << registerString(source, true, sourceLow);

  return result.str();
}
