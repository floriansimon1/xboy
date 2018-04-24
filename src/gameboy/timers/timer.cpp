#include "timer-frequencies.hpp"
#include "../gameboy.hpp"
#include "timer.hpp"

constexpr uint16_t resetValueAddress = 0xff06; // TMA

Timer::Timer():
  timerStart(0),
  dividerStart(0),
  lastTimerIncrementTick(0)
{
  reset();
}

void Timer::reset() {
  timerStart             = 0;
  dividerStart           = 0;
  lastTimerIncrementTick = 0;
}

void Timer::process(Gameboy &gameboy) {
  const TimerControlRegister controlRegister(gameboy);

  const auto incrementTicks = controlRegister.ticks();
  const auto timerValue     = gameboy.mmu.read(gameboy, timerCounterAddress);

  const auto willOverflow = timerValue == maxUint8;

  if (!controlRegister.timersEnabled()) {
    gameboy.mmu.write(gameboy, timerCounterAddress, 0);

    lastTimerIncrementTick = gameboy.cpu.ticks;
    timerStart             = gameboy.cpu.ticks;

    return;
  }

  // Should we increment the timer?
  if (lastTimerIncrementTick - gameboy.cpu.ticks >= incrementTicks) {
    const auto newValue = (
      willOverflow
      ? gameboy.mmu.read(gameboy, resetValueAddress)
      : timerValue + 1
    );

    // When games write to the timer counter, it's reset to 0, which is not what we want.
    gameboy.mmu.sideEffectFreeWrite(timerCounterAddress, newValue);

    lastTimerIncrementTick += incrementTicks;

    if (willOverflow) {
      gameboy.interrupts.requestTimerInterrupt(gameboy);
    }
  }
}

void Timer::resetDivider(Tick tick) {
  dividerStart = tick;
}

void Timer::resetTimer(Tick tick) {
  lastTimerIncrementTick = tick;
  timerStart             = tick;
}

uint8_t Timer::getDividerOfTick(Tick tick) const {
  // No need to divide, the truncation to 8 bits does it for us.
  return (tick - dividerStart) / dividerTicks;
}
