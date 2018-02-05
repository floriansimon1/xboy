#ifndef TWO_BYTES_REGISTERS_ADDITION_HPP
#define TWO_BYTES_REGISTERS_ADDITION_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct TwoBytesRegistersAddition: ConstantTimeInstruction {
  CpuRegisterPointer source;
  CpuRegisterPointer destination;

  TwoBytesRegistersAddition(CpuRegisterPointer source, CpuRegisterPointer destination);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
