#ifndef WRITE_TWO_BYTES_REGISTER_TO_ADDRESS_HPP
#define WRITE_TWO_BYTES_REGISTER_TO_ADDRESS_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct WriteTwoBytesRegisterToAddress: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;

  WriteTwoBytesRegisterToAddress(CpuRegisterPointer cpuRegister);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
