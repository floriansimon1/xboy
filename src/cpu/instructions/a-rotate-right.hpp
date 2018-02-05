#ifndef A_ROTATE_RIGHT_HPP
#define A_ROTATE_RIGHT_HPP

#include "../constant-time-instruction.hpp"
#include "register-rotate-right.hpp"
#include "../cpu.hpp"

struct RotateRightA: ConstantTimeInstruction {
  const RegisterRotateRight standardRotateRight;

  RotateRightA();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
