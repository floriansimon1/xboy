#ifndef INSTRUCTIONS_TABLE_HPP
#define INSTRUCTIONS_TABLE_HPP

#include <memory>
#include <cstdint>

#include "instruction.hpp"

struct InstructionsTable {
  std::shared_ptr<Instruction> oneByteOpcodes[256];
  std::shared_ptr<Instruction> twoBytesOpcodes[256];

  InstructionsTable();

  std::shared_ptr<Instruction> get(const bool fromExtendedSet, const uint8_t opcode);

  private:
    void mapFirstTable();
    void mapExtendedTable();
};

#endif
