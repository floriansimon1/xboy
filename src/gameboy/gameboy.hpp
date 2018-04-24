#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include <SFML/System.hpp>

#include "gpu/gpu.hpp"
#include "cpu/cpu.hpp"
#include "memory/mmu.hpp"
#include "interrupts.hpp"
#include "timers/timer.hpp"

struct Gameboy {
  sf::Clock          clock;
  unsigned long long lastPause;

  Interrupts interrupts;
  Timer      timer;
  Gpu::Gpu   gpu;
  Mmu        mmu;
  Cpu        cpu;

  bool lowPowerMode;

  Gameboy();

  void tick();
  void reset();
  void sleep();
};

#endif
