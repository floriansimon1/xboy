#include "gpu.hpp"
#include "types.hpp"
#include "gameboy.hpp"

Gpu::Gpu() {
  reset();
}

void Gpu::process(Gameboy &gameboy) {
  const auto scanline = getScanlineOfTick(displayStartTick, gameboy.cpu.ticks);
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
