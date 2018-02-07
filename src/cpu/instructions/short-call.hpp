#ifndef SHORT_CALL_HPP
#define SHORT_CALL_HPP

#include "../constant-time-instruction.hpp"
#include "../../gameboy.hpp"
#include "call.hpp"

struct ShortCall: ConstantTimeInstruction {
  const uint8_t hardcodedAddress;

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  ShortCall(uint8_t hardcodedAddress);

  private:
    const Call call;
};

#endif
