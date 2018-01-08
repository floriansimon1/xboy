#include <iostream>
#include <cstdlib>
#include <string>

#include "gameboy.hpp"

int main(int argc, char **argv) {
  Gameboy gameboy;

  gameboy.mmu.memory[0] = 1;
  gameboy.mmu.memory[1] = 0;
  gameboy.mmu.memory[2] = 100;

  gameboy.tick();

  const bool executed = gameboy.cpu.bc == 100;

  const std::string message = (
    executed
    ? "The LD bc, d16 instruction was executed: "
    : "The LD bc, d16 instruction was not executed: "
  );

  std::cout << message << gameboy.cpu.bc << std::endl;

  return executed ? EXIT_SUCCESS : EXIT_FAILURE;
}

