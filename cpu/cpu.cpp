#include "cpu.hpp"
#include "../gameboy.hpp"

Cpu::Cpu() {
  reset();
}

void Cpu::reset() {
  ticks = 0;

  af = 0;
  bc = 0;
  de = 0;
  hl = 0;
  sp = 0;
  pc = 0;
}

void Cpu::process(Gameboy &gameboy) {
  const auto firstOpcodeByte = gameboy.mmu.memory[pc];

  const auto readSecondByte = Instruction::isExtendedInstruction(firstOpcodeByte);

  const auto instruction = table.get(
    readSecondByte,
    readSecondByte ? gameboy.mmu.memory[pc + 1] : firstOpcodeByte
  );

  const auto data = (
    instruction->dataSize
    ? gameboy.mmu.memory + pc + instruction->opcodeSize
    : NULL
  );

  instruction->execute(gameboy, data);

  pc    += instruction->totalSize();
  ticks += instruction->ticks;
}

