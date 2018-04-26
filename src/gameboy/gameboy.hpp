#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include <SFML/System.hpp>

#include "gpu/gpu.hpp"
#include "cpu/cpu.hpp"
#include "cartridge.hpp"
#include "memory/mmu.hpp"
#include "interrupts.hpp"
#include "timers/timer.hpp"
#include "joypad/joypad.hpp"

struct Gameboy {
  sf::Clock            clock;
  bool                 inBios;
  Optional<Cartridge*> cartridge;
  unsigned long long   lastPause;

  Interrupts interrupts;
  Joypad     joypad;
  Timer      timer;
  Gpu::Gpu   gpu;
  Mmu        mmu;
  Cpu        cpu;

  bool lowPowerMode;

  Gameboy();

  void reset();
  void sleep();
  void tick(const InputMedium &inputMedium);
};

#endif
