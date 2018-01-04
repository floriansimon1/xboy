#ifndef NOP_HPP
#define NOP_HPP

#include "../operation.hpp"

struct Nop: Operation {
  void execute(Gameboy &gameboy) override;

  Nop();
};

#endif

