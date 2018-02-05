#ifndef A_ROTATE_LEFT_CARRY_HPP
#define A_ROTATE_LEFT_CARRY_HPP

#include "../constant-time-instruction.hpp"
#include "register-rotate-left-carry.hpp"
#include "../cpu.hpp"

struct RotateLeftCarryA: ConstantTimeInstruction {
  const RegisterRotateLeftCarry standardRotateLeftCarry;

  RotateLeftCarryA();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
