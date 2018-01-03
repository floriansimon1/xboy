#ifndef OPERATION_HPP
#define OPERATION_HPP

#include "execution.hpp"

struct Gameboy;

struct Operation {
  virtual Execution execute(Gameboy &gameboy) = 0;
};

#endif

