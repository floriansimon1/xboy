#include "../../bit.hpp"
#include "../gameboy.hpp"
#include "lcd-status-register.hpp"

constexpr uint8_t modeFirstBit              = 0;
constexpr uint8_t scanlineCoincidenceBit    = 2;
constexpr uint8_t scanlineInterruptFlagBit  = 6;
constexpr uint8_t firstModeInterruptFlagBit = 3;

constexpr uint16_t lcdStatusAddress         = 0xff41;
constexpr uint16_t interruptScanlineAddress = 0xff45;

LcdStatusRegister::LcdStatusRegister(const Gameboy &gameboy):
  value(gameboy.mmu.read(gameboy, lcdStatusAddress))
{
}

bool LcdStatusRegister::interruptOnModeChange(const Gpu::Mode mode) const {
  if (mode == Gpu::Mode::VramAccess) {
    return false;
  }

  // Bits 3-5 correspond to interrupt enabled flags of mode 0-2.
  return getBit(value, mode + firstModeInterruptFlagBit);
}

bool LcdStatusRegister::shouldTriggerScanlineInterrupt(const Gameboy &gameboy, Scanline currentScanline) const {
  return getBit(value, scanlineInterruptFlagBit) && isInterruptScanline(gameboy, currentScanline);
}

void LcdStatusRegister::update(Gameboy &gameboy, Gpu::Mode mode, Scanline currentScanline) const {
  const auto updatedValue = setBit(
    setBit(
      setBit(value, modeFirstBit, mode & 1),
      modeFirstBit + 1,
      mode & 0b10
    ),

    scanlineCoincidenceBit,
    isInterruptScanline(gameboy, currentScanline)
  );

  gameboy.mmu.write(gameboy, lcdStatusAddress, updatedValue);
}

bool LcdStatusRegister::isInterruptScanline(const Gameboy &gameboy, Scanline currentScanline) const {
  return currentScanline == gameboy.mmu.read(gameboy, interruptScanlineAddress);
}
