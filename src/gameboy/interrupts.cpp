#include <cstdint>
#include <array>

#include "gameboy.hpp"
#include "interrupts.hpp"

constexpr uint16_t configurationRegister = 0xffff;
constexpr uint16_t requestRegister       = 0xff0f;

constexpr uint16_t joypadBit = 3;
constexpr uint16_t vblankBit = 0;
constexpr uint16_t timerBit  = 2;
constexpr uint16_t lcdBit    = 1;

constexpr uint16_t vblankRoutineAddress = 0x40;
constexpr uint16_t joypadRoutineAddress = 0x60;
constexpr uint16_t timerRoutineAddress  = 0x50;
constexpr uint16_t lcdRoutineAddress    = 0x48;

constexpr uint16_t routineAddresses[] = {
  vblankRoutineAddress, lcdRoutineAddress,
  timerRoutineAddress,  joypadRoutineAddress
};

Interrupts::Interrupts() {
  reset();
}

void Interrupts::reset() {
  inInterrupt = false;
  enabled     = true;
}

void Interrupts::requestInterrupt(Gameboy &gameboy, const uint8_t bit) {
  gameboy.mmu.write(gameboy, requestRegister, setBit(
    gameboy.mmu.read(gameboy, requestRegister),
    bit,
    true
  ));
}

void Interrupts::process(Gameboy &gameboy) {
  if (!enabled || inInterrupt) {
    return;
  }

  const auto request       = gameboy.mmu.read(gameboy, requestRegister);
  const auto configuration = gameboy.mmu.read(gameboy, configurationRegister);

  for (auto bit = 0; bit < 4; bit++) {
    if (getBit(request, bit) && getBit(configuration, bit)) {
      gameboy.cpu.call(gameboy, routineAddresses[bit]);

      gameboy.mmu.write(gameboy, requestRegister, setBit(request, bit, false));

      return;
    }
  }
}

void Interrupts::requestLcdInterrupt(Gameboy &gameboy) {
  requestInterrupt(gameboy, lcdBit);
}

void Interrupts::requestTimerInterrupt(Gameboy &gameboy) {
  requestInterrupt(gameboy, timerBit);
}

void Interrupts::requestJoypadInterrupt(Gameboy &gameboy) {
  requestInterrupt(gameboy, joypadBit);
}

void Interrupts::requestVblankInterrupt(Gameboy &gameboy) {
  requestInterrupt(gameboy, vblankBit);
}
