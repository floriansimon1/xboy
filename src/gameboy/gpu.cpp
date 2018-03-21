#include "gpu.hpp"

constexpr unsigned short scanlineDuration = 456;
constexpr unsigned short scanlinesInFrame = 154;

Gpu::Gpu() {
  reset();
}

void Gpu::process(Gameboy &) {
}

OptionalScanline Gpu::scanlineOfTick(Tick tick) const {
  return getScanlineOfTick(displayStartTick, tick);
}

void Gpu::reset() {
  displayStartTick = OptionalTick();
}

OptionalScanline getScanlineOfTick(OptionalTick displayStartTick, Tick tick) {
  if (!displayStartTick) {
    return OptionalScanline();
  }

  const auto Δt = tick - displayStartTick.value();

  const auto absoluteScanline = Δt / scanlineDuration;

  const auto scanline = absoluteScanline % scanlinesInFrame;

  return OptionalScanline(scanline);
}
