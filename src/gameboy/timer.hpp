#ifndef TIMER_HPP
#define TIMER_HPP

struct Gameboy;

struct Timer {
  Timer();

  void reset();
  void process(Gameboy &gameboy);
};

#endif
