#ifndef REGISTERS_AND_TEST_HPP
#define REGISTERS_AND_TEST_HPP

#include "../test.hpp"

struct RegistersAndTest: Test {
  RegistersAndTest();

  bool run() override;
};

#endif
