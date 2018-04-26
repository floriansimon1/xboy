#ifndef JOYPAD_HPP
#define JOYPAD_HPP

#include "input-medium.hpp"

struct Gameboy;

struct Joypad {
  Joypad();

  void reset();
  void process(Gameboy &gameboy, const InputMedium &input);

  private:
    bool upWasPressed;
    bool downWasPressed;
    bool leftWasPressed;
    bool rightWasPressed;

    bool aWasPressed;
    bool bWasPressed;
    bool startWasPressed;
    bool selectWasPressed;
};

#endif
