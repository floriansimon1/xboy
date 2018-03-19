#ifndef GPU_HPP
#define GPU_HPP

#include <memory>

#include "screen.hpp"

struct Gpu {
  Gpu();

  Screen *screen;

  void reset();
};

#endif
