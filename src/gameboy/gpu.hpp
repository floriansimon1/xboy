#ifndef GPU_HPP
#define GPU_HPP

#include <memory>

#include "screen.hpp"

struct Gameboy;

struct Gpu {
  Gpu();

  Screen *screen;

  void reset();
  void process(Gameboy &gameboy);
};

#endif
