#ifndef DEREFERENCE_INTO_HIGH_BYTE_HPP
#define DEREFERENCE_INTO_HIGH_BYTE_HPP

#include "load-immediate-8.hpp"
#include "../cpu.hpp"

struct DereferenceIntoHighByte: ConstantTimeInstruction {
  DereferenceIntoHighByte();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
