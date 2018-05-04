#ifndef MMU_HPP
#define MMU_HPP

#include <cstdint>
#include "../../bit.hpp"

struct Gameboy;

struct Mmu {
  static const uint16_t ramStart = 0x8000;

  void pushWordToStack(Gameboy &gameboy, uint16_t value);
  void pushByteToStack(Gameboy &gameboy, uint8_t value);
  uint16_t popWordFromStack(Gameboy &gameboy);
  uint8_t popByteFromStack(Gameboy &gameboy);

  uint16_t readWord(const Gameboy &gameboy, uint16_t address) const;
  uint8_t read(const Gameboy &gameboy, uint16_t address) const;
  bool inBios() const;

  void writeWord(Gameboy &gameboy, uint16_t address, uint16_t word);
  void write(Gameboy &gameboy, uint16_t address, uint8_t byte);
  void sideEffectFreeWrite(uint16_t address, uint8_t byte);

  static uint16_t convertShadowRamAddressToRamAddress(uint16_t address);
  static bool inFirstRomBank(uint16_t address);
  static bool inShadowRam(uint16_t address);
  static bool inRom(uint16_t address);

  void reset();

  uint8_t readDisplayControlRegister(const Gameboy &gameboy) const;

  private:
    uint8_t memory[maxUint16];

    void oamDmaTransfer(Gameboy &gameboy, uint8_t codedAddress);
};

#endif
