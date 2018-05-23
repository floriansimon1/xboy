#include <iostream>
#include <thread>
#include <chrono>

#include "timers/timer-frequencies.hpp"
#include "joypad/input-medium.hpp"
#include "gameboy.hpp"

constexpr auto frameDurationMilliseconds = ticksPerFrame * 1000 / ticksPerSecond;

Gameboy::Gameboy() {
  reset();
}

void Gameboy::reset() {
  lowPowerMode            = false;
  lastPause               = 0;
  joypadProcessingCounter = 0;

  interrupts.reset();
  timer.reset();
  cpu.reset();
  mmu.reset();
  gpu.reset();

  clock.restart();
}

void Gameboy::tick(const InputMedium &inputMedium) {
  // If the counter overflows...
  if (!joypadProcessingCounter) {
    joypad.process(*this, inputMedium);
  }

  if (!lowPowerMode) {
    timer.process(*this);
    gpu.process(*this);
    interrupts.process(*this);

    if (!cpu.halted) {
      cpu.process(*this);
    }

    sleep();
  } else {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  joypadProcessingCounter++;
}

void Gameboy::sleep() {
  const auto Δt = cpu.ticks - lastPause;

  if (Δt < ticksPerFrame) {
    return;
  }

  const unsigned int elapsedTime = clock.getElapsedTime().asMilliseconds();

  if (elapsedTime < frameDurationMilliseconds) {
    const auto timeCorrection = frameDurationMilliseconds - elapsedTime;

    std::this_thread::sleep_for(std::chrono::milliseconds(timeCorrection));
  }

  lastPause = cpu.ticks;

  clock.restart();
}
