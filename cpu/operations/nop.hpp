#ifndef NOP_HPP
#define NOP_HPP

#include "../operation.hpp"

struct Nop: Operation {
  Execution execute(Gameboy &gameboy) override;
};

#endif

