#ifndef UNSIGNED_REGISTERS_SUBTRACTION_HPP
#define UNSIGNED_REGISTERS_SUBTRACTION_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct UnsignedRegistersSubtraction: Instruction {
  CpuRegisterPointer cpuRegister;
  bool               carry;
  bool               low;

  UnsignedRegistersSubtraction(
    CpuRegisterPointer cpuRegister,
    bool carry,
    bool low
  );

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
  const char* mnemonic() const;
};

#endif
