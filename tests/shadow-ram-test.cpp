#include <iostream>

#include "../src/gameboy/gameboy.hpp"
#include "shadow-ram-test.hpp"

ShadowRamTest::ShadowRamTest(): Test("Shadow RAM test") {
}

bool ShadowRamTest::run() {
  Gameboy gameboy;

  gameboy.mmu.write(gameboy, 0xc000, 3);
  gameboy.mmu.write(gameboy, 0xe001, 4);

  gameboy.mmu.writeWord(gameboy, 0xc002, 5);
  gameboy.mmu.writeWord(gameboy, 0xe004, 6);

  if (
    gameboy.mmu.read(gameboy, 0xc000) != gameboy.mmu.read(gameboy, 0xe000)
    || gameboy.mmu.read(gameboy, 0xc001) != gameboy.mmu.read(gameboy, 0xe001)
    || gameboy.mmu.readWord(gameboy, 0xc002) != gameboy.mmu.readWord(gameboy, 0xe002)
    || gameboy.mmu.readWord(gameboy, 0xc004) != gameboy.mmu.readWord(gameboy, 0xe004)
  ) {
    std::cout << (unsigned int) gameboy.mmu.read(gameboy, 0xc000) << " ≠ " << (unsigned int) gameboy.mmu.read(gameboy, 0xe000) << "\n"
              << (unsigned int) gameboy.mmu.read(gameboy, 0xc001) << " ≠ " << (unsigned int) gameboy.mmu.read(gameboy, 0xe001) << "\n"
              << (unsigned int) gameboy.mmu.readWord(gameboy, 0xc002) << " ≠ " << (unsigned int) gameboy.mmu.readWord(gameboy, 0xe002) << "\n"
              << (unsigned int) gameboy.mmu.readWord(gameboy, 0xc004) << " ≠ " << (unsigned int) gameboy.mmu.readWord(gameboy, 0xe004)
              << std::endl;

    return false;
  }

  return true;
}
