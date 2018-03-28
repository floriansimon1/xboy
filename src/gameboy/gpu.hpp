#ifndef GPU_HPP
#define GPU_HPP

#include <memory>

#include "types.hpp"
#include "screen.hpp"

struct Gameboy;

constexpr Tick ticksPerVramAccess = 172;
constexpr Tick scanlinesInFrame   = 154;
constexpr Tick ticksPerHblank     = 204;
constexpr Tick realScanlines      = 144;
constexpr Tick ticksPerOamAccess  = 80;

constexpr Tick ticksPerScanline = ticksPerHblank + ticksPerVramAccess + ticksPerOamAccess;

constexpr Tick ticksPerFrame = ticksPerScanline * scanlinesInFrame;

namespace Gpu {
  enum Mode {
    Hblank     = 0,
    Vblank     = 1,
    OamAccess  = 2,
    VramAccess = 3
  };

  struct State {
    const Mode           mode;
    const unsigned short scanline;
    const bool           displayEnabled;
  };

  typedef std::experimental::optional<Gpu::State> OptionalState;

  struct Gpu {
    Gpu();

    FrameBuffer frameBuffer;
    Screen      *screen;

    void reset();
    void process(Gameboy &gameboy);
    void drawScanline(uint8_t displayControlRegister, Scanline scanline);

    private:
      OptionalState previousState;
      OptionalTick  displayStartTick;

      void drawSprites(uint8_t displayControlRegister, Scanline scanline);
      void drawBackground(uint8_t displayControlRegister, Scanline scanline);
  };
}

// Exposed only for tests.
Gpu::State getStateOfTick(OptionalTick displayStartTick, uint8_t displayControlRegisterValue, Tick tick);
OptionalScanline getScanlineOfTick(OptionalTick displayStartTick, Tick tick);
Gpu::State displayDisabledStatus();

#endif
