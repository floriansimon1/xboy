#include <iostream>
#include <thread>
#include <chrono>

#include "gameboy.hpp"

constexpr Tick ticksPerSecond = 4194304;

constexpr auto frameDurationMilliseconds = ticksPerFrame * 1000 / ticksPerSecond;

Gameboy::Gameboy() {
  reset();
}

void Gameboy::reset() {
  lowPowerMode = false;
  lastPause    = 0;

  interrupts.reset();
  timer.reset();
  cpu.reset();
  mmu.reset();
  gpu.reset();

  clock.restart();
}

void Gameboy::tick() {
  timer.process(*this);
  gpu.process(*this);
  interrupts.process(*this);
  cpu.process(*this);

  sleep();
}

void Gameboy::sleep() {
  const auto Δt = cpu.ticks - lastPause;

  if (Δt < ticksPerFrame) {
    return;
  }

  const auto elapsedTime = clock.getElapsedTime().asMilliseconds();

  const auto timeCorrection = frameDurationMilliseconds - elapsedTime;

  std::this_thread::sleep_for(std::chrono::milliseconds(timeCorrection));

  lastPause = cpu.ticks;

  clock.restart();
}
