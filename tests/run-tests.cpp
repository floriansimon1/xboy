#include <list>
#include <memory>
#include <iostream>

#include "test.hpp"
#include "run-tests.hpp"
#include "instructions/load-immediate-8-test.hpp"
#include "instructions/two-bytes-increment-test.hpp"
#include "instructions/two-bytes-decrement-test.hpp"
#include "instructions/single-byte-increment-test.hpp"
#include "instructions/single-byte-decrement-test.hpp"
#include "instructions/register-rotate-left-carry-test.hpp"
#include "instructions/two-bytes-registers-addition-test.hpp"
#include "instructions/single-byte-register-to-memory-test.hpp"
#include "instructions/dereference-combined-into-single-test.hpp"
#include "instructions/write-two-bytes-register-to-address-test.hpp"

using namespace std;

bool runTests() {
  bool success = true;

  list<std::shared_ptr<Test>> tests;

  tests.push_back(make_shared<LoadImmediate8Test>());
  tests.push_back(make_shared<TwoBytesIncrementTest>());
  tests.push_back(make_shared<TwoBytesDecrementTest>());
  tests.push_back(make_shared<SingleByteIncrementTest>());
  tests.push_back(make_shared<SingleByteDecrementTest>());
  tests.push_back(make_shared<RegisterRotateLeftCarryTest>());
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
