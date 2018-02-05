#include <iostream>

#include "../../src/cpu/instructions/register-rotate-right.hpp"
#include "register-rotate-right-test.hpp"
#include "../../src/gameboy.hpp"

RegisterRotateRightTest::RegisterRotateRightTest():
  Test("Register rotate right carry")
{
}

bool RegisterRotateRightTest::run() {
  Gameboy             gameboy;
  RegisterRotateRight instruction(&Cpu::af, false);

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 1 << 7);

  for (auto i = 0; i < 7; i++) {
    instruction.execute(gameboy, gameboy.mmu.memory);

    const auto value = gameboy.cpu.singleByteRegister(&Cpu::af, false);

    if (value != (1 << (7 - i - 1)) || gameboy.cpu.anyFlagSet()) {
      std::cout << "No carry #" << i << '\n'
                << "Value: " << (unsigned int) value << '\n'
                << "Flags: " << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true) << std::endl;

      return false;
    }
  }

  instruction.execute(gameboy, gameboy.mmu.memory);

  const auto value = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  if (value || !gameboy.cpu.onlyFlagSet(Cpu::carryFlag)) {
    std::cout << "Carry\n"
              << "Value: " << (unsigned int) value << '\n'
              << "Flags: " << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true) << std::endl;

    return false;
  }

  return true;
}
