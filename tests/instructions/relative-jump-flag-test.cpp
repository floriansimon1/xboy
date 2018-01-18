#include <iostream>

#include "../../gameboy.hpp"
#include "relative-jump-flag-test.hpp"
#include "../../cpu/instructions/relative-jump-flag.hpp"

RelativeJumpFlagTest::RelativeJumpFlagTest():
  Test("Conditional relative jump instruction")
{
}

bool RelativeJumpFlagTest::run() {
  Gameboy          gameboy;
  RelativeJumpFlag onZero(Cpu::zeroFlag, true);
  RelativeJumpFlag negated(Cpu::zeroFlag, false);

  int8_t jump = 127;

  const auto asByte = static_cast<uint8_t>(jump);

  gameboy.cpu.af = 0;
  gameboy.cpu.pc = 0;

  gameboy.cpu.setCarryFlag(true);

  onZero.execute(gameboy, &asByte);

  if (gameboy.cpu.pc) {
    std::cout << "1 - pc: " << (unsigned int) gameboy.cpu.pc
              << ", Z: " << gameboy.cpu.getZeroFlag()
              << std::endl;

    return false;
  }

  gameboy.cpu.af = 0;
  gameboy.cpu.pc = 0;

  gameboy.cpu.setCarryFlag(true);

  negated.execute(gameboy, &asByte);

  if (gameboy.cpu.pc != asByte) {
    std::cout << "2 - pc: " << (unsigned int) gameboy.cpu.pc
              << ", Z: " << gameboy.cpu.getZeroFlag()
              << std::endl;

    return false;
  }

  gameboy.cpu.af = 0;
  gameboy.cpu.pc = 0;

  gameboy.cpu.setZeroFlag(true);

  onZero.execute(gameboy, &asByte);

  if (gameboy.cpu.pc != asByte) {
    std::cout << "3 - pc: " << (unsigned int) gameboy.cpu.pc
              << ", Z: " << gameboy.cpu.getZeroFlag()
              << std::endl;

    return false;
  }

  gameboy.cpu.af = 0;
  gameboy.cpu.pc = 0;

  gameboy.cpu.setZeroFlag(true);

  negated.execute(gameboy, &asByte);

  if (gameboy.cpu.pc) {
    std::cout << "4 - pc: " << (unsigned int) gameboy.cpu.pc
              << ", Z: " << gameboy.cpu.getZeroFlag()
              << std::endl;

    return false;
  }

  return true;
}
