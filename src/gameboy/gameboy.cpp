#include <thread>
#include <chrono>

#include "gameboy.hpp"

constexpr unsigned int cyclesPerSecond = 4194304;

Gameboy::Gameboy() {
  reset();

  clock.restart();
}

void Gameboy::reset() {
  cpu.reset();
  mmu.reset();
  gpu.reset();

  lowPowerMode = false;
}

void Gameboy::tick() {
  cpu.process(*this);
}

void Gameboy::sleep() {
  // If the CPU second has not yet elapsed, we just do nothing.
  if (cpu.ticks < cyclesPerSecond) {
    return;
  }

  const auto ticks = cpu.ticks % cyclesPerSecond;

  const auto elapsedTime = clock.getElapsedTime().asMilliseconds();

  const auto timeCorrection = 1000 - elapsedTime;

  std::this_thread::sleep_for(std::chrono::milliseconds(timeCorrection));

  cpu.ticks = ticks;

  clock.restart();
}
