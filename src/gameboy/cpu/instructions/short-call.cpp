#include <sstream>
#include <iomanip>

#include "../../../debug/flag-string.hpp"
#include "../../gameboy.hpp"
#include "short-call.hpp"

ShortCall::ShortCall(uint16_t hardcodedAddress):
  ConstantTimeInstruction(16, 0, 1),
  hardcodedAddress(hardcodedAddress),
  call(false)
{
}

#include <signal.h>
void ShortCall::execute(Gameboy &gameboy, const uint8_t *) const {
  call.execute(gameboy, reinterpret_cast<const uint8_t*>(&hardcodedAddress));
}

std::string ShortCall::toString() const {
  std::ostringstream result;

  result << "RST "
         << std::hex << std::setfill('0') << std::setw(2)
         << "0x" << ((unsigned int) hardcodedAddress);

  return result.str();
}
