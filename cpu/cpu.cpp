#include <iostream>

#include "cpu.hpp"
#include "../bit.hpp"
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

  std::cout << instruction->toString() << std::endl;

  instruction->execute(gameboy, data);

  pc    += instruction->totalSize();
  ticks += instruction->ticks;
}

uint16_t Cpu::twoBytesRegister(CpuRegisterPointer cpuRegister) {
  return this->*cpuRegister;
}

uint8_t Cpu::singleByteRegister(CpuRegisterPointer cpuRegister, bool low) {
  const auto fullRegisterValue = twoBytesRegister(cpuRegister);

  if (low) {
    return fullRegisterValue & 0b11111111;
  }

  return fullRegisterValue >> 8;
}

void Cpu::setZeroFlag(bool enable) {
  af = setBit(af, 7, enable);
}

void Cpu::setCarryFlag(bool enable) {
  af = setBit(af, 4, enable);
}

void Cpu::setSubtractFlag(bool enable) {
  af = setBit(af, 6, enable);
}

void Cpu::setHalfCarryFlag(bool enable) {
  af = setBit(af, 5, enable);
}

