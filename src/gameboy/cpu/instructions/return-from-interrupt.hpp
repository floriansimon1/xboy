#ifndef RETURN_FROM_INTERRUPT_HPP
#define RETURN_FROM_INTERRUPT_HPP

#include "return-flag.hpp"
#include "../constant-time-instruction.hpp"

struct ReturnFromInterrupt: ConstantTimeInstruction {
  ReturnFromInterrupt();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    ReturnFlag returnInstruction;
};

#endif
