#include "instructions/dereference-combined-into-single-increment.hpp"
#include "instructions/single-byte-register-to-memory-increment.hpp"
#include "instructions/write-two-bytes-register-to-address.hpp"
#include "instructions/dereference-combined-into-single.hpp"
#include "instructions/single-byte-register-to-memory.hpp"
#include "instructions/two-bytes-registers-addition.hpp"
#include "instructions/unsigned-registers-addition.hpp"
#include "instructions/write-immediate-to-address.hpp"
#include "instructions/increment-dereference.hpp"
#include "instructions/single-byte-increment.hpp"
#include "instructions/a-rotate-right-carry.hpp"
#include "instructions/two-bytes-increment.hpp"
#include "instructions/a-rotate-left-carry.hpp"
#include "instructions/relative-jump-flag.hpp"
#include "instructions/invert-carry-flag.hpp"
#include "instructions/load-immediate-16.hpp"
#include "instructions/load-immediate-8.hpp"
#include "instructions/set-carry-flag.hpp"
#include "instructions/decimal-adjust.hpp"
#include "instructions/a-rotate-right.hpp"
#include "instructions/a-rotate-left.hpp"
#include "instructions/relative-jump.hpp"
#include "instructions/copy-register.hpp"
#include "instructions/negate.hpp"
#include "instructions-table.hpp"
#include "instructions/halt.hpp"
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
  oneByteOpcodes[0x2c] = std::make_shared<SingleByteIncrement>(&Cpu::hl, true, 1);
  oneByteOpcodes[0x2d] = std::make_shared<SingleByteIncrement>(&Cpu::hl, true, -1);
  oneByteOpcodes[0x2e] = std::make_shared<LoadImmediate8>(&Cpu::hl, true);
  oneByteOpcodes[0x2f] = std::make_shared<Negate>();

  oneByteOpcodes[0x30] = std::make_shared<RelativeJumpFlag>(Cpu::carryFlag, true);
  oneByteOpcodes[0x31] = std::make_shared<LoadImmediate16>(&Cpu::sp);
  oneByteOpcodes[0x32] = std::make_shared<SingleByteRegisterToMemoryIncrement>(&Cpu::hl, &Cpu::af, -1, false);
  oneByteOpcodes[0x33] = std::make_shared<TwoBytesIncrement>(&Cpu::sp, 1);
  oneByteOpcodes[0x34] = std::make_shared<IncrementDereference>(&Cpu::hl, 1);
  oneByteOpcodes[0x35] = std::make_shared<IncrementDereference>(&Cpu::hl, -1);
  oneByteOpcodes[0x36] = std::make_shared<WriteImmediateToAddress>(&Cpu::hl);
  oneByteOpcodes[0x37] = std::make_shared<SetCarryFlag>();
  oneByteOpcodes[0x38] = std::make_shared<RelativeJumpFlag>(Cpu::carryFlag, false);
  oneByteOpcodes[0x39] = std::make_shared<TwoBytesRegistersAddition>(&Cpu::hl, &Cpu::sp);
  oneByteOpcodes[0x3a] = std::make_shared<DereferenceCombinedIntoSingleIncrement>(&Cpu::hl, &Cpu::af, -1, false);
  oneByteOpcodes[0x3b] = std::make_shared<TwoBytesIncrement>(&Cpu::sp, -1);
  oneByteOpcodes[0x3c] = std::make_shared<SingleByteIncrement>(&Cpu::af, false, 1);
  oneByteOpcodes[0x3d] = std::make_shared<SingleByteIncrement>(&Cpu::af, false, -1);
  oneByteOpcodes[0x3e] = std::make_shared<LoadImmediate8>(&Cpu::af, false);
  oneByteOpcodes[0x3f] = std::make_shared<InvertCarryFlag>();

  oneByteOpcodes[0x40] = std::make_shared<Nop>();
  oneByteOpcodes[0x41] = std::make_shared<CopyRegister>(&Cpu::bc, false, &Cpu::bc, true);
  oneByteOpcodes[0x42] = std::make_shared<CopyRegister>(&Cpu::bc, false, &Cpu::de, false);
  oneByteOpcodes[0x43] = std::make_shared<CopyRegister>(&Cpu::bc, false, &Cpu::de, true);
  oneByteOpcodes[0x44] = std::make_shared<CopyRegister>(&Cpu::bc, false, &Cpu::hl, false);
  oneByteOpcodes[0x45] = std::make_shared<CopyRegister>(&Cpu::bc, false, &Cpu::hl, true);
  oneByteOpcodes[0x46] = std::make_shared<DereferenceCombinedIntoSingle>(&Cpu::hl, &Cpu::bc, false);
  oneByteOpcodes[0x47] = std::make_shared<CopyRegister>(&Cpu::bc, false, &Cpu::af, false);
  oneByteOpcodes[0x48] = std::make_shared<CopyRegister>(&Cpu::bc, true, &Cpu::bc, false);
  oneByteOpcodes[0x49] = std::make_shared<Nop>();
  oneByteOpcodes[0x4a] = std::make_shared<CopyRegister>(&Cpu::bc, true, &Cpu::de, false);
  oneByteOpcodes[0x4b] = std::make_shared<CopyRegister>(&Cpu::bc, true, &Cpu::de, true);
  oneByteOpcodes[0x4c] = std::make_shared<CopyRegister>(&Cpu::bc, true, &Cpu::hl, false);
  oneByteOpcodes[0x4d] = std::make_shared<CopyRegister>(&Cpu::bc, true, &Cpu::hl, true);
  oneByteOpcodes[0x4e] = std::make_shared<DereferenceCombinedIntoSingle>(&Cpu::hl, &Cpu::bc, true);
  oneByteOpcodes[0x4f] = std::make_shared<CopyRegister>(&Cpu::bc, true, &Cpu::af, false);

  oneByteOpcodes[0x50] = std::make_shared<CopyRegister>(&Cpu::de, false, &Cpu::bc, false);
  oneByteOpcodes[0x51] = std::make_shared<CopyRegister>(&Cpu::de, false, &Cpu::bc, true);
  oneByteOpcodes[0x52] = std::make_shared<Nop>();
  oneByteOpcodes[0x53] = std::make_shared<CopyRegister>(&Cpu::de, false, &Cpu::de, true);
  oneByteOpcodes[0x54] = std::make_shared<CopyRegister>(&Cpu::de, false, &Cpu::hl, false);
  oneByteOpcodes[0x55] = std::make_shared<CopyRegister>(&Cpu::de, false, &Cpu::hl, true);
  oneByteOpcodes[0x56] = std::make_shared<DereferenceCombinedIntoSingle>(&Cpu::hl, &Cpu::de, false);
  oneByteOpcodes[0x57] = std::make_shared<CopyRegister>(&Cpu::de, false, &Cpu::af, false);
  oneByteOpcodes[0x59] = std::make_shared<CopyRegister>(&Cpu::de, true, &Cpu::bc, false);
  oneByteOpcodes[0x59] = std::make_shared<CopyRegister>(&Cpu::de, true, &Cpu::bc, true);
  oneByteOpcodes[0x5a] = std::make_shared<CopyRegister>(&Cpu::de, true, &Cpu::de, false);
  oneByteOpcodes[0x5b] = std::make_shared<Nop>();
  oneByteOpcodes[0x5c] = std::make_shared<CopyRegister>(&Cpu::de, true, &Cpu::hl, false);
  oneByteOpcodes[0x5d] = std::make_shared<CopyRegister>(&Cpu::de, true, &Cpu::hl, true);
  oneByteOpcodes[0x5e] = std::make_shared<DereferenceCombinedIntoSingle>(&Cpu::hl, &Cpu::de, true);
  oneByteOpcodes[0x5f] = std::make_shared<CopyRegister>(&Cpu::de, true, &Cpu::af, false);

  oneByteOpcodes[0x60] = std::make_shared<CopyRegister>(&Cpu::hl, false, &Cpu::bc, false);
  oneByteOpcodes[0x61] = std::make_shared<CopyRegister>(&Cpu::hl, false, &Cpu::bc, true);
  oneByteOpcodes[0x62] = std::make_shared<CopyRegister>(&Cpu::hl, false, &Cpu::de, false);
  oneByteOpcodes[0x63] = std::make_shared<CopyRegister>(&Cpu::hl, false, &Cpu::de, true);
  oneByteOpcodes[0x64] = std::make_shared<Nop>();
  oneByteOpcodes[0x65] = std::make_shared<CopyRegister>(&Cpu::hl, false, &Cpu::hl, true);
  oneByteOpcodes[0x66] = std::make_shared<DereferenceCombinedIntoSingle>(&Cpu::hl, &Cpu::hl, false);
  oneByteOpcodes[0x67] = std::make_shared<CopyRegister>(&Cpu::hl, false, &Cpu::af, false);
  oneByteOpcodes[0x68] = std::make_shared<CopyRegister>(&Cpu::hl, true, &Cpu::bc, false);
  oneByteOpcodes[0x69] = std::make_shared<CopyRegister>(&Cpu::hl, true, &Cpu::bc, true);
  oneByteOpcodes[0x6a] = std::make_shared<CopyRegister>(&Cpu::hl, true, &Cpu::de, false);
  oneByteOpcodes[0x6b] = std::make_shared<CopyRegister>(&Cpu::hl, true, &Cpu::de, true);
  oneByteOpcodes[0x6c] = std::make_shared<CopyRegister>(&Cpu::hl, true, &Cpu::hl, false);
  oneByteOpcodes[0x6d] = std::make_shared<Nop>();
  oneByteOpcodes[0x6e] = std::make_shared<DereferenceCombinedIntoSingle>(&Cpu::hl, &Cpu::hl, true);
  oneByteOpcodes[0x6f] = std::make_shared<CopyRegister>(&Cpu::hl, true, &Cpu::af, false);

  oneByteOpcodes[0x70] = std::make_shared<SingleByteRegisterToMemory>(&Cpu::hl, &Cpu::bc, false);
  oneByteOpcodes[0x71] = std::make_shared<SingleByteRegisterToMemory>(&Cpu::hl, &Cpu::bc, true);
  oneByteOpcodes[0x72] = std::make_shared<SingleByteRegisterToMemory>(&Cpu::hl, &Cpu::de, false);
  oneByteOpcodes[0x73] = std::make_shared<SingleByteRegisterToMemory>(&Cpu::hl, &Cpu::de, true);
  oneByteOpcodes[0x74] = std::make_shared<SingleByteRegisterToMemory>(&Cpu::hl, &Cpu::hl, false);
  oneByteOpcodes[0x75] = std::make_shared<SingleByteRegisterToMemory>(&Cpu::hl, &Cpu::hl, true);
  oneByteOpcodes[0x76] = std::make_shared<Halt>();
  oneByteOpcodes[0x77] = std::make_shared<SingleByteRegisterToMemory>(&Cpu::hl, &Cpu::af, false);
  oneByteOpcodes[0x78] = std::make_shared<CopyRegister>(&Cpu::af, false, &Cpu::bc, false);
  oneByteOpcodes[0x79] = std::make_shared<CopyRegister>(&Cpu::af, false, &Cpu::bc, true);
  oneByteOpcodes[0x7a] = std::make_shared<CopyRegister>(&Cpu::af, false, &Cpu::de, false);
  oneByteOpcodes[0x7b] = std::make_shared<CopyRegister>(&Cpu::af, false, &Cpu::de, true);
  oneByteOpcodes[0x7c] = std::make_shared<CopyRegister>(&Cpu::af, false, &Cpu::hl, false);
  oneByteOpcodes[0x7d] = std::make_shared<CopyRegister>(&Cpu::af, false, &Cpu::hl, true);
  oneByteOpcodes[0x7e] = std::make_shared<DereferenceCombinedIntoSingle>(&Cpu::hl, &Cpu::af, false);
  oneByteOpcodes[0x7f] = std::make_shared<Nop>();

  oneByteOpcodes[0x80] = std::make_shared<UnsignedRegistersAddition>(&Cpu::af, false, &Cpu::bc, false);
  oneByteOpcodes[0x81] = std::make_shared<UnsignedRegistersAddition>(&Cpu::af, false, &Cpu::bc, true);
  oneByteOpcodes[0x82] = std::make_shared<UnsignedRegistersAddition>(&Cpu::af, false, &Cpu::de, false);
  oneByteOpcodes[0x83] = std::make_shared<UnsignedRegistersAddition>(&Cpu::af, false, &Cpu::de, true);
  oneByteOpcodes[0x84] = std::make_shared<UnsignedRegistersAddition>(&Cpu::af, false, &Cpu::hl, false);
  oneByteOpcodes[0x85] = std::make_shared<UnsignedRegistersAddition>(&Cpu::af, false, &Cpu::hl, true);

  oneByteOpcodes[0x87] = std::make_shared<UnsignedRegistersAddition>(&Cpu::af, false, &Cpu::af, false);
}

std::shared_ptr<Instruction> InstructionsTable::get(const bool fromExtendedSet, const uint8_t opcode) {
  const auto table = fromExtendedSet ? twoBytesOpcodes : oneByteOpcodes;

  return table[opcode];
}
