#ifndef MMU_HPP
#define MMU_HPP

#include <cstdint>
#include "../../bit.hpp"

struct Cpu;

struct Mmu {
  static const uint16_t ramStart = 0x8000;

  void pushWordToStack(Cpu &cpu, uint16_t value);
  void pushByteToStack(Cpu &cpu, uint8_t value);
  uint16_t popWordFromStack(Cpu &cpu);
  uint8_t popByteFromStack(Cpu &cpu);

  const uint8_t& operator[](const uint16_t address) const;
  void writeWord(uint16_t address, uint16_t word);
  void write(uint16_t address, uint8_t byte);
  uint16_t readWord(uint16_t address) const;

  static uint16_t convertShadowRamAddressToRamAddress(uint16_t address);
  static bool inShadowRam(uint16_t address);
  static bool inRom(uint16_t address);

  void reset();

  private:
    uint8_t memory[maxUint16];
};

#endif
