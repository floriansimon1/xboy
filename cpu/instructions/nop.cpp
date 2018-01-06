#include "nop.hpp"
#include "../../gameboy.hpp"

Nop::Nop(): Instruction(4, 0, 1) {
}

void Nop::execute(Gameboy &gameboy, const uint8_t *data) {
}

