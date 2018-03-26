#include "gpu.hpp"
#include "types.hpp"
#include "gameboy.hpp"

#warning "Display power status is not yet implemented!"

Gpu::Gpu() {
  reset();
}

void Gpu::process(Gameboy &) {
}

void Gpu::reset() {
  displayStartTick = OptionalTick();
}

OptionalScanline getScanlineOfTick(OptionalTick displayStartTick, Tick tick) {
  if (!displayStartTick) {
    return OptionalScanline();
  }

  const auto Δticks = tick - displayStartTick.value();

  const auto absoluteScanline = Δticks / ticksPerScanline;

  const auto scanline = absoluteScanline % scanlinesInFrame;

  return OptionalScanline(scanline);
}

Gpu::Status getStatusOfTick(OptionalTick displayStartTick, Tick tick) {
  Gpu::Mode mode;

  const auto displayEnabled = false;
  const auto Δticks         = tick - displayStartTick.value();

  if (!displayEnabled) {
    return displayDisabledStatus();
  }

  const auto scanline = getScanlineOfTick(displayStartTick, tick).value();

  const auto frameTicks = Δticks % ticksPerFrame;

  const auto scanlineTicks = frameTicks - scanline * ticksPerScanline;

  if (scanlineTicks < ticksPerOamAccess) {
    mode = Gpu::Mode::OamAccess;
  } else if (scanlineTicks < ticksPerVramAccess) {
    mode = Gpu::Mode::VramAccess;
  } else if (scanlineTicks < ticksPerHblank) {
    mode = Gpu::Mode::Hblank;
  } else {
    mode = Gpu::Mode::Vblank;
  }

  return Gpu::Status { mode, true, scanline };
}

Gpu::Status displayDisabledStatus() {
  /*
  * "One important part to emulate with the lcd modes is when the lcd is disabled the mode must be set
  * to mode 1. If you dont do this then you will spend hours like I did wondering why Mario2 wont play
  * past the title screen. You also need to reset the m_ScanlineCounter and current scanline."
  *
  * Source: http://www.codeslinger.co.uk/pages/projects/gameboy/lcd.html
  */
  return Gpu::Status { Gpu::Mode::Vblank, false, 0 };
}
