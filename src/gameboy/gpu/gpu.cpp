#include <SFML/Graphics.hpp>

#include "gpu.hpp"
#include "../types.hpp"
#include "../gameboy.hpp"
#include "../memory/display-control-register.hpp"

constexpr uint16_t backgroundXAddress       = 0xff43;
constexpr uint16_t backgroundYAddress       = 0xff42;
constexpr uint16_t windowXAddress           = 0xff4b;
constexpr uint16_t windowYAddress           = 0xff4a;
constexpr uint16_t backgroundPaletteAddress = 0xff47;

Gpu::Gpu::Gpu() {
  reset();
}

void Gpu::Gpu::process(Gameboy &gameboy) {
  const auto oldState               = previousState;
  const auto displayControlRegister = gameboy.mmu.readDisplayControlRegister();

  const auto newState = getStateOfTick(
    displayStartTick,
    DisplayControlRegister::enabled(displayControlRegister),
    gameboy.cpu.ticks
  );

  previousState.emplace(newState);

  if (!newState.displayEnabled) {
    return;
  }

  const auto isStartOfNewScanline = !oldState || oldState.value().scanline != newState.scanline;

  const auto isStartOfVblank = (
    oldState
    && newState.mode == Mode::Vblank
    && oldState.value().mode != Mode::Vblank
  );

  if (isStartOfVblank) {
    screen->display(frameBuffer);
  } else if (isStartOfNewScanline) {
    drawScanline(gameboy.mmu, displayControlRegister, newState.scanline);
  }
}

void Gpu::Gpu::reset() {
  displayStartTick = {};

  for (size_t i = 0; i < frameSize; i++) {
    frameBuffer[i] = i % 4 == 3 ? maxUint8 : 0;
  }
}

void Gpu::Gpu::drawScanline(const Mmu &mmu, uint8_t displayControlRegister, Scanline scanline) {
  if (
    DisplayControlRegister::showWindow(displayControlRegister)
    || DisplayControlRegister::showBackground(displayControlRegister)
  ) {
    drawTiles(mmu, displayControlRegister, scanline);
  }

  if (DisplayControlRegister::showSprites(displayControlRegister)) {
    drawSprites(mmu, displayControlRegister, scanline);
  }
}

void Gpu::Gpu::drawSprites(const Mmu &mmu, uint8_t displayControlRegister, Scanline scanline) {
  const SpriteData spriteData(displayControlRegister);

  // Iterate in reverse to stop once prioritary sprites have been displayed.
  for (Coordinate x = 0; x < screenWidth; x++) {
    for (auto i = numberOfSprites - 1; i >= 0; i--) {
      const Sprite sprite(mmu, i);

      if (sprite.backgroundPrioritary && !pixelIsWhite(frameBuffer, x, scanline)) {
        continue;
      }
    }
  }
}

void Gpu::Gpu::drawTiles(const Mmu &mmu, uint8_t displayControlRegister, Scanline scanline) {
  const auto palette          = mmu[backgroundPaletteAddress];
  const auto backgroundStartX = mmu[backgroundXAddress];
  const auto backgroundStartY = mmu[backgroundYAddress];
  const auto windowStartY     = mmu[windowYAddress];

  // Don't ask me why, but windowXAddress points to the window's X minus 7.
  const auto windowStartX = mmu[windowXAddress - 7];

  const TileData tileData(mmu);

  const Coordinate backgroundY = backgroundStartY + scanline;
  const Coordinate windowY     = scanline - windowStartY;

  for (Coordinate x = 0; x < screenWidth; x++) {
    if (DisplayControlRegister::showBackground(displayControlRegister)) {
      const Coordinate backgroundX = x + backgroundStartX;

      drawTile(true, mmu, frameBuffer, tileData, palette, backgroundX, backgroundY, x, scanline);
    }

    if (DisplayControlRegister::showWindow(displayControlRegister)) {
        const Coordinate windowX = x - windowStartX;

        drawTile(false, mmu, frameBuffer, tileData, palette, windowX, windowY, x, scanline);
    }
  }
}

void Gpu::drawTile(
  bool background,
  const Mmu &mmu,
  FrameBuffer &frameBuffer,
  const TileData &tileData,
  Palette palette,
  Coordinate x,
  Coordinate y,
  Coordinate screenX,
  Coordinate screenY
) {
  const Coordinate tilemapX = x / tileWidth;
  const Coordinate tilemapY = y / tileHeight;

  // No need to perform negative checks because Coordinate is an unsigned type.
  if (tilemapX >= tilemapWidth || tilemapY >= tilemapHeight) {
    return;
  }

  const Coordinate tileX = x % tileWidth;
  const Coordinate tileY = y % tileHeight;

  const Tile tile(mmu, tileData, background, tilemapX, tilemapY);

  drawObjectPixel(
    frameBuffer,
    mmu,
    palette,
    tile,
    tileX,
    tileY,
    screenX,
    screenY
  );
}

bool Gpu::drawObjectPixel(
  FrameBuffer &frameBuffer,
  const Mmu &mmu,
  Palette palette,
  const GraphicalObject &object,
  Coordinate x,
  Coordinate y,
  Coordinate screenX,
  Coordinate screenY
) {
  const auto pixel = readObjectPixel(mmu, object, x, y);

  const auto translatedPixel = translatePixel(palette, pixel);

  writeColor(frameBuffer, screenX, screenY, pixelToColor(translatedPixel));

  return !translatedPixel;
}

OptionalScanline Gpu::getScanlineOfTick(OptionalTick displayStartTick, Tick tick) {
  const auto Δticks = tick - displayStartTick.value_or(0);

  const auto absoluteScanline = Δticks / ticksPerScanline;

  const auto scanline = absoluteScanline % scanlinesInFrame;

  return std::experimental::make_optional(scanline);
}

Gpu::State Gpu::getStateOfTick(OptionalTick displayStartTick, bool displayEnabled, Tick tick) {
  Mode mode;

  const auto Δticks = tick - displayStartTick.value_or(0);

  if (!displayEnabled) {
    return displayDisabledStatus();
  }

  const auto scanline = getScanlineOfTick(displayStartTick, tick).value();

  const auto frameTicks = Δticks % ticksPerFrame;

  const auto scanlineTicks = frameTicks - scanline * ticksPerScanline;

  if (scanline >= realScanlines) {
    mode = Mode::Vblank;
  } else if (scanlineTicks < ticksPerOamAccess) {
    mode = Mode::OamAccess;
  } else if (scanlineTicks < ticksPerVramAccess) {
    mode = Mode::VramAccess;
  } else {
    mode = Mode::Hblank;
  }

  return State { mode, scanline, true };
}

Gpu::State Gpu::displayDisabledStatus() {
  /*
  * "One important part to emulate with the lcd modes is when the lcd is disabled the mode must be set
  * to mode 1. If you dont do this then you will spend hours like I did wondering why Mario2 wont play
  * past the title screen. You also need to reset the m_ScanlineCounter and current scanline."
  *
  * Source: http://www.codeslinger.co.uk/pages/projects/gameboy/lcd.html
  */
  return State { Mode::Vblank, 0, false };
}

sf::Color Gpu::pixelToColor(Pixel pixel) {
  switch (pixel) {
    default:

    case 3: return black;
    case 2: return darkGrey;
    case 1: return lightGrey;
    case 0: return white;
  }
}

Pixel Gpu::translatePixel(Palette palette, Pixel pixel) {
  const auto shifts = pixel * 2;

  return (palette >> shifts) & 0b11;
}
