#ifndef RETURN_FLAG_HPP
#define RETURN_FLAG_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct ReturnFlag: Instruction {
  const bool           conditional;
  const bool           negate;
  const unsigned short flag;

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  unsigned short ticks(Gameboy &gameboy) const override;
  std::string toString() const override;

  // Default values are meaningless, just meant to help creating the unconditional return.
  ReturnFlag(bool conditional, unsigned short flag = Cpu::zeroFlag, bool negate = true);

  private:
    bool shouldJump(Gameboy &gameboy) const;
};

#endif
