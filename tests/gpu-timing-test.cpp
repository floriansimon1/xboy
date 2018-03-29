#include "../src/gameboy/gpu/gpu.hpp"
#include "gpu-timing-test.hpp"

#include <iostream>

GpuTimingTest::GpuTimingTest(): Test("GPU timing test") {
}

bool GpuTimingTest::run() {
  const auto noScanline                 = getScanlineOfTick(OptionalTick(), 0);
  const auto firstScanlineOfFirstFrame  = getScanlineOfTick(OptionalTick(0), 0);
  const auto firstScanlineOfSecondFrame = getScanlineOfTick(OptionalTick(0), ticksPerFrame);
  const auto secondScanline             = getScanlineOfTick(OptionalTick(0), ticksPerScanline);

  const auto ok = (
    !noScanline
    && secondScanline.value() == 1
    && firstScanlineOfFirstFrame.value() == 0
    && firstScanlineOfSecondFrame.value() == 0
  );

  if (!ok) {
    std::cout << "secondScanline: " << secondScanline.value() << "\n"
              << "noScanline: " << (noScanline ? "present" : "absent") << "\n"
              << "firstScanlineOfFirstFrame: " << firstScanlineOfFirstFrame.value() << "\n"
              << "firstScanlineOfSecondFrame: " << firstScanlineOfSecondFrame.value() << "\n"
              << std::endl;
  }

  return ok;
}
