#ifndef LCD_STATUS_REGISTER_HPP
#define LCD_STATUS_REGISTER_HPP

#include <cstdint>

#include "../gpu/gpu-mode.hpp"

struct LcdStatusRegister {
  LcdStatusRegister(const Gameboy &gameboy);

  bool interruptOnModeChange(const Gpu::Mode mode) const;
  void update(Gameboy &gameboy, Gpu::Mode mode, Scanline currentScanline) const;
  bool shouldTriggerScanlineInterrupt(const Gameboy &gameboy, Scanline currentScanline) const;

  private:
    bool isInterruptScanline(const Gameboy &gameboy, Scanline currentScanline) const;
    const uint8_t value;
};

#endif
