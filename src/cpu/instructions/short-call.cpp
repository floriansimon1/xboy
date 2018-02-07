#include <sstream>
#include <iomanip>

#include "../../debug/flag-string.hpp"
#include "../../gameboy.hpp"
#include "short-call.hpp"

ShortCall::ShortCall(uint8_t hardcodedAddress):
  ConstantTimeInstruction(16, 0, 1),
  hardcodedAddress(hardcodedAddress),
  call(true)
{
}

void ShortCall::execute(Gameboy &gameboy, const uint8_t *) const {
  call.execute(gameboy, &hardcodedAddress);
}

std::string ShortCall::toString() const {
  std::ostringstream result;

  result << "RST "
         << std::hex << std::setfill('0') << std::setw(2)
         << ((unsigned int) hardcodedAddress) << 'h';

  return result.str();
}
