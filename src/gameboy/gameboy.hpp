#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include <chrono>

#include "gpu/gpu.hpp"
#include "cpu/cpu.hpp"
#include "cartridge.hpp"
#include "memory/mmu.hpp"
#include "interrupts.hpp"
#include "timers/timer.hpp"
#include "joypad/joypad.hpp"

struct Gameboy {
  bool debug = false;

  TimePoint          epoch;
  unsigned long long lastPause;
  uint8_t            joypadProcessingCounter;

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

  const Cartridge* cartridge;
};

#endif
