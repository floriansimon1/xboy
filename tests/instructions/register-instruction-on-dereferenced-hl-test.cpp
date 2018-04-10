#include <iostream>

#include "../../src/gameboy/gameboy.hpp"
#include "register-instruction-on-dereferenced-hl-test.hpp"
#include "../../src/gameboy/cpu/instructions/register-rotate-left-carry.hpp"
#include "../../src/gameboy/cpu/instructions/register-instruction-on-dereferenced-hl.hpp"

RegisterInstructionOnDereferencedHlTest::RegisterInstructionOnDereferencedHlTest():
  Test("Executing a register instruction on dereferenced-HL")
{
}

bool RegisterInstructionOnDereferencedHlTest::run() {
  Gameboy                                                      gameboy;
  RegisterInstructionOnDereferencedHl<RegisterRotateLeftCarry> instruction;
  RegisterRotateLeftCarry                                      rlc(&Cpu::de, true);

  if (instruction.toString() != "RLC (HL)") {
    std::cout << "Wrong mnemonic: " << instruction.toString() << std::endl;

    return false;
  }

  const uint8_t  dummy   = 0;
  const uint16_t input   = 123;
  const uint16_t address = Mmu::ramStart;

  gameboy.cpu.af = 0;
  gameboy.cpu.de = input;
  gameboy.cpu.hl = address;

  gameboy.mmu.write(gameboy, gameboy.cpu.hl, input);

  rlc.execute(gameboy, &dummy);

  const auto expectedAf     = gameboy.cpu.af;
  const auto expectedOutput = gameboy.cpu.de;

  gameboy.cpu.af = 0;

  instruction.execute(gameboy, &dummy);

  if (
    gameboy.cpu.hl == address
    && gameboy.cpu.af == expectedAf
    && gameboy.mmu.read(gameboy, gameboy.cpu.hl) == expectedOutput
  ) {
    return true;
  }

  std::cout << "HL: " << (unsigned int) gameboy.cpu.hl << " (" << (unsigned int) address << "), "
            << "AF: " << (unsigned int) gameboy.cpu.af << " (" << (unsigned int) expectedAf << "), "
            << "Out: " << (unsigned int) gameboy.mmu.read(gameboy, gameboy.cpu.hl) << " (" << (unsigned int) expectedOutput << ')'
            << std::endl;

  return false;
}
