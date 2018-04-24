#ifndef TIMER_HPP
#define TIMER_HPP

#include "../memory/timer-control-register.hpp"
#include "../types.hpp"

constexpr uint16_t dividerAddress      = 0xff04;
constexpr uint16_t timerCounterAddress = 0xff05; // TIMA

struct Gameboy;

// The divider is calculated, the timer is update imperatively.
struct Timer {
  Timer();

  void reset();
  void process(Gameboy &gameboy);

  void resetTimer(Tick tick);
  void resetDivider(Tick tick);

  uint8_t getDividerOfTick(Tick tick) const;
  uint8_t getTimerCounterOfTick(const TimerControlRegister controlRegister, Tick tick) const;

  private:
    Tick timerStart;
    Tick dividerStart;
    Tick lastTimerIncrementTick;
};

#endif
