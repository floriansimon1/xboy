#ifndef DECIMAL_ADJUST_TEST_HPP
#define DECIMAL_ADJUST_TEST_HPP

#include "../test.hpp"

struct DecimalAdjustTest: Test {
  DecimalAdjustTest();

  bool run() override;

  bool testLowByteAddition() const;
  bool testHighByteAddition() const;
  bool testLowByteSubtraction() const;
  bool testHighByteSubtraction() const;
  bool testCombinedCarriesAddition() const;
  bool testCombinedCarriesSubtraction() const;
};

#endif
