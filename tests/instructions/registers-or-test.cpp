#include "../../src/bit.hpp"
#include "../../src/gameboy.hpp"
#include "./registers-or-test.hpp"
#include "../../src/cpu/instructions/dereference-or.hpp"

RegistersOrTest::RegistersOrTest(): Test("Registers AND test") {
}

bool RegistersOrTest::run() {
  return runOrTests() && runXorTests();
}

bool RegistersOrTest::runOrTests() const {
  DereferenceOr instruction(&Cpu::hl, false);
  Gameboy       gameboy;

  gameboy.cpu.hl = 0;
  gameboy.mmu.write(gameboy.cpu.hl, 1);
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 0);

  instruction.execute(gameboy, NULL);

  if (gameboy.cpu.af != getBit(gameboy.cpu.af, Cpu::zeroFlag)) {
    return false;
  }

  gameboy.mmu.write(gameboy.cpu.hl, maxUint8);

  instruction.execute(gameboy, NULL);

  if (gameboy.cpu.af != maxUint8 << 8) {
    return false;
  }

  return true;
}

bool RegistersOrTest::runXorTests() const {
  DereferenceOr instruction(&Cpu::hl, true);
  Gameboy       gameboy;

  gameboy.cpu.hl = 0;
  gameboy.mmu.write(gameboy.cpu.hl, 1);
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 0);

  instruction.execute(gameboy, NULL);

  if (gameboy.cpu.af != getBit(gameboy.cpu.af, Cpu::zeroFlag)) {
    return false;
  }

  gameboy.mmu.write(gameboy.cpu.hl, 0b11);
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 0b10);

  instruction.execute(gameboy, NULL);

  if (gameboy.cpu.af != 1 << 8) {
    return false;
  }

  return true;
}
