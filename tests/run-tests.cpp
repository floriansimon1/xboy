#include <list>
#include <memory>
#include <iostream>

#include "test.hpp"
#include "run-tests.hpp"
#include "./instructions/two-bytes-increment-test.hpp"
#include "./instructions/two-bytes-decrement-test.hpp"

using namespace std;

bool runTests() {
  bool success = true;

  list<std::shared_ptr<Test>> tests;

  tests.push_back(make_shared<TwoBytesIncrementTest>());
  tests.push_back(make_shared<TwoBytesDecrementTest>());

  for (auto &&test: tests) {
    if (!test->run()) {
      success = false;

      cout << "Failure: " << test->name << endl;
    }
  }

  return success;
}
