#ifndef RELATIVE_JUMP_HPP
#define RELATIVE_JUMP_HPP

#include "../instruction.hpp"

struct RelativeJump: Instruction {
  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  RelativeJump();
};

#endif
