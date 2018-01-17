#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include "cpu/cpu.hpp"
#include "memory/mmu.hpp"

struct Gameboy {
  Mmu mmu;
  Cpu cpu;

  bool lowPowerMode;

  Gameboy();

  void tick();
  void reset();
};

#endif
