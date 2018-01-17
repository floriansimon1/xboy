#include "instructions/write-two-bytes-register-to-address.hpp"
#include "instructions/dereference-combined-into-single.hpp"
#include "instructions/single-byte-register-to-memory.hpp"
#include "instructions/two-bytes-registers-addition.hpp"
#include "instructions/single-byte-increment.hpp"
#include "instructions/a-rotate-right-carry.hpp"
#include "instructions/two-bytes-increment.hpp"
#include "instructions/a-rotate-left-carry.hpp"
#include "instructions/load-immediate-16.hpp"
#include "instructions/load-immediate-8.hpp"
#include "instructions/a-rotate-left.hpp"
#include "instructions-table.hpp"
#include "instructions/stop.hpp"
#include "instructions/nop.hpp"
#include "cpu.hpp"

// See http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html

InstructionsTable::InstructionsTable() {
  oneByteOpcodes[0x00] = std::make_shared<Nop>();
  oneByteOpcodes[0x01] = std::make_shared<LoadImmediate16>(&Cpu::bc);
  oneByteOpcodes[0x02] = std::make_shared<SingleByteRegisterToMemory>(&Cpu::bc, &Cpu::af, false);
  oneByteOpcodes[0x03] = std::make_shared<TwoBytesIncrement>(&Cpu::bc, 1);
  oneByteOpcodes[0x04] = std::make_shared<SingleByteIncrement>(&Cpu::bc, false, 1);
  oneByteOpcodes[0x05] = std::make_shared<SingleByteIncrement>(&Cpu::bc, false, -1);
  oneByteOpcodes[0x06] = std::make_shared<LoadImmediate8>(&Cpu::bc, false);
  oneByteOpcodes[0x07] = std::make_shared<RotateLeftCarryA>();
  oneByteOpcodes[0x08] = std::make_shared<WriteTwoBytesRegisterToAddress>(&Cpu::sp);
  oneByteOpcodes[0x09] = std::make_shared<TwoBytesRegistersAddition>(&Cpu::bc, &Cpu::hl);
  oneByteOpcodes[0x0a] = std::make_shared<DereferenceCombinedIntoSingle>(&Cpu::bc, &Cpu::af, false);
  oneByteOpcodes[0x0b] = std::make_shared<TwoBytesIncrement>(&Cpu::bc, -1);
  oneByteOpcodes[0x0c] = std::make_shared<SingleByteIncrement>(&Cpu::bc, true, 1);
  oneByteOpcodes[0x0d] = std::make_shared<SingleByteIncrement>(&Cpu::bc, true, -1);
  oneByteOpcodes[0x0e] = std::make_shared<LoadImmediate8>(&Cpu::bc, true);
  oneByteOpcodes[0x0f] = std::make_shared<RotateRightCarryA>();

  oneByteOpcodes[0x10] = std::make_shared<Stop>();
  oneByteOpcodes[0x11] = std::make_shared<LoadImmediate16>(&Cpu::de);
  oneByteOpcodes[0x12] = std::make_shared<SingleByteRegisterToMemory>(&Cpu::de, &Cpu::af, false);
  oneByteOpcodes[0x13] = std::make_shared<TwoBytesIncrement>(&Cpu::de, 1);
  oneByteOpcodes[0x14] = std::make_shared<SingleByteIncrement>(&Cpu::de, false, 1);
  oneByteOpcodes[0x15] = std::make_shared<SingleByteIncrement>(&Cpu::de, false, -1);
  oneByteOpcodes[0x16] = std::make_shared<LoadImmediate8>(&Cpu::de, false);
  oneByteOpcodes[0x17] = std::make_shared<RotateLeftA>();
}

std::shared_ptr<Instruction> InstructionsTable::get(const bool fromExtendedSet, const uint8_t opcode) {
  const auto table = fromExtendedSet ? twoBytesOpcodes : oneByteOpcodes;

  return table[opcode];
}
