#include <iostream>

#include "../../bit.hpp"
#include "../../gameboy.hpp"
#include "two-bytes-registers-addition-test.hpp"
#include "../../cpu/instructions/two-bytes-registers-addition.hpp"

TwoBytesRegistersAdditionTest::TwoBytesRegistersAdditionTest():
  Test("Two-bytes registers addition")
{
}

bool TwoBytesRegistersAdditionTest::executeAndCheck(
  Gameboy &gameboy,
  Instruction &instruction,
  uint16_t value,
  bool carry,
  bool subtract,
  bool halfCarry
) const {
  Cpu &cpu = gameboy.cpu;

  instruction.execute(gameboy, gameboy.mmu.memory);

  bool success = (
    cpu.de == value
    && carry == cpu.getCarryFlag()
    && subtract == cpu.getSubtractFlag()
    && halfCarry == cpu.getHalfCarryFlag()
  );

  if (!success) {
    std::cout << "Value: " << (unsigned int) cpu.de << " (expected " << value << ")\n"
              << "C: " << cpu.getCarryFlag() << " (expected " << carry << ")\n"
              << "H: " << cpu.getHalfCarryFlag() << " (expected " << halfCarry << ")\n"
              << "N: " << cpu.getSubtractFlag() << " (expected " << subtract << ")"
              << std::endl;
  }

  return success;
}

bool TwoBytesRegistersAdditionTest::run() {
  Gameboy                   gameboy;
  TwoBytesRegistersAddition instruction(&Cpu::bc, &Cpu::de);

  gameboy.cpu.de = 0;
  gameboy.cpu.bc = 0;

  if (!executeAndCheck(gameboy, instruction, 0, false, false, false)) {
    return false;
  }

  gameboy.cpu.de = lowHalfByteMask;
  gameboy.cpu.bc = 1;

  if (!executeAndCheck(gameboy, instruction, lowHalfByteMask + 1, false, false, true)) {
    return false;
  }

  gameboy.cpu.de = maxUint16;
  gameboy.cpu.bc = maxUint16;

  if (!executeAndCheck(gameboy, instruction, maxUint16 - 1, true, false, true)) {
    return false;
  }

  return true;
}
