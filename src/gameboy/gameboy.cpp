#include <iostream>
#include <thread>
#include <chrono>

#include "timers/timer-frequencies.hpp"
#include "joypad/input-medium.hpp"
#include "gameboy.hpp"

constexpr uint16_t programStartAddress   = 0x100;
constexpr auto frameDurationMilliseconds = ticksPerFrame * 1000 / ticksPerSecond;

Gameboy::Gameboy() {
  reset();
}

void Gameboy::reset() {
  bootFailed              = false;
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

  if (!bootFailed && !lowPowerMode) {
    timer.process(*this);
    gpu.process(*this);
    interrupts.process(*this);

    if (!cpu.halted) {
      cpu.process(*this);
    }

    if (cpu.pc == programStartAddress && mmu.inBios()) {
      std::cout << "Boot failed!" << std::endl;

      bootFailed = true;
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

  const auto elapsedTime = clock.getElapsedTime().asMilliseconds();

  if (elapsedTime < frameDurationMilliseconds) {
    const auto timeCorrection = frameDurationMilliseconds - elapsedTime;

    std::this_thread::sleep_for(std::chrono::milliseconds(timeCorrection));
  }

  lastPause = cpu.ticks;

  clock.restart();
}
