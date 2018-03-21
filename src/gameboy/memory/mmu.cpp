#include <cstring>
#include <cstdint>

#include "mmu.hpp"
#include "../bios.hpp"
#include "../../bit.hpp"
#include "../cpu/cpu.hpp"

constexpr uint16_t displayControlRegister = 0xff40;
constexpr uint8_t  displayEnabledBit      = 7;

bool Mmu::inShadowRam(uint16_t address) {
  return address >= 0xe000 && address < 0xfe00;
}

bool Mmu::inRom(uint16_t address) {
  return address < 0x8000;
}

uint16_t Mmu::convertShadowRamAddressToRamAddress(uint16_t address) {
  return address - 0x2000;
}

void Mmu::reset() {
  memset(memory, 0, maxUint16);
  memcpy(memory, bios, biosLength);
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
  if (Mmu::inRom(address)) {
    return;
  }

  if (Mmu::inShadowRam(address)) {
    memory[Mmu::convertShadowRamAddressToRamAddress(address)] = byte;
  }

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

bool Mmu::displayEnabled() const {
  return getBit((*this)[displayControlRegister], displayEnabledBit);
}

const uint8_t& Mmu::operator[](const uint16_t address) const {
  if (inShadowRam(address)) {
    return memory[Mmu::convertShadowRamAddressToRamAddress(address)];
  }

  return memory[address];
}
