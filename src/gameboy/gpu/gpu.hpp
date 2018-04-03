#ifndef GPU_HPP
#define GPU_HPP

#include <memory>

#include "../memory/mmu.hpp"
#include "tile-data.hpp"
#include "../types.hpp"
#include "screen.hpp"

struct Gameboy;

constexpr Tick ticksPerVramAccess = 172;
constexpr Tick scanlinesInFrame   = 154;
constexpr Tick ticksPerHblank     = 204;
constexpr Tick realScanlines      = 144;
constexpr Tick ticksPerOamAccess  = 80;

constexpr Tick ticksPerScanline = ticksPerHblank + ticksPerVramAccess + ticksPerOamAccess;

constexpr Tick ticksPerFrame = ticksPerScanline * scanlinesInFrame;

typedef uint8_t Palette;

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
    void drawScanline(const Mmu &mmu, uint8_t displayControlRegister, Scanline scanline);

    private:
      OptionalState previousState;
      OptionalTick  displayStartTick;

      void drawTiles(const Mmu &mmu, uint8_t displayControlRegister, Scanline scanline);
      void drawSprites(uint8_t displayControlRegister, Scanline scanline);
  };
}

// Exposed only for tests.
Gpu::State getStateOfTick(OptionalTick displayStartTick, uint8_t displayControlRegisterValue, Tick tick);
OptionalScanline getScanlineOfTick(OptionalTick displayStartTick, Tick tick);
Pixel translatePixel(Palette palette, Pixel pixel);
sf::Color pixelToColor(Pixel pixel);
Gpu::State displayDisabledStatus();

void drawTile(
  bool background,
  const Mmu &mmu,
  FrameBuffer &frameBuffer,
  const TileData &tileData,
  Palette palette,
  Coordinate x,
  Coordinate y,
  Coordinate screenX,
  Coordinate screenY
);

#endif
