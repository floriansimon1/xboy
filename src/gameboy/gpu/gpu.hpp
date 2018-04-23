#ifndef GPU_HPP
#define GPU_HPP

#include <memory>

#include "graphical-objects.hpp"
#include "../types.hpp"
#include "gpu-mode.hpp"
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
  struct State {
    const Mode           mode;
    const unsigned short scanline;
    const bool           displayEnabled;
  };

  typedef std::experimental::optional<Gpu::State> OptionalState;

  struct Gpu {
    Gpu();

    OptionalTick displayStartTick;
    FrameBuffer  frameBuffer;
    Screen       *screen;

    void reset();
    void process(Gameboy &gameboy);
    void drawScanline(const Gameboy &gameboy, uint8_t displayControlRegister, Scanline scanline);

    Scanline getScanlineOfTick(const Tick &tick) const;

    private:
      OptionalState previousState;

      void drawTiles(const Gameboy &gameboy, uint8_t displayControlRegister, Scanline scanline);
      void drawSprites(const Gameboy &gameboy, uint8_t displayControlRegister, Scanline scanline);
  };

  // Exposed only for tests.
  State getStateOfTick(OptionalTick displayStartTick, bool displayEnabled, Tick tick);
  OptionalScanline getScanlineOfTick(OptionalTick displayStartTick, Tick tick);
  Pixel translatePixel(Palette palette, Pixel pixel);
  sf::Color pixelToColor(Pixel pixel);
  State displayDisabledStatus();

  // Returns true if the pixel is transparent.
  bool drawObjectPixel(
    FrameBuffer &frameBuffer,
    const Gameboy &gameboy,
    const GraphicalObject &object,
    Coordinate x,
    Coordinate y,
    Coordinate screenX,
    Coordinate screenY
  );

  void drawTile(
    bool background,
    const Gameboy &gameboy,
    FrameBuffer &frameBuffer,
    const TileConfiguration &tileConfiguration,
    Coordinate x,
    Coordinate y,
    Coordinate screenX,
    Coordinate screenY
  );
}

#endif
