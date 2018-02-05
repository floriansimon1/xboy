#include <cstring>
#include <cstdint>

#include "mmu.hpp"
#include "../bios.hpp"
#include "../cpu/cpu.hpp"

void Mmu::reset() {
  memset(memory, 0, sizeof(memory));
  memcpy(memory, bios, sizeof(bios));
}

uint16_t Mmu::popTwoBytesFromStack(Cpu &cpu) {
  const auto value = *reinterpret_cast<uint16_t*>(memory + cpu.sp);

  cpu.sp += 2;

  return value;
}

uint8_t Mmu::popByteFromStack(Cpu &cpu) {
  const auto value = memory[cpu.sp];

  cpu.sp++;

  return value;
}

void Mmu::pushTwoBytesToStack(Cpu &cpu, uint16_t value) {
  cpu.sp -= 2;

  *reinterpret_cast<uint16_t*>(memory + cpu.sp) = value;
}

void Mmu::pushByteToStack(Cpu &cpu, uint8_t value) {
  memory[cpu.sp] = value;

  cpu.sp--;
}
