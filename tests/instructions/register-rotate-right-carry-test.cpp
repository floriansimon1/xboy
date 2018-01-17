#include <iostream>

#include "../../cpu/instructions/register-rotate-right-carry.hpp"
#include "register-rotate-right-carry-test.hpp"
#include "../../gameboy.hpp"

RegisterRotateRightCarryTest::RegisterRotateRightCarryTest():
  Test("Register rotate right carry")
{
}

bool RegisterRotateRightCarryTest::run() {
  Gameboy                  gameboy;
  RegisterRotateRightCarry instruction(&Cpu::af, false);

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

  if (value != (1 << 7) || !gameboy.cpu.onlyFlagSet(Cpu::carryFlag)) {
    std::cout << "Carry\n"
              << "Value: " << (unsigned int) value << '\n'
              << "Flags: " << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true) << std::endl;

    return false;
  }

  return true;
}
