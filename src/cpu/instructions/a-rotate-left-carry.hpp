#ifndef A_ROTATE_LEFT_CARRY_HPP
#define A_ROTATE_LEFT_CARRY_HPP

#include "register-rotate-left-carry.hpp"
#include "../instruction.hpp"
#include "../cpu.hpp"

struct RotateLeftCarryA: Instruction {
  const RegisterRotateLeftCarry standardRotateLeftCarry;

  RotateLeftCarryA();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
