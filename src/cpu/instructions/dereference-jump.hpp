#ifndef DEREFERENCE_JUMP_HPP
#define DEREFERENCE_JUMP_HPP

#include "../constant-time-instruction.hpp"
#include "jump.hpp"

struct DereferenceJump: ConstantTimeInstruction {
  DereferenceJump();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    Jump jumpInstruction;
};

#endif
