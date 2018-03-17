#ifndef A_ROTATE_LEFT_HPP
#define A_ROTATE_LEFT_HPP

#include "../constant-time-instruction.hpp"
#include "register-rotate-left.hpp"
#include "../cpu.hpp"

struct RotateLeftA: ConstantTimeInstruction {
  const RegisterRotateLeft standardRotateLeft;

  RotateLeftA();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
