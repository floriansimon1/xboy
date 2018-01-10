#include <list>
#include <memory>
#include <iostream>

#include "test.hpp"
#include "run-tests.hpp"

using namespace std;

bool runTests() {
  bool success = true;

  list<std::shared_ptr<Test>> tests;

  for (auto &&test: tests) {
    if (!test->run()) {
      success = false;

      cout << "Failure: " << test->name << endl;
    }
  }

  return success;
}
