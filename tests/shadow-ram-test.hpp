#ifndef SHADOW_RAM_TEST_HPP
#define SHADOW_RAM_TEST_HPP

#include "test.hpp"

struct ShadowRamTest: Test {
  ShadowRamTest();

  bool run() override;
};

#endif
