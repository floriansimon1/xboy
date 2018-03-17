#ifndef REGISTER_INSTRUCTION_ON_DEREFERENCED_HL_HPP
#define REGISTER_INSTRUCTION_ON_DEREFERENCED_HL_HPP

#include "../constant-time-instruction.hpp"
#include "../../gameboy.hpp"

#include <iostream>

template <typename WrappedInstruction>
struct RegisterInstructionOnDereferencedHl: ConstantTimeInstruction {
  const WrappedInstruction instruction;

  RegisterInstructionOnDereferencedHl():
    ConstantTimeInstruction(16, 0, 2),
    instruction(&Cpu::de, true)
  {
  }

  void execute(Gameboy &gameboy, const uint8_t *data) const override {
    const auto registerBackup = gameboy.cpu.singleByteRegister(
      instruction.cpuRegister,
      instruction.low
    );

    gameboy.cpu.setSingleByteRegister(
      instruction.cpuRegister,
      instruction.low,
      gameboy.mmu[gameboy.cpu.hl]
    );

    instruction.execute(gameboy, data);

    gameboy.mmu.write(gameboy.cpu.hl, gameboy.cpu.singleByteRegister(
      instruction.cpuRegister,
      instruction.low
    ));

    gameboy.cpu.setSingleByteRegister(instruction.cpuRegister, instruction.low, registerBackup);
  }

  std::string toString() const override {
    std::string instructionString = instruction.toString();

    instructionString.erase(instructionString.size() - 2);

    return instructionString + " (HL)";
  }
};

#endif
