#ifndef TWO_BYTES_REGISTERS_ADDITION_TEST_HPP
#define TWO_BYTES_REGISTERS_ADDITION_TEST_HPP

#include "../test.hpp"
#include "../../gameboy.hpp"
#include "../../cpu/instruction.hpp"

struct TwoBytesRegistersAdditionTest: Test {
  TwoBytesRegistersAdditionTest();

  bool run() override;

  private:
    bool executeAndCheck(
      Gameboy &gameboy,
      Instruction &instruction,
      uint16_t value,
      bool carry,
      bool subtract,
      bool halfCarry
    ) const;
};

#endif
