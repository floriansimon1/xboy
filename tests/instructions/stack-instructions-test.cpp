#include "../../src/gameboy.hpp"
#include "stack-instructions-test.hpp"
#include "../../src/cpu/instructions/pop-two-bytes.hpp"
#include "../../src/cpu/instructions/push-two-bytes.hpp"

StackInstructionsTest::StackInstructionsTest(): Test("Stack instructions test") {
}

bool StackInstructionsTest::run() {
  PushTwoBytes push(&Cpu::hl);
  PopTwoBytes  pop(&Cpu::hl);
  Gameboy      gameboy;

  const auto value = 100;

  gameboy.cpu.hl = value;

  push.execute(gameboy, gameboy.mmu.memory);

  if (gameboy.cpu.hl != value) {
    return false;
  }

  gameboy.cpu.hl = value + 1;

  pop.execute(gameboy, gameboy.mmu.memory);

  return gameboy.cpu.hl == value;
}
