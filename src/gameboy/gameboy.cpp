#include <thread>
#include <chrono>

#include "gameboy.hpp"

constexpr unsigned int cyclesPerSecond = 4194304;

Gameboy::Gameboy() {
  reset();
}

void Gameboy::reset() {
  lowPowerMode        = false;
  synchronizedSeconds = 0;

  cpu.reset();
  mmu.reset();
  gpu.reset();

  clock.restart();
}

void Gameboy::tick() {
  cpu.process(*this);
  gpu.process(*this);
}

void Gameboy::sleep() {
  const auto synchronizedTicks = synchronizedSeconds * cyclesPerSecond;

  // If the CPU second has not yet elapsed, we just do nothing.
  if (cpu.ticks < synchronizedTicks + cyclesPerSecond) {
    return;
  }

  const auto elapsedTime = clock.getElapsedTime().asMilliseconds();

  const auto timeCorrection = 1000 - elapsedTime;

  std::this_thread::sleep_for(std::chrono::milliseconds(timeCorrection));

  synchronizedSeconds++;

  clock.restart();
}
