#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include "gpu.hpp"
#include "cpu/cpu.hpp"
#include "memory/mmu.hpp"

struct Gameboy {
  Mmu mmu;
  Gpu gpu;
  Cpu cpu;

  bool lowPowerMode;

  Gameboy();

  void tick();
  void reset();

  void setScreen(Screen *screen);
};

#endif
