#ifndef GPU_TIMING_TEST_HPP
#define GPU_TIMING_TEST_HPP

#include "test.hpp"

struct GpuTimingTest: Test {
  GpuTimingTest();

  bool run() override;
};

#endif
