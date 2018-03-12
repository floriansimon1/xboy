#ifndef DEREFERENCE_HIGH_BYTE_HPP
#define DEREFERENCE_HIGH_BYTE_HPP

#include "load-immediate-8.hpp"
#include "../cpu.hpp"

struct DereferenceHighByte: ConstantTimeInstruction {
  DereferenceHighByte();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    LoadImmediate8 loadImmediated8Instruction;
};

#endif
