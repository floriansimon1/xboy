#include "gpu.hpp"
#include "types.hpp"
#include "gameboy.hpp"

#warning "Display power status is not yet implemented!"

Gpu::Gpu::Gpu() {
  reset();
}

void Gpu::Gpu::process(Gameboy &gameboy) {
  const auto oldState = previousState;
  const auto newState = getStateOfTick(displayStartTick, gameboy.cpu.ticks);

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

  const auto oldScanline = oldState ? oldState.value().scanline : 0;

  if (isStartOfVblank) {
    screen->display(frameBuffer);
  } else if (isStartOfNewScanline) {
    drawScanline(newState.scanline);
  }
}

void Gpu::Gpu::reset() {
  displayStartTick = {};

  for (size_t i = 0; i < frameSize; i++) {
    frameBuffer[i] = i % 4 == 3 ? maxUint8 : 0;
  }
}

void Gpu::Gpu::drawScanline(Scanline scanline) {
  frameBuffer[scanline * 160 + 64] = 255;
}

OptionalScanline getScanlineOfTick(OptionalTick displayStartTick, Tick tick) {
  const auto Δticks = tick - displayStartTick.value_or(0);

  const auto absoluteScanline = Δticks / ticksPerScanline;

  const auto scanline = absoluteScanline % scanlinesInFrame;

  return std::experimental::make_optional(scanline);
}

Gpu::State getStateOfTick(OptionalTick displayStartTick, Tick tick) {
  Gpu::Mode mode;

  const auto displayEnabled = true;
  const auto Δticks         = tick - displayStartTick.value_or(0);

  if (!displayEnabled) {
    return displayDisabledStatus();
  }

  const auto scanline = getScanlineOfTick(displayStartTick, tick).value();

  const auto frameTicks = Δticks % ticksPerFrame;

  const auto scanlineTicks = frameTicks - scanline * ticksPerScanline;

  if (scanline >= realScanlines) {
    mode = Gpu::Mode::Vblank;
  } else if (scanlineTicks < ticksPerOamAccess) {
    mode = Gpu::Mode::OamAccess;
  } else if (scanlineTicks < ticksPerVramAccess) {
    mode = Gpu::Mode::VramAccess;
  } else {
    mode = Gpu::Mode::Hblank;
  }

  return Gpu::State { mode, scanline, true };
}

Gpu::State displayDisabledStatus() {
  /*
  * "One important part to emulate with the lcd modes is when the lcd is disabled the mode must be set
  * to mode 1. If you dont do this then you will spend hours like I did wondering why Mario2 wont play
  * past the title screen. You also need to reset the m_ScanlineCounter and current scanline."
  *
  * Source: http://www.codeslinger.co.uk/pages/projects/gameboy/lcd.html
  */
  return Gpu::State { Gpu::Mode::Vblank, 0, false };
}
