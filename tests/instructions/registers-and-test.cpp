#include "../../src/bit.hpp"
#include "../../src/gameboy/gameboy.hpp"
#include "./registers-and-test.hpp"
#include "../../src/gameboy/cpu/instructions/dereference-and.hpp"

RegistersAndTest::RegistersAndTest(): Test("Registers AND test") {
}

bool RegistersAndTest::run() {
  DereferenceAnd instruction(&Cpu::hl);
  Gameboy        gameboy;

  gameboy.cpu.hl = 0;
  gameboy.mmu.write(gameboy, gameboy.cpu.hl, 1);
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, maxUint8);

  instruction.execute(gameboy, NULL);

  if (
    !gameboy.cpu.onlyFlagSet(Cpu::halfCarryFlag)
    || gameboy.cpu.singleByteRegister(&Cpu::af, false) != 1
  ) {
    return false;
  }

  gameboy.mmu.write(gameboy, gameboy.cpu.hl, 0);

  instruction.execute(gameboy, NULL);

  if (gameboy.cpu.af != (
    getBit(gameboy.cpu.af, Cpu::zeroFlag)
    | getBit(gameboy.cpu.af, Cpu::halfCarryFlag)
  )) {
    return false;
  }

  return true;
}
