#include "joypad.hpp"
#include "../gameboy.hpp"

constexpr uint8_t  processDirectionalBit = 4;
constexpr uint8_t  processButtonsBit     = 5;
constexpr uint16_t joypadStatusAddress   = 0xff00;

Joypad::Joypad() {
  reset();
}

void Joypad::reset() {
  aWasPressed      = false;
  bWasPressed      = false;
  upWasPressed     = false;
  downWasPressed   = false;
  leftWasPressed   = false;
  rightWasPressed  = false;
  startWasPressed  = false;
  selectWasPressed = false;
}

// Everything gets negated, because for the Gameboy, a keypress is indicated by a 0, not a 1.
void Joypad::process(Gameboy &gameboy, const InputMedium &input) {
  const bool processDirectionalKeys = getBit(
    gameboy.mmu.read(gameboy, joypadStatusAddress),
    processDirectionalBit
  );

  // Right or A.
  const bool oldBit0 = !(processDirectionalKeys ? rightWasPressed : aWasPressed);
  const bool newBit0 = !(processDirectionalKeys ? input.rightIsPressed() : input.aIsPressed());

  // Left or B.
  const bool oldBit1 = !(processDirectionalKeys ? leftWasPressed : bWasPressed);
  const bool newBit1 = !(processDirectionalKeys ? input.leftIsPressed() : input.bIsPressed());

  // Up or Select.
  const bool oldBit2 = !(processDirectionalKeys ? upWasPressed : selectWasPressed);
  const bool newBit2 = !(processDirectionalKeys ? input.upIsPressed() : input.selectIsPressed());

  // Down or Start.
  const bool oldBit3 = !(processDirectionalKeys ? downWasPressed : startWasPressed);
  const bool newBit3 = !(processDirectionalKeys ? input.downIsPressed() : input.startIsPressed());

  const bool triggerInterrupt = (
    (oldBit0 && !newBit0)
    || (oldBit1 && !newBit1)
    || (oldBit2 && !newBit2)
    || (oldBit3 && !newBit3)
  );

  if (triggerInterrupt) {
    gameboy.cpu.unhalt();

    gameboy.interrupts.requestJoypadInterrupt(gameboy);
  }

  gameboy.mmu.write(gameboy, joypadStatusAddress, (
    newBit0
    | (newBit1 << 1)
    | (newBit2 << 2)
    | (newBit3 << 3)
    | (processDirectionalKeys << processDirectionalBit)
    | (!processDirectionalKeys << processButtonsBit)
  ));

  aWasPressed      = input.aIsPressed();
  bWasPressed      = input.bIsPressed();
  upWasPressed     = input.upIsPressed();
  downWasPressed   = input.downIsPressed();
  leftWasPressed   = input.leftIsPressed();
  rightWasPressed  = input.rightIsPressed();
  startWasPressed  = input.startIsPressed();
  selectWasPressed = input.selectIsPressed();
}
