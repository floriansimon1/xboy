#include <iostream>

#include "cpu.hpp"
#include "../../bit.hpp"
#include "../gameboy.hpp"

Cpu::Cpu() {
  reset();
}

void Cpu::reset() {
  ticks = 0;

  interruptsEnabled = true;
  inInterrupt       = false;

  af = 0;
  bc = 0;
  de = 0;
  hl = 0;
  sp = 0;
  pc = 0;
}

void Cpu::process(Gameboy &gameboy) {
  const auto firstOpcodeByte = gameboy.mmu[pc];

  const auto readSecondByte = Instruction::isExtendedInstruction(firstOpcodeByte);

  const auto instruction = table.get(
    readSecondByte,
    readSecondByte ? gameboy.mmu[pc + 1] : firstOpcodeByte
  );

  // We can have at most 2 bytes of data from what I've seen.
  const uint8_t data[2] = {
    gameboy.mmu[pc + instruction->opcodeSize],
    gameboy.mmu[pc + instruction->opcodeSize + 1]
  };

  std::cout << instruction->toString() << std::endl;

  ticks += instruction->ticks(gameboy);

  instruction->execute(gameboy, data);

  pc += instruction->totalSize();
}

void Cpu::setTwoBytesRegister(CpuRegisterPointer cpuRegister, uint16_t value) {
  this->*cpuRegister = value;
}

uint16_t Cpu::twoBytesRegister(CpuRegisterPointer cpuRegister) const {
  return this->*cpuRegister;
}

uint8_t Cpu::singleByteRegister(CpuRegisterPointer cpuRegister, bool low) const {
  const auto fullRegisterValue = twoBytesRegister(cpuRegister);

  if (low) {
    return fullRegisterValue & lowByteMask;
  }

  return fullRegisterValue >> 8;
}

void Cpu::clearAllFlags() {
  setSingleByteRegister(&Cpu::af, true, 0);
}

void Cpu::setZeroFlag(bool enable) {
  af = setBit(af, Cpu::zeroFlag, enable);
}

void Cpu::setCarryFlag(bool enable) {
  af = setBit(af, Cpu::carryFlag, enable);
}

void Cpu::setSubtractFlag(bool enable) {
  af = setBit(af, Cpu::subtractFlag, enable);
}

void Cpu::setHalfCarryFlag(bool enable) {
  af = setBit(af, Cpu::halfCarryFlag, enable);
}

bool Cpu::anyFlagSet() const {
  return singleByteRegister(&Cpu::af, true);
}

bool Cpu::getZeroFlag() const {
  return getBit(af, Cpu::zeroFlag);
}

bool Cpu::getCarryFlag() const {
  return getBit(af, Cpu::carryFlag);
}

bool Cpu::getSubtractFlag() const {
  return getBit(af, Cpu::subtractFlag);
}

bool Cpu::getHalfCarryFlag() const {
  return getBit(af, Cpu::halfCarryFlag);
}

bool Cpu::onlyFlagSet(unsigned short flag) const {
  return singleByteRegister(&Cpu::af, true) == (1 << flag);
}

bool Cpu::flagHasValue(unsigned short flag, bool value) const {
  return static_cast<bool>(getBit(af, flag)) == value;
}

void Cpu::setSingleByteRegister(CpuRegisterPointer cpuRegister, bool low, uint8_t value) {
  const auto registerValue = this->*cpuRegister;
  const auto otherIsLow    = !low;

  const auto otherByteMask = otherIsLow ? lowByteMask : highByteMask;

  uint16_t widerValue = low ? value : value << 8;
  uint16_t otherByte  = registerValue & otherByteMask;

  this->*cpuRegister = widerValue | otherByte;
}

const unsigned short Cpu::zeroFlag;
const unsigned short Cpu::carryFlag;
const unsigned short Cpu::subtractFlag;
const unsigned short Cpu::halfCarryFlag;
