#ifndef INSTRUCTIONS_TABLE_HPP
#define INSTRUCTIONS_TABLE_HPP

#include <memory>

#include "instruction.hpp"

struct InstructionsTable {
  std::shared_ptr<Instruction> oneByteOpcodes[256];
  std::shared_ptr<Instruction> twoBytesOpcodes[256];

  InstructionsTable();
};

#endif

