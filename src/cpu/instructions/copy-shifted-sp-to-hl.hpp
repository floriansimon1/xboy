#ifndef COPY_SHIFTED_SP_TO_HL_HPP
#define COPY_SHIFTED_SP_TO_HL_HPP

#include "signed-immediate-addition.hpp"
#include "copy-combined-register.hpp"
#include "../cpu.hpp"

struct CopyShiftedSpToHl: ConstantTimeInstruction {
  CopyShiftedSpToHl();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    SignedImmediateAddition additionInstruction;
    CopyCombinedRegister    copyInstruction;
};

#endif
