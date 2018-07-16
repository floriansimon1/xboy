#ifndef WRITE_REGISTER_AT_SHORT_ADDRESS_HPP
#define WRITE_REGISTER_AT_SHORT_ADDRESS_HPP

#include "../constant-time-instruction.hpp"
#include "register-rotate-left.hpp"
#include "../cpu.hpp"

struct WriteRegisterAtShortAddress: ConstantTimeInstruction {
  CpuRegisterPointer source;
  const bool         sourceLow;
  CpuRegisterPointer destination;
  const bool         destinationLow;

  WriteRegisterAtShortAddress(
    CpuRegisterPointer source,
    const bool         sourceLow,
    CpuRegisterPointer destination,
    const bool         destinationLow
  );

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
