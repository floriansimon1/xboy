#include "../../src/gameboy.hpp"
#include "stack-instructions-test.hpp"
#include "../../src/cpu/instructions/pop-word.hpp"
#include "../../src/cpu/instructions/push-word.hpp"

StackInstructionsTest::StackInstructionsTest(): Test("Stack instructions test") {
}

bool StackInstructionsTest::run() {
  PushWord push(&Cpu::hl);
  PopWord  pop(&Cpu::hl);
  Gameboy  gameboy;

  const auto value = 100;

  gameboy.cpu.hl = value;

  push.execute(gameboy, NULL);

  if (gameboy.cpu.hl != value) {
    return false;
  }

  gameboy.cpu.hl = value + 1;

  pop.execute(gameboy, NULL);

  return gameboy.cpu.hl == value;
}
