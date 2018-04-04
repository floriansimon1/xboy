#include <iostream>

#include "../../src/gameboy/gpu/gpu.hpp"
#include "gpu-timing-test.hpp"

GpuTimingTest::GpuTimingTest(): Test("GPU timing test") {
}

bool GpuTimingTest::run() {
  const Tick start = 1234;

  const auto noScanline                 = getScanlineOfTick(OptionalTick(), 0);
  const auto firstScanlineOfFirstFrame  = getScanlineOfTick(OptionalTick(start), start);
  const auto firstScanlineOfSecondFrame = getScanlineOfTick(OptionalTick(start), start + ticksPerFrame);
  const auto secondScanline             = getScanlineOfTick(OptionalTick(start), start + ticksPerScanline);

  const auto displayDisabledState     = getStateOfTick(OptionalTick(), false, 0);
  const auto firstScanlineState       = getStateOfTick(OptionalTick(start), true, start);
  const auto secondVramAccessState    = getStateOfTick(OptionalTick(start), true, start + ticksPerScanline + ticksPerOamAccess + 10);
  const auto secondLineOfVblankState  = getStateOfTick(OptionalTick(start), true, start + (realScanlines + 1) * ticksPerScanline);
  const auto hblankOfSecondFrameState = getStateOfTick(OptionalTick(start), true, start + ticksPerFrame + ticksPerOamAccess + ticksPerVramAccess);

  const auto scanlineOk = (
    !noScanline.value()
    && secondScanline.value() == 1
    && firstScanlineOfFirstFrame.value() == 0
    && firstScanlineOfSecondFrame.value() == 0
  );

  const auto displayDisabledStateOk = (
    !displayDisabledState.displayEnabled
    && displayDisabledState.mode == Gpu::Mode::Vblank
    && !displayDisabledState.scanline
  );

  const auto firstScanlineStateOk = (
    firstScanlineState.displayEnabled
    && firstScanlineState.mode == Gpu::Mode::OamAccess
    && !firstScanlineState.scanline
  );

  const auto secondVramAccessStateOk = (
    secondVramAccessState.displayEnabled
    && secondVramAccessState.mode == Gpu::Mode::VramAccess
    && secondVramAccessState.scanline == 1
  );

  const auto secondLineOfVblankStateOk = (
    secondLineOfVblankState.displayEnabled
    && secondLineOfVblankState.mode == Gpu::Mode::Vblank
    && secondLineOfVblankState.scanline == realScanlines + 1
  );

  const auto hblankOfSecondFrameStateOk = (
    hblankOfSecondFrameState.displayEnabled
    && hblankOfSecondFrameState.mode == Gpu::Mode::Hblank
    && !hblankOfSecondFrameState.scanline
  );

  if (!scanlineOk) {
    std::cout << "secondScanline: " << secondScanline.value() << "\n"
              << "noScanline: " << noScanline.value_or(-1) << "\n"
              << "firstScanlineOfFirstFrame: " << firstScanlineOfFirstFrame.value() << "\n"
              << "firstScanlineOfSecondFrame: " << firstScanlineOfSecondFrame.value() << "\n"
              << std::endl;
  }

  if (!displayDisabledStateOk) {
    std::cout << "Display disabled:\n"
              << "Enabled: " << displayDisabledState.displayEnabled << "\n"
              << "Scanline: " << (unsigned short) displayDisabledState.scanline << "\n"
              << "GPU mode: " << (unsigned short) displayDisabledState.mode
              << std::endl;
  }

  if (!firstScanlineStateOk) {
    std::cout << "First scanline:\n"
              << "Enabled: " << firstScanlineState.displayEnabled << "\n"
              << "Scanline: " << (unsigned short) firstScanlineState.scanline << "\n"
              << "GPU mode: " << (unsigned short) firstScanlineState.mode
              << std::endl;
  }

  if (!secondVramAccessStateOk) {
    std::cout << "Second VRAM access:\n"
              << "Enabled: " << secondVramAccessState.displayEnabled << "\n"
              << "Scanline: " << (unsigned short) secondVramAccessState.scanline << "\n"
              << "GPU mode: " << (unsigned short) secondVramAccessState.mode
              << std::endl;
  }

  if (!secondLineOfVblankStateOk) {
    std::cout << "Second line of VBlank:\n"
              << "Enabled: " << secondLineOfVblankState.displayEnabled << "\n"
              << "Scanline: " << (unsigned short) secondLineOfVblankState.scanline << "\n"
              << "GPU mode: " << (unsigned short) secondLineOfVblankState.mode
              << std::endl;
  }

  if (!hblankOfSecondFrameStateOk) {
    std::cout << "Hblank of first scanline of second frame:\n"
              << "Enabled: " << hblankOfSecondFrameState.displayEnabled << "\n"
              << "Scanline: " << (unsigned short) hblankOfSecondFrameState.scanline << "\n"
              << "GPU mode: " << (unsigned short) hblankOfSecondFrameState.mode
              << std::endl;
  }

  return (
    scanlineOk
    && displayDisabledStateOk
    && firstScanlineStateOk
    && secondVramAccessStateOk
    && hblankOfSecondFrameStateOk
  );
}
