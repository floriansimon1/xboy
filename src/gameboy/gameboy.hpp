#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include <SFML/System.hpp>

#include "gpu/gpu.hpp"
#include "cpu/cpu.hpp"
#include "memory/mmu.hpp"

struct Gameboy {
  sf::Clock          clock;
  unsigned long long lastPause;

  Gpu::Gpu gpu;
  Mmu      mmu;
  Cpu      cpu;

  bool lowPowerMode;

  Gameboy();

  void tick();
  void reset();
  void sleep();
};

#endif
