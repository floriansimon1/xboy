#include <iostream>
#include <cstdlib>

#include "./tests/run-tests.hpp"

int main(int argc, char **argv) {
  bool success = runTests();

  if (success) {
    std::cout << "All tests pass!" << std::endl;
  }

  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
