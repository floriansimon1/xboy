#ifndef A_ROTATE_RIGHT_CARRY_HPP
#define A_ROTATE_RIGHT_CARRY_HPP

#include "../constant-time-instruction.hpp"
#include "register-rotate-right-carry.hpp"
#include "../cpu.hpp"

struct RotateRightCarryA: ConstantTimeInstruction {
  const RegisterRotateRightCarry standardRotateRightCarry;

  RotateRightCarryA();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
