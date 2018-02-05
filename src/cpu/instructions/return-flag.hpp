#ifndef RETURN_FLAG_HPP
#define RETURN_FLAG_HPP

#include "../instruction.hpp"

struct ReturnFlag: Instruction {
  const bool           conditional;
  const bool           negate;
  const unsigned short flag;

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  unsigned short ticks(Gameboy &gameboy) const override;
  std::string toString() const override;

  ReturnFlag(bool conditional, unsigned short flag, bool negate);

  private:
    bool shouldJump(Gameboy &gameboy) const;
};

#endif
