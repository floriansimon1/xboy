#ifndef JUMP_HPP
#define JUMP_HPP

#include "../instruction.hpp"
#include "../../gameboy.hpp"

struct Jump: Instruction {
  const bool           conditional;
  const bool           negate;
  const unsigned short flag;

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  unsigned short ticks(Gameboy &gameboy) const override;
  std::string toString() const override;

  // Default values are meaningless, just meant to help creating the unconditional jump.
  Jump(bool conditional, unsigned short flag = 0, bool negate = false);

  private:
    bool shouldJump(Gameboy &gameboy) const;
};

#endif
