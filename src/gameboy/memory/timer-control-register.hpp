#ifndef TIMER_CONTROL_REGISTER_HPP
#define TIMER_CONTROL_REGISTER_HPP

#include <cstdint>

struct Gameboy;

struct TimerControlRegister {
  TimerControlRegister(const Gameboy &gameboy);

  bool timersEnabled() const;
  unsigned int ticks() const;

  private:
    const uint8_t value;
};

#endif
