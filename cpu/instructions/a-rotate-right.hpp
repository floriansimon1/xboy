#ifndef A_ROTATE_RIGHT_HPP
#define A_ROTATE_RIGHT_HPP

#include "register-rotate-right.hpp"
#include "../instruction.hpp"
#include "../cpu.hpp"

struct RotateRightA: Instruction {
  const RegisterRotateRight standardRotateRight;

  RotateRightA();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
