#include "operations-table.hpp"
#include "operations/nop.hpp"

// See http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html

OperationsTable::OperationsTable() {
  oneByteOpcodes[0x00] = std::make_shared<Nop>();
}

