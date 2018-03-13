#include "../src/memory/mmu.hpp"
#include "shadow-ram-test.hpp"

ShadowRamTest::ShadowRamTest(): Test("Shadow RAM test") {
}

bool ShadowRamTest::run() {
  Mmu memory;

  memory.write(0xc000, 3);
  memory.write(0xe001, 4);

  memory.writeWord(0xc002, 5);
  memory.writeWord(0xe004, 6);

  if (
    memory[0xc000] != memory[0xe000]
    || memory[0xc001] != memory[0xe001]
    || memory.readWord(0xc002) != memory.readWord(0xe002)
    || memory.readWord(0xc004) != memory.readWord(0xe004)
  ) {
    return false;
  }

  return true;
}
