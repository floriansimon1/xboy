#include "instructions/dereference-combined-into-single-increment.hpp"
#include "instructions/single-byte-register-to-memory-increment.hpp"
#include "instructions/write-two-bytes-register-to-address.hpp"
#include "instructions/dereference-combined-into-single.hpp"
#include "instructions/single-byte-register-to-memory.hpp"
#include "instructions/two-bytes-registers-addition.hpp"
#include "instructions/single-byte-increment.hpp"
#include "instructions/a-rotate-right-carry.hpp"
#include "instructions/two-bytes-increment.hpp"
#include "instructions/a-rotate-left-carry.hpp"
#include "instructions/relative-jump-flag.hpp"
#include "instructions/load-immediate-16.hpp"
#include "instructions/load-immediate-8.hpp"
#include "instructions/decimal-adjust.hpp"
#include "instructions/a-rotate-right.hpp"
#include "instructions/a-rotate-left.hpp"
#include "instructions/relative-jump.hpp"
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
  oneByteOpcodes[0x18] = std::make_shared<RelativeJump>();
  oneByteOpcodes[0x19] = std::make_shared<TwoBytesRegistersAddition>(&Cpu::de, &Cpu::hl);
  oneByteOpcodes[0x1a] = std::make_shared<DereferenceCombinedIntoSingle>(&Cpu::de, &Cpu::af, false);
  oneByteOpcodes[0x1b] = std::make_shared<TwoBytesIncrement>(&Cpu::de, -1);
  oneByteOpcodes[0x1c] = std::make_shared<SingleByteIncrement>(&Cpu::de, true, 1);
  oneByteOpcodes[0x1d] = std::make_shared<SingleByteIncrement>(&Cpu::de, true, -1);
  oneByteOpcodes[0x1e] = std::make_shared<LoadImmediate8>(&Cpu::de, true);
  oneByteOpcodes[0x1f] = std::make_shared<RotateRightA>();

  oneByteOpcodes[0x20] = std::make_shared<RelativeJumpFlag>(Cpu::zeroFlag, true);
  oneByteOpcodes[0x21] = std::make_shared<LoadImmediate16>(&Cpu::hl);
  oneByteOpcodes[0x22] = std::make_shared<SingleByteRegisterToMemoryIncrement>(&Cpu::hl, &Cpu::af, 1, false);
  oneByteOpcodes[0x23] = std::make_shared<TwoBytesIncrement>(&Cpu::hl, 1);
  oneByteOpcodes[0x24] = std::make_shared<SingleByteIncrement>(&Cpu::hl, false, 1);
  oneByteOpcodes[0x25] = std::make_shared<SingleByteIncrement>(&Cpu::hl, false, -1);
  oneByteOpcodes[0x26] = std::make_shared<LoadImmediate8>(&Cpu::hl, false);
  oneByteOpcodes[0x27] = std::make_shared<DecimalAdjust>();
  oneByteOpcodes[0x28] = std::make_shared<RelativeJumpFlag>(Cpu::zeroFlag, false);
  oneByteOpcodes[0x29] = std::make_shared<TwoBytesRegistersAddition>(&Cpu::hl, &Cpu::hl);
  oneByteOpcodes[0x2a] = std::make_shared<DereferenceCombinedIntoSingleIncrement>(&Cpu::hl, &Cpu::af, 1, false);
  oneByteOpcodes[0x2b] = std::make_shared<TwoBytesIncrement>(&Cpu::hl, -1);
}

std::shared_ptr<Instruction> InstructionsTable::get(const bool fromExtendedSet, const uint8_t opcode) {
  const auto table = fromExtendedSet ? twoBytesOpcodes : oneByteOpcodes;

  return table[opcode];
}
