#include "gameboy.hpp"

Gameboy::Gameboy() {
  reset();
}

void Gameboy::reset() {
  cpu.reset();

  lowPowerMode = false;
}

void Gameboy::tick() {
  cpu.process(*this);
}