#include "dereference.hpp"
#include "../../gameboy.hpp"

Dereference::Dereference(): ConstantTimeInstruction(16, 2, 1) {
}

void Dereference::execute(Gameboy &gameboy, const uint8_t *data) const {
  const auto address = *reinterpret_cast<const uint16_t*>(data);

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, gameboy.mmu.memory[address]);
}

std::string Dereference::toString() const {
  return "LD A, (a16)";
}
