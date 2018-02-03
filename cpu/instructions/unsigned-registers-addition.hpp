#ifndef UNSIGNED_REGISTERS_ADDITION_HPP
#define UNSIGNED_REGISTERS_ADDITION_HPP

#include "./unsigned-immediate-addition.hpp"
#include "../instruction.hpp"
#include "../cpu.hpp"

struct UnsignedRegistersAddition: Instruction {
  const bool         low;
  CpuRegisterPointer cpuRegister;

  UnsignedRegistersAddition(
    CpuRegisterPointer cpuRegister,
    bool carry,
    bool low
  );

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
  const char* mnemonic() const;

  private:
    UnsignedImmediateAddition additionInstruction;
};

#endif
