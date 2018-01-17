#ifndef A_ROTATE_LEFT_HPP
#define A_ROTATE_LEFT_HPP

#include "register-rotate-left.hpp"
#include "../instruction.hpp"
#include "../cpu.hpp"

struct RotateLeftA: Instruction {
  const RegisterRotateLeft standardRotateLeft;

  RotateLeftA();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
