#include <cstring>
#include <cstdint>

#include "mmu.hpp"
#include "../../bit.hpp"
#include "../gameboy.hpp"
#include "../timers/timer.hpp"
#include "timer-control-register.hpp"
#include "display-control-register.hpp"

constexpr uint16_t dmaControlRegister    = 0xff46;
constexpr uint16_t scanlineRegister      = 0xff44;
constexpr uint16_t oamStart              = 0xfe00;

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
}

uint16_t Mmu::popWordFromStack(Gameboy &gameboy) {
  const auto value = readWord(gameboy, gameboy.cpu.sp);

  gameboy.cpu.sp += 2;

  return value;
}

uint8_t Mmu::popByteFromStack(Gameboy &gameboy) {
  const auto value = read(gameboy, gameboy.cpu.sp);

  gameboy.cpu.sp++;

  return value;
}

void Mmu::write(Gameboy &gameboy, uint16_t address, uint8_t byte) {
  if (Mmu::inRom(address)) {
    return;
  }

  if (address == dmaControlRegister) {
    oamDmaTransfer(gameboy, byte);
  } else if (Mmu::inShadowRam(address)) {
    memory[Mmu::convertShadowRamAddressToRamAddress(address)] = byte;
  } else if (address == scanlineRegister) {
    gameboy.gpu.displayStartTick = OptionalTick(gameboy.cpu.ticks);
  } else if (address == timerCounterAddress) {
    memory[timerCounterAddress] = 0;

    gameboy.timer.resetTimer(gameboy.cpu.ticks);
  } else if (address == dividerAddress) {
    memory[dividerAddress] = 0;

    gameboy.timer.resetDivider(gameboy.cpu.ticks);
  } else {
    memory[address] = byte;
  }
}

uint16_t Mmu::readWord(const Gameboy &gameboy, uint16_t address) const {
  const auto firstByte  = read(gameboy, address);
  const auto secondByte = read(gameboy, address + 1);

  return firstByte | (secondByte << 8);
}

void Mmu::writeWord(Gameboy &gameboy, uint16_t address, const uint16_t word) {
  write(gameboy, address, word & lowByteMask);
  write(gameboy, address + 1, (word & highByteMask) >> 8);
}

void Mmu::pushWordToStack(Gameboy &gameboy, uint16_t value) {
  gameboy.cpu.sp -= 2;

  writeWord(gameboy, gameboy.cpu.sp, value);
}

void Mmu::pushByteToStack(Gameboy &gameboy, uint8_t value) {
  write(gameboy, gameboy.cpu.sp, value);

  gameboy.cpu.sp--;
}

uint8_t Mmu::readDisplayControlRegister(const Gameboy &gameboy) const {
  return read(gameboy, DisplayControlRegister::address);
}

uint8_t Mmu::read(const Gameboy &gameboy, uint16_t address) const {
  if (inShadowRam(address)) {
    return memory[Mmu::convertShadowRamAddressToRamAddress(address)];
  } else if (address == scanlineRegister) {
    return gameboy.gpu.getScanlineOfTick(gameboy.cpu.ticks);
  } else if (address == dividerAddress) {
    return gameboy.timer.getDividerOfTick(gameboy.cpu.ticks);
  }

  return memory[address];
}

void Mmu::sideEffectFreeWrite(uint16_t address, uint8_t value) {
  memory[address] = value;
}

/*
* See http://bgb.bircd.org/pandocs.htm#lcdoamdmatransfers
* and http://www.codeslinger.co.uk/pages/projects/gameboy/dma.html
*/
void Mmu::oamDmaTransfer(Gameboy &gameboy, uint8_t codedAddress) {
  constexpr uint8_t divisor     = 160;
  constexpr uint8_t bytesToCopy = 160;

  const uint16_t decodedAddress = codedAddress * divisor;

  for (auto i = 0; i < bytesToCopy; i++) {
    write(gameboy, oamStart + i, read(gameboy, decodedAddress + i));
  }
}
