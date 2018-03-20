#include "gameboy.hpp"

Gameboy::Gameboy() {
  reset();
}

void Gameboy::reset() {
  cpu.reset();
  mmu.reset();
  gpu.reset();

  lowPowerMode = false;
}

void Gameboy::tick() {
  cpu.process(*this);
}

