#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include <SFML/System.hpp>

#include "gpu.hpp"
#include "cpu/cpu.hpp"
#include "memory/mmu.hpp"

struct Gameboy {
  sf::Clock          clock;
  unsigned long long synchronizedSeconds;

  Mmu mmu;
  Gpu gpu;
  Cpu cpu;

  bool lowPowerMode;

  Gameboy();

  void tick();
  void reset();
  void sleep();
};

#endif
