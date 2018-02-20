#include <list>
#include <memory>
#include <iostream>

#include "test.hpp"
#include "run-tests.hpp"
#include "instructions/short-call-test.hpp"
#include "instructions/registers-or-test.hpp"
#include "instructions/registers-and-test.hpp"
#include "instructions/decimal-adjust-test.hpp"
#include "instructions/load-immediate-8-test.hpp"
#include "instructions/stack-instructions-test.hpp"
#include "instructions/relative-jump-flag-test.hpp"
#include "instructions/registers-addition-test.hpp"
#include "instructions/two-bytes-increment-test.hpp"
#include "instructions/two-bytes-decrement-test.hpp"
#include "instructions/register-rotate-left-test.hpp"
#include "instructions/register-rotate-right-test.hpp"
#include "instructions/single-byte-increment-test.hpp"
#include "instructions/single-byte-decrement-test.hpp"
#include "instructions/registers-subtraction-test.hpp"
#include "instructions/high-byte-dereference-test.hpp"
#include "instructions/register-rotate-left-carry-test.hpp"
#include "instructions/register-rotate-right-carry-test.hpp"
#include "instructions/two-bytes-registers-addition-test.hpp"
#include "instructions/single-byte-register-to-memory-test.hpp"
#include "instructions/dereference-combined-into-single-test.hpp"
#include "instructions/write-two-bytes-register-to-address-test.hpp"

using namespace std;

bool runTests() {
  bool success = true;

  list<std::shared_ptr<Test>> tests;

  tests.push_back(make_shared<ShortCallTest>());
  tests.push_back(make_shared<DecimalAdjustTest>());
  tests.push_back(make_shared<LoadImmediate8Test>());
  tests.push_back(make_shared<RelativeJumpFlagTest>());
  tests.push_back(make_shared<StackInstructionsTest>());
  tests.push_back(make_shared<TwoBytesIncrementTest>());
  tests.push_back(make_shared<RegistersAdditionTest>());
  tests.push_back(make_shared<TwoBytesDecrementTest>());
  tests.push_back(make_shared<RegisterRotateLeftTest>());
  tests.push_back(make_shared<SingleByteIncrementTest>());
  tests.push_back(make_shared<SingleByteDecrementTest>());
  tests.push_back(make_shared<RegisterRotateRightTest>());
  tests.push_back(make_shared<HighByteDereferenceTest>());
  tests.push_back(make_shared<RegistersSubtractionTest>());
  tests.push_back(make_shared<RegisterRotateLeftCarryTest>());
  tests.push_back(make_shared<RegisterRotateRightCarryTest>());
  tests.push_back(make_shared<TwoBytesRegistersAdditionTest>());
  tests.push_back(make_shared<SingleByteRegisterToMemoryTest>());
  tests.push_back(make_shared<DereferenceCombinedIntoSingleTest>());
  tests.push_back(make_shared<WriteTwoBytesRegisterToAddressTest>());

  for (auto &&test: tests) {
    if (!test->run()) {
      success = false;

      cout << "Failure: " << test->name << endl;
    }
  }

  return success;
}
