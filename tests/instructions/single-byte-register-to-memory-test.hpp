#ifndef SINGLE_BYTE_REGISTER_TO_MEMORY_TEST_HPP
#define SINGLE_BYTE_REGISTER_TO_MEMORY_TEST_HPP

#include "../test.hpp"

struct SingleByteRegisterToMemoryTest: Test {
  SingleByteRegisterToMemoryTest();

  bool run() override;
};
#endif
