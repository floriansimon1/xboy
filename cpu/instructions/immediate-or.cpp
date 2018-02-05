#include <sstream>

#include "../../gameboy.hpp"
#include "immediate-or.hpp"
#include "../../bit.hpp"

ImmediateOr::ImmediateOr(bool exclusive): Instruction(8, 1, 1), exclusive(exclusive) {
}

void ImmediateOr::execute(Gameboy &gameboy, const uint8_t *data) const {
  gameboy.cpu.clearAllFlags();

  const auto a = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  const auto result = (
    exclusive
    ? a ^ *data
    : a | *data
  );

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, result);

  gameboy.cpu.setZeroFlag(!result);
}

std::string ImmediateOr::toString() const {
  std::ostringstream result;

  result << mnemonic() << " d8";

  return result.str();
}

const char* ImmediateOr::mnemonic() const {
  return exclusive ? "XOR " : "OR ";
}
