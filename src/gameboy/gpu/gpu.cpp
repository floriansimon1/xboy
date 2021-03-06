#include <SFML/Graphics.hpp>

#include "gpu.hpp"
#include "../types.hpp"
#include "../gameboy.hpp"
#include "../memory/lcd-status-register.hpp"
#include "../memory/display-control-register.hpp"

constexpr uint16_t backgroundXAddress = 0xff43;
constexpr uint16_t backgroundYAddress = 0xff42;
constexpr uint16_t windowXAddress     = 0xff4b;
constexpr uint16_t windowYAddress     = 0xff4a;

Gpu::Gpu::Gpu(): screen(nullptr) {
  reset();
}

Scanline Gpu::Gpu::getScanlineOfTick(const Tick &tick) const {
  return ::Gpu::getScanlineOfTick(displayStartTick, tick).value_or(0);
}

// The top line should be black, the rest should be white.
void Gpu::Gpu::displayStopScreen() {
  for (uint8_t i = 0; i < screenWidth; i++) {
    auto &frameBuffer = screen->getFrameBuffer();

    frameBuffer.setPixel(i, 0, black);

    for (uint8_t j = 1; j < screenHeight; j++) {
      frameBuffer.setPixel(i, 0, white);
    }

    screen->display();
  }
}

void Gpu::Gpu::process(Gameboy &gameboy) {
  const auto oldState               = previousState;
  const auto displayControlRegister = gameboy.mmu.readDisplayControlRegister(gameboy);

  const auto newState = getStateOfTick(
    displayStartTick,
    DisplayControlRegister::enabled(displayControlRegister),
    gameboy.cpu.ticks
  );

  previousState.emplace(newState);

  if (!newState.displayEnabled) {
    return;
  }

  const LcdStatusRegister lcdStatus(gameboy);

  const auto isStartOfNewScanline = !oldState || oldState.value().scanline != newState.scanline;
  const auto isStartOfMode        = !oldState || newState.mode != oldState.value().mode;

  if (isStartOfMode && newState.mode == Mode::Vblank) {
    screen->display();

    gameboy.interrupts.requestVblankInterrupt(gameboy);
  } else if (isStartOfNewScanline && newState.scanline < realScanlines) {
    drawScanline(gameboy, displayControlRegister, newState.scanline);
  }

  if (
    (isStartOfMode && lcdStatus.interruptOnModeChange(newState.mode))
    || (isStartOfNewScanline && lcdStatus.shouldTriggerScanlineInterrupt(gameboy, newState.scanline))
  ) {
    gameboy.interrupts.requestLcdInterrupt(gameboy);
  }
}

void Gpu::Gpu::reset() {
  displayStartTick = {};

  if (screen) {
    for (Coordinate x = 0; x < screenWidth; x++) {
      for (Coordinate y = 0; y < screenHeight; y++) {
        screen->getFrameBuffer().setPixel(x, y, white);
      }
    }
  }
}

void Gpu::Gpu::drawScanline(const Gameboy &gameboy, uint8_t displayControlRegister, Scanline scanline) {
  if (
    DisplayControlRegister::showWindow(displayControlRegister)
    || DisplayControlRegister::showBackground(displayControlRegister)
  ) {
    drawTiles(gameboy, displayControlRegister, scanline);
  }

  if (DisplayControlRegister::showSprites(displayControlRegister)) {
    drawSprites(gameboy, displayControlRegister, scanline);
  }
}

void Gpu::Gpu::drawSprites(const Gameboy &gameboy, uint8_t displayControlRegister, Scanline scanline) {
  const SpriteConfiguration spriteConfiguration(displayControlRegister);

  auto &frameBuffer = screen->getFrameBuffer();

  // Iterate in reverse to stop once prioritary sprites have been displayed.
  for (Coordinate x = 0; x < screenWidth; x++) {
    const sf::IntRect  pixelRectangle(x, scanline, 1, 1);
    const sf::Vector2i point(x, scanline);

    for (auto i = numberOfSprites - 1; i >= 0; i--) {
      const Sprite sprite(gameboy, spriteConfiguration, i);

      // Non-prioritary sprites cannot be drawn over non-white backgrounds.
      if (sprite.backgroundPrioritary && !frameBuffer.pixelIsWhite(x, scanline)) {
        continue;
      }

      const sf::IntRect  spriteRectangle(sprite.x, sprite.y, spriteWidth, sprite.height);
      const sf::Vector2i spriteStartPoint(sprite.x, sprite.y);

      if (spriteRectangle.contains(point)) {
        const sf::Vector2i spritePixel = point - spriteStartPoint;

        const auto transparent = drawObjectPixel(frameBuffer, gameboy, sprite, spritePixel.x, spritePixel.y, x, scanline);

        // The last sprite's pixel has been written. It can be overwritten.
        if (transparent) {
          break;
        }
      }
    }
  }
}

void Gpu::Gpu::drawTiles(const Gameboy &gameboy, uint8_t displayControlRegister, Scanline scanline) {
  const auto backgroundStartX = gameboy.mmu.read(gameboy, backgroundXAddress);
  const auto backgroundStartY = gameboy.mmu.read(gameboy, backgroundYAddress);
  const auto windowStartY     = gameboy.mmu.read(gameboy, windowYAddress);

  auto &frameBuffer = screen->getFrameBuffer();

  // Don't ask me why, but windowXAddress points to the window's X minus 7.
  const auto windowStartX = gameboy.mmu.read(gameboy, windowXAddress - 7);

  const TileConfiguration tileConfiguration(gameboy);

  const Coordinate backgroundY = backgroundStartY + scanline;
  const Coordinate windowY     = scanline - windowStartY;

  for (Coordinate x = 0; x < screenWidth; x++) {
    if (DisplayControlRegister::showBackground(displayControlRegister)) {
      const Coordinate backgroundX = x + backgroundStartX;

      drawTile(true, gameboy, frameBuffer, tileConfiguration, backgroundX, backgroundY, x, scanline);
    }

    if (DisplayControlRegister::showWindow(displayControlRegister)) {
      const Coordinate windowX = x - windowStartX;

      drawTile(false, gameboy, frameBuffer, tileConfiguration, windowX, windowY, x, scanline);
    }
  }
}

void Gpu::drawTile(
  bool background,
  const Gameboy &gameboy,
  FrameBuffer &frameBuffer,
  const TileConfiguration &tileConfiguration,
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

  const Tile tile(gameboy, tileConfiguration, background, tilemapX, tilemapY);

  drawObjectPixel(frameBuffer, gameboy, tile, tileX, tileY, screenX, screenY);
}

bool Gpu::drawObjectPixel(
  FrameBuffer &frameBuffer,
  const Gameboy &gameboy,
  const GraphicalObject &object,
  Coordinate x,
  Coordinate y,
  Coordinate screenX,
  Coordinate screenY
) {
  const auto pixel = readObjectPixel(gameboy, object, x, y);

  const auto translatedPixel = translatePixel(object.palette, pixel);

  frameBuffer.setPixel(screenX, screenY, pixelToColor(translatedPixel));

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

Color Gpu::pixelToColor(Pixel pixel) {
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
