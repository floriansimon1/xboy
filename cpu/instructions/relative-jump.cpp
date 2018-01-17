#include "relative-jump.hpp"
#include "../../gameboy.hpp"

RelativeJump::RelativeJump(): Instruction(12, 1, 1) {
}

void RelativeJump::execute(Gameboy &gameboy, const uint8_t *data) const {
  gameboy.cpu.pc += *reinterpret_cast<const int8_t *>(data);
}

std::string RelativeJump::toString() const {
  return "JR r8";
}
