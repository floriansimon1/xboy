#ifndef GPU_HPP
#define GPU_HPP

#include <memory>

#include "types.hpp"
#include "screen.hpp"

struct Gameboy;

// Exposed only for tests.
OptionalScanline getScanlineOfTick(OptionalTick displayStartTick, Tick tick);

struct Gpu {
  Gpu();

  Screen *screen;

  void reset();
  void process(Gameboy &gameboy);

  OptionalScanline scanlineOfTick(Tick tick) const;

  private:
    std::experimental::optional<Tick>  displayStartTick;
};

#endif
