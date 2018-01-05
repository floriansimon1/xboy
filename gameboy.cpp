#include "gameboy.hpp"

void Gameboy::tick() {
  cpu.process(*this);
}

