#ifndef RELATIVE_JUMP_FLAG_HPP
#define RELATIVE_JUMP_FLAG_HPP

#include "../instruction.hpp"

struct RelativeJumpFlag: Instruction {
  const bool negate;
  const unsigned short flag;

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  unsigned short ticks(Gameboy &gameboy) const override;
  std::string toString() const override;

  RelativeJumpFlag(unsigned short flag, bool negate);

  private:
    bool shouldJump(Gameboy &gameboy) const;
};

#endif
