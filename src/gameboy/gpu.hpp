#ifndef GPU_HPP
#define GPU_HPP

#include <memory>

#include "types.hpp"
#include "screen.hpp"

struct Gameboy;

constexpr Tick ticksPerVramAccess = 172;
constexpr Tick ticksPerScanline   = 456;
constexpr Tick scanlinesInFrame   = 154;
constexpr Tick ticksPerHblank     = 204;
constexpr Tick realScanlines      = 144;
constexpr Tick ticksPerOamAccess  = 80;

constexpr Tick ticksPerFrame = ticksPerScanline * scanlinesInFrame;

struct Gpu {
  enum Mode {
    Hblank     = 0,
    Vblank     = 1,
    OamAccess  = 2,
    VramAccess = 3
  };

  struct Status {
    const Mode           mode;
    const bool           display;
    const unsigned short scanline;
  };

  Gpu();

  Screen *screen;

  void reset();
  void process(Gameboy &gameboy);

  private:
    std::experimental::optional<Tick>  displayStartTick;
};

// Exposed only for tests.
OptionalScanline getScanlineOfTick(OptionalTick displayStartTick, Tick tick);
Gpu::Status getStatusOfTick(OptionalTick displayStartTick, Tick tick);
Gpu::Status displayDisabledStatus();

#endif
