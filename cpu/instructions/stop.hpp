#ifndef STOP_HPP
#define STOP_HPP

#include "../instruction.hpp"

struct Stop: Instruction {
  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  Stop();
};

#endif
