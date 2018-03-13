#include <cstring>
#include <cstdint>

#include "mmu.hpp"
#include "../bit.hpp"
#include "../bios.hpp"
#include "../cpu/cpu.hpp"

void Mmu::reset() {
  memset(memory, 0, sizeof(memory));
  memcpy(memory, bios, sizeof(bios));
}

uint16_t Mmu::popWordFromStack(Cpu &cpu) {
  const auto value = readWord(cpu.sp);

  cpu.sp += 2;

  return value;
}

uint8_t Mmu::popByteFromStack(Cpu &cpu) {
  const auto value = (*this)[cpu.sp];

  cpu.sp++;

  return value;
}

void Mmu::write(uint16_t address, uint8_t byte) {
  memory[address] = byte;
}

uint16_t Mmu::readWord(uint16_t address) const {
  const auto firstByte  = (*this)[address];
  const auto secondByte = (*this)[address + 1];

  return firstByte | (secondByte << 8);
}

void Mmu::writeWord(uint16_t address, const uint16_t word) {
  write(address, word & lowByteMask);
  write(address + 1, (word & highByteMask) >> 8);
}

void Mmu::pushWordToStack(Cpu &cpu, uint16_t value) {
  cpu.sp -= 2;

  writeWord(cpu.sp, value);
}

void Mmu::pushByteToStack(Cpu &cpu, uint8_t value) {
  write(cpu.sp, value);

  cpu.sp--;
}

const uint8_t& Mmu::operator[](const uint16_t address) const {
  return memory[address];
}
