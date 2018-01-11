#include "../../cpu/instructions/single-byte-register-to-memory.hpp"
#include "single-byte-register-to-memory-test.hpp"
#include "../../gameboy.hpp"

SingleByteRegisterToMemoryTest::SingleByteRegisterToMemoryTest():
  Test("Single-byte register to memory instruction")
{
}

bool SingleByteRegisterToMemoryTest::run() {
  Gameboy                    gameboy;
  SingleByteRegisterToMemory instruction(&Cpu::bc, &Cpu::af, false);

  gameboy.mmu.memory[0] = 0;
  gameboy.cpu.bc        = 0;

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 1);

  instruction.execute(gameboy, gameboy.mmu.memory);

  return gameboy.mmu.memory[0] == 1;
}
