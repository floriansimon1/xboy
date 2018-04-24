#include "../../bit.hpp"
#include "../gameboy.hpp"
#include "timer-control-register.hpp"
#include "../timers/timer-frequencies.hpp"

constexpr uint8_t  timersEnabledBit      = 2;
constexpr uint8_t  timersSpeedMask       = 0b11;
constexpr uint16_t timerFrequencyAddress = 0xff07; // TMC

TimerControlRegister::TimerControlRegister(const Gameboy &gameboy):
  value(gameboy.mmu.read(gameboy, timerFrequencyAddress)) {
}

bool TimerControlRegister::timersEnabled() const {
  return getBit(value, timersEnabledBit);
}

unsigned int TimerControlRegister::ticks() const {
  return incrementTicks[value & timersSpeedMask];
}
