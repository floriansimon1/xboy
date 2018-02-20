#include "enable-interrupts.hpp"
#include "../../gameboy.hpp"

EnableInterrupts::EnableInterrupts(bool enable): ConstantTimeInstruction(4, 0, 1), enable(enable) {
}

void EnableInterrupts::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.interruptsEnabled = enable;
}

std::string EnableInterrupts::toString() const {
  return enable ? "EI" : "DI";
}
