#ifndef INTERRUPTS_HPP
#define INTERRUPTS_HPP

struct Gameboy;

struct Interrupts {
  Interrupts();

  void reset();
  void process(Gameboy &gameboy);
  void requestLcdInterrupt(Gameboy &gameboy);
  void requestTimerInterrupt(Gameboy &gameboy);
  void requestJoypadInterrupt(Gameboy &gameboy);
  void requestVblankInterrupt(Gameboy &gameboy);

  bool inInterrupt;
  bool enabled;

  private:
    void requestInterrupt(Gameboy &gameboy, const uint8_t bit);
};

#endif
