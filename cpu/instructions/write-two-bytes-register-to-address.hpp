#ifndef WRITE_TWO_BYTES_REGISTER_TO_ADDRESS_HPP
#define WRITE_TWO_BYTES_REGISTER_TO_ADDRESS_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct WriteTwoBytesRegisterToAddress: Instruction {
  CpuRegisterPointer cpuRegister;

  WriteTwoBytesRegisterToAddress(CpuRegisterPointer cpuRegister);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const;
};

#endif

