#include <iostream>
#include <cstdlib>
#include <string>

#include "gameboy.hpp"

int main(int argc, char **argv) {
  Gameboy gameboy;

  gameboy.cpu.af        = 0b100000000;
  gameboy.cpu.bc        = 1;
  gameboy.mmu.memory[0] = 2;

  gameboy.tick();

  const bool executed = gameboy.mmu.memory[1] == 1;

  const std::string message = (
    executed
    ? "The instruction was executed: "
    : "The instruction was not executed: "
  );

  std::cout << message << (unsigned int) gameboy.mmu.memory[1] << std::endl;

  return executed ? EXIT_SUCCESS : EXIT_FAILURE;
}

