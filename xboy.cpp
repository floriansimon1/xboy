#include <iostream>
#include <cstdlib>
#include <string>

#include "gameboy.hpp"

int main(int argc, char **argv) {
  Gameboy gameboy;

  gameboy.mmu.memory[0] = 0;

  gameboy.tick();

  const bool executed = gameboy.mmu.memory[10] == 100;

  const std::string message = (
    executed
    ? "The NOP instruction was executed"
    : "The NOP instruction was not executed"
  );

  std::cout << message << std::endl;

  return executed ? EXIT_SUCCESS : EXIT_FAILURE;
}

