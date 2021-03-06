#include "instructions/dereference-combined-into-single-increment.hpp"
#include "instructions/single-byte-register-to-memory-increment.hpp"
#include "instructions/register-instruction-on-dereferenced-hl.hpp"
#include "instructions/write-two-bytes-register-to-address.hpp"
#include "instructions/subtract-memory-byte-to-register.hpp"
#include "instructions/dereference-combined-into-single.hpp"
#include "instructions/write-register-at-short-address.hpp"
#include "instructions/unsigned-registers-subtraction.hpp"
#include "instructions/single-byte-register-to-memory.hpp"
#include "instructions/two-bytes-registers-addition.hpp"
#include "instructions/add-memory-byte-to-register.hpp"
#include "instructions/unsigned-registers-addition.hpp"
#include "instructions/unsigned-immediate-addition.hpp"
#include "instructions/write-immediate-to-address.hpp"
#include "instructions/dereference-into-high-byte.hpp"
#include "instructions/signed-immediate-addition.hpp"
#include "instructions/write-register-to-address.hpp"
#include "instructions/copy-combined-register.hpp"
#include "instructions/copy-shifted-sp-to-hl.hpp"
#include "instructions/return-from-interrupt.hpp"
#include "instructions/increment-dereference.hpp"
#include "instructions/single-byte-increment.hpp"
#include "instructions/dereference-high-byte.hpp"
#include "instructions/a-rotate-right-carry.hpp"
#include "instructions/register-shift-right.hpp"
#include "instructions/register-shift-left.hpp"
#include "instructions/two-bytes-increment.hpp"
#include "instructions/a-rotate-left-carry.hpp"
#include "instructions/dereference-compare.hpp"
#include "instructions/relative-jump-flag.hpp"
#include "instructions/invert-carry-flag.hpp"
#include "instructions/enable-interrupts.hpp"
#include "instructions/registers-compare.hpp"
#include "instructions/load-immediate-16.hpp"
#include "instructions/dereference-jump.hpp"
#include "instructions/load-immediate-8.hpp"
#include "instructions/dereference-and.hpp"
#include "instructions/dereference-or.hpp"
#include "instructions/set-carry-flag.hpp"
#include "instructions/decimal-adjust.hpp"
#include "instructions/a-rotate-right.hpp"
#include "instructions/a-rotate-left.hpp"
#include "instructions/copy-register.hpp"
#include "instructions/registers-and.hpp"
#include "instructions/registers-or.hpp"
#include "instructions/dereference.hpp"
#include "instructions/return-flag.hpp"
#include "instructions/short-call.hpp"
#include "instructions/push-word.hpp"
#include "instructions/pop-word.hpp"
#include "instructions/unmapped.hpp"
#include "instructions/get-bit.hpp"
#include "instructions/negate.hpp"
#include "instructions/clear.hpp"
#include "instructions-table.hpp"
#include "instructions/jump.hpp"
#include "instructions/swap.hpp"
#include "instructions/call.hpp"
#include "instructions/halt.hpp"
#include "instructions/stop.hpp"
#include "instructions/set.hpp"
#include "instructions/nop.hpp"
#include "cpu.hpp"

// See http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html

InstructionsTable::InstructionsTable() {
  mapFirstTable();
  mapExtendedTable();
}

void InstructionsTable::mapFirstTable() {
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
  oneByteOpcodes[0x18] = std::make_shared<RelativeJumpFlag>(false);
  oneByteOpcodes[0x19] = std::make_shared<TwoBytesRegistersAddition>(&Cpu::de, &Cpu::hl);
  oneByteOpcodes[0x1a] = std::make_shared<DereferenceCombinedIntoSingle>(&Cpu::de, &Cpu::af, false);
  oneByteOpcodes[0x1b] = std::make_shared<TwoBytesIncrement>(&Cpu::de, -1);
  oneByteOpcodes[0x1c] = std::make_shared<SingleByteIncrement>(&Cpu::de, true, 1);
  oneByteOpcodes[0x1d] = std::make_shared<SingleByteIncrement>(&Cpu::de, true, -1);
  oneByteOpcodes[0x1e] = std::make_shared<LoadImmediate8>(&Cpu::de, true);
  oneByteOpcodes[0x1f] = std::make_shared<RotateRightA>();

  oneByteOpcodes[0x20] = std::make_shared<RelativeJumpFlag>(true, Cpu::zeroFlag, true);
  oneByteOpcodes[0x21] = std::make_shared<LoadImmediate16>(&Cpu::hl);
  oneByteOpcodes[0x22] = std::make_shared<SingleByteRegisterToMemoryIncrement>(&Cpu::hl, &Cpu::af, 1, false);
  oneByteOpcodes[0x23] = std::make_shared<TwoBytesIncrement>(&Cpu::hl, 1);
  oneByteOpcodes[0x24] = std::make_shared<SingleByteIncrement>(&Cpu::hl, false, 1);
  oneByteOpcodes[0x25] = std::make_shared<SingleByteIncrement>(&Cpu::hl, false, -1);
  oneByteOpcodes[0x26] = std::make_shared<LoadImmediate8>(&Cpu::hl, false);
  oneByteOpcodes[0x27] = std::make_shared<DecimalAdjust>();
  oneByteOpcodes[0x28] = std::make_shared<RelativeJumpFlag>(true, Cpu::zeroFlag, false);
  oneByteOpcodes[0x29] = std::make_shared<TwoBytesRegistersAddition>(&Cpu::hl, &Cpu::hl);
  oneByteOpcodes[0x2a] = std::make_shared<DereferenceCombinedIntoSingleIncrement>(&Cpu::hl, &Cpu::af, 1, false);
  oneByteOpcodes[0x2b] = std::make_shared<TwoBytesIncrement>(&Cpu::hl, -1);
  oneByteOpcodes[0x2c] = std::make_shared<SingleByteIncrement>(&Cpu::hl, true, 1);
  oneByteOpcodes[0x2d] = std::make_shared<SingleByteIncrement>(&Cpu::hl, true, -1);
  oneByteOpcodes[0x2e] = std::make_shared<LoadImmediate8>(&Cpu::hl, true);
  oneByteOpcodes[0x2f] = std::make_shared<Negate>();

  oneByteOpcodes[0x30] = std::make_shared<RelativeJumpFlag>(true, Cpu::carryFlag, true);
  oneByteOpcodes[0x31] = std::make_shared<LoadImmediate16>(&Cpu::sp);
  oneByteOpcodes[0x32] = std::make_shared<SingleByteRegisterToMemoryIncrement>(&Cpu::hl, &Cpu::af, -1, false);
  oneByteOpcodes[0x33] = std::make_shared<TwoBytesIncrement>(&Cpu::sp, 1);
  oneByteOpcodes[0x34] = std::make_shared<IncrementDereference>(&Cpu::hl, 1);
  oneByteOpcodes[0x35] = std::make_shared<IncrementDereference>(&Cpu::hl, -1);
  oneByteOpcodes[0x36] = std::make_shared<WriteImmediateToAddress>(&Cpu::hl);
  oneByteOpcodes[0x37] = std::make_shared<SetCarryFlag>();
  oneByteOpcodes[0x38] = std::make_shared<RelativeJumpFlag>(true, Cpu::carryFlag, false);
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

  oneByteOpcodes[0x80] = std::make_shared<UnsignedRegistersAddition>( &Cpu::bc, false, false);
  oneByteOpcodes[0x81] = std::make_shared<UnsignedRegistersAddition>( &Cpu::bc, true, false);
  oneByteOpcodes[0x82] = std::make_shared<UnsignedRegistersAddition>( &Cpu::de, false, false);
  oneByteOpcodes[0x83] = std::make_shared<UnsignedRegistersAddition>( &Cpu::de, true, false);
  oneByteOpcodes[0x84] = std::make_shared<UnsignedRegistersAddition>( &Cpu::hl, false, false);
  oneByteOpcodes[0x85] = std::make_shared<UnsignedRegistersAddition>( &Cpu::hl, true, false);
  oneByteOpcodes[0x86] = std::make_shared<AddMemoryByteToRegister>(&Cpu::hl,  false);
  oneByteOpcodes[0x87] = std::make_shared<UnsignedRegistersAddition>( &Cpu::af, false, false);
  oneByteOpcodes[0x88] = std::make_shared<UnsignedRegistersAddition>(&Cpu::bc, false, true);
  oneByteOpcodes[0x89] = std::make_shared<UnsignedRegistersAddition>(&Cpu::bc, true, true);
  oneByteOpcodes[0x8a] = std::make_shared<UnsignedRegistersAddition>(&Cpu::de, false, true);
  oneByteOpcodes[0x8b] = std::make_shared<UnsignedRegistersAddition>(&Cpu::de, true, true);
  oneByteOpcodes[0x8c] = std::make_shared<UnsignedRegistersAddition>(&Cpu::hl, false, true);
  oneByteOpcodes[0x8d] = std::make_shared<UnsignedRegistersAddition>(&Cpu::hl, true, true);
  oneByteOpcodes[0x8e] = std::make_shared<AddMemoryByteToRegister>(&Cpu::hl, true);
  oneByteOpcodes[0x8f] = std::make_shared<UnsignedRegistersAddition>(&Cpu::af, false, true);

  oneByteOpcodes[0x90] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::bc, false, false);
  oneByteOpcodes[0x91] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::bc, true, false);
  oneByteOpcodes[0x92] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::de, false, false);
  oneByteOpcodes[0x93] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::de, true, false);
  oneByteOpcodes[0x94] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::hl, false, false);
  oneByteOpcodes[0x95] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::hl, true, false);
  oneByteOpcodes[0x96] = std::make_shared<SubtractMemoryByteToRegister>(&Cpu::hl, false);
  oneByteOpcodes[0x97] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::af, false, false);
  oneByteOpcodes[0x98] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::bc, false, true);
  oneByteOpcodes[0x99] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::bc, true, true);
  oneByteOpcodes[0x9a] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::de, false, true);
  oneByteOpcodes[0x9b] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::de, true, true);
  oneByteOpcodes[0x9c] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::hl, false, true);
  oneByteOpcodes[0x9d] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::hl, true, true);
  oneByteOpcodes[0x9e] = std::make_shared<SubtractMemoryByteToRegister>(&Cpu::hl, true);
  oneByteOpcodes[0x9f] = std::make_shared<UnsignedRegistersSubtraction>(&Cpu::af, false, true);

  oneByteOpcodes[0xa0] = std::make_shared<RegistersAnd>(&Cpu::bc, false);
  oneByteOpcodes[0xa1] = std::make_shared<RegistersAnd>(&Cpu::bc, true);
  oneByteOpcodes[0xa2] = std::make_shared<RegistersAnd>(&Cpu::de, false);
  oneByteOpcodes[0xa3] = std::make_shared<RegistersAnd>(&Cpu::de, true);
  oneByteOpcodes[0xa4] = std::make_shared<RegistersAnd>(&Cpu::hl, false);
  oneByteOpcodes[0xa5] = std::make_shared<RegistersAnd>(&Cpu::hl, true);
  oneByteOpcodes[0xa6] = std::make_shared<DereferenceAnd>(&Cpu::hl);
  oneByteOpcodes[0xa7] = std::make_shared<RegistersAnd>(&Cpu::af, false);
  oneByteOpcodes[0xa8] = std::make_shared<RegistersOr>(&Cpu::bc, false, true);
  oneByteOpcodes[0xa9] = std::make_shared<RegistersOr>(&Cpu::bc, true, true);
  oneByteOpcodes[0xaa] = std::make_shared<RegistersOr>(&Cpu::de, false, true);
  oneByteOpcodes[0xab] = std::make_shared<RegistersOr>(&Cpu::de, true, true);
  oneByteOpcodes[0xac] = std::make_shared<RegistersOr>(&Cpu::hl, false, true);
  oneByteOpcodes[0xad] = std::make_shared<RegistersOr>(&Cpu::hl, true, true);
  oneByteOpcodes[0xae] = std::make_shared<DereferenceOr>(&Cpu::hl, true);
  oneByteOpcodes[0xaf] = std::make_shared<RegistersOr>(&Cpu::af, false, true);

  oneByteOpcodes[0xb0] = std::make_shared<RegistersOr>(&Cpu::bc, false, false);
  oneByteOpcodes[0xb1] = std::make_shared<RegistersOr>(&Cpu::bc, true, false);
  oneByteOpcodes[0xb2] = std::make_shared<RegistersOr>(&Cpu::de, false, false);
  oneByteOpcodes[0xb3] = std::make_shared<RegistersOr>(&Cpu::de, true, false);
  oneByteOpcodes[0xb4] = std::make_shared<RegistersOr>(&Cpu::hl, false, false);
  oneByteOpcodes[0xb5] = std::make_shared<RegistersOr>(&Cpu::hl, true, false);
  oneByteOpcodes[0xb6] = std::make_shared<DereferenceOr>(&Cpu::hl, false);
  oneByteOpcodes[0xb7] = std::make_shared<RegistersOr>(&Cpu::af, false, false);
  oneByteOpcodes[0xb8] = std::make_shared<RegistersCompare>(&Cpu::bc, false);
  oneByteOpcodes[0xb9] = std::make_shared<RegistersCompare>(&Cpu::bc, true);
  oneByteOpcodes[0xba] = std::make_shared<RegistersCompare>(&Cpu::de, false);
  oneByteOpcodes[0xbb] = std::make_shared<RegistersCompare>(&Cpu::de, true);
  oneByteOpcodes[0xbc] = std::make_shared<RegistersCompare>(&Cpu::hl, false);
  oneByteOpcodes[0xbd] = std::make_shared<RegistersCompare>(&Cpu::hl, true);
  oneByteOpcodes[0xbe] = std::make_shared<DereferenceCompare>(&Cpu::hl);
  oneByteOpcodes[0xbf] = std::make_shared<RegistersCompare>(&Cpu::af, false);

  oneByteOpcodes[0xc0] = std::make_shared<ReturnFlag>(true, Cpu::zeroFlag, true);
  oneByteOpcodes[0xc1] = std::make_shared<PopWord>(&Cpu::bc);
  oneByteOpcodes[0xc2] = std::make_shared<Jump>(true, Cpu::zeroFlag, true);
  oneByteOpcodes[0xc3] = std::make_shared<Jump>(false);
  oneByteOpcodes[0xc4] = std::make_shared<Call>(true, Cpu::zeroFlag, true);
  oneByteOpcodes[0xc5] = std::make_shared<PushWord>(&Cpu::bc);
  oneByteOpcodes[0xc6] = std::make_shared<UnsignedImmediateAddition>(false);
  oneByteOpcodes[0xc7] = std::make_shared<ShortCall>(0);
  oneByteOpcodes[0xc8] = std::make_shared<ReturnFlag>(true, Cpu::zeroFlag, false);
  oneByteOpcodes[0xc9] = std::make_shared<ReturnFlag>(false);
  oneByteOpcodes[0xca] = std::make_shared<Jump>(true, Cpu::zeroFlag, false);
  // oneByteOpcodes[0xcb] is unmapped (refers to the second table).
  oneByteOpcodes[0xcc] = std::make_shared<Call>(true, Cpu::zeroFlag, true);
  oneByteOpcodes[0xcd] = std::make_shared<Call>(false);
  oneByteOpcodes[0xce] = std::make_shared<UnsignedImmediateAddition>(true);
  oneByteOpcodes[0xcf] = std::make_shared<ShortCall>(8);

  oneByteOpcodes[0xd0] = std::make_shared<ReturnFlag>(true, Cpu::carryFlag, true);
  oneByteOpcodes[0xd1] = std::make_shared<PopWord>(&Cpu::de);
  oneByteOpcodes[0xd2] = std::make_shared<Jump>(true, Cpu::carryFlag, true);
  oneByteOpcodes[0xd3] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xd4] = std::make_shared<Call>(true, Cpu::carryFlag, true);
  oneByteOpcodes[0xd5] = std::make_shared<PushWord>(&Cpu::de);
  oneByteOpcodes[0xd6] = std::make_shared<UnsignedImmediateSubtraction>(false);
  oneByteOpcodes[0xd7] = std::make_shared<ShortCall>(0x10);
  oneByteOpcodes[0xd8] = std::make_shared<ReturnFlag>(true, Cpu::carryFlag, false);
  oneByteOpcodes[0xd9] = std::make_shared<ReturnFromInterrupt>();
  oneByteOpcodes[0xda] = std::make_shared<Jump>(true, Cpu::carryFlag, false);
  oneByteOpcodes[0xdb] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xdc] = std::make_shared<Call>(true, Cpu::carryFlag, true);
  oneByteOpcodes[0xdd] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xde] = std::make_shared<UnsignedImmediateSubtraction>(true);
  oneByteOpcodes[0xdf] = std::make_shared<ShortCall>(0x18);

  oneByteOpcodes[0xe0] = std::make_shared<DereferenceIntoHighByte>();
  oneByteOpcodes[0xe1] = std::make_shared<PopWord>(&Cpu::hl);
  oneByteOpcodes[0xe2] = std::make_shared<WriteRegisterAtShortAddress>(&Cpu::af, false, &Cpu::bc, true);
  oneByteOpcodes[0xe3] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xe4] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xe5] = std::make_shared<PushWord>(&Cpu::hl);
  oneByteOpcodes[0xe6] = std::make_shared<ImmediateAnd>();
  oneByteOpcodes[0xe7] = std::make_shared<ShortCall>(0x20);
  oneByteOpcodes[0xe8] = std::make_shared<SignedImmediateAddition>();
  oneByteOpcodes[0xe9] = std::make_shared<DereferenceJump>();
  oneByteOpcodes[0xea] = std::make_shared<WriteRegisterToAddress>(&Cpu::af, false);
  oneByteOpcodes[0xeb] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xec] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xed] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xee] = std::make_shared<ImmediateOr>(true);
  oneByteOpcodes[0xef] = std::make_shared<ShortCall>(0x28);

  oneByteOpcodes[0xf0] = std::make_shared<DereferenceHighByte>();
  oneByteOpcodes[0xf1] = std::make_shared<PopWord>(&Cpu::af);
  oneByteOpcodes[0xf2] = std::make_shared<WriteRegisterAtShortAddress>(&Cpu::bc, true, &Cpu::af, false);
  oneByteOpcodes[0xf3] = std::make_shared<EnableInterrupts>(false);
  oneByteOpcodes[0xf4] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xf5] = std::make_shared<PushWord>(&Cpu::af);
  oneByteOpcodes[0xf6] = std::make_shared<ImmediateOr>(false);
  oneByteOpcodes[0xf7] = std::make_shared<ShortCall>(0x30);
  oneByteOpcodes[0xf8] = std::make_shared<CopyShiftedSpToHl>();
  oneByteOpcodes[0xf9] = std::make_shared<CopyCombinedRegister>(&Cpu::sp, &Cpu::hl);
  oneByteOpcodes[0xfa] = std::make_shared<Dereference>();
  oneByteOpcodes[0xfb] = std::make_shared<EnableInterrupts>(true);
  oneByteOpcodes[0xfc] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xfd] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xfe] = std::make_shared<ImmediateCompare>();
  oneByteOpcodes[0xff] = std::make_shared<ShortCall>(0x38);
}

void InstructionsTable::mapExtendedTable() {
  twoBytesOpcodes[0x00] = std::make_shared<RegisterRotateLeftCarry>(&Cpu::bc, false);
  twoBytesOpcodes[0x01] = std::make_shared<RegisterRotateLeftCarry>(&Cpu::bc, true);
  twoBytesOpcodes[0x02] = std::make_shared<RegisterRotateLeftCarry>(&Cpu::de, false);
  twoBytesOpcodes[0x03] = std::make_shared<RegisterRotateLeftCarry>(&Cpu::de, true);
  twoBytesOpcodes[0x04] = std::make_shared<RegisterRotateLeftCarry>(&Cpu::hl, false);
  twoBytesOpcodes[0x05] = std::make_shared<RegisterRotateLeftCarry>(&Cpu::hl, true);
  twoBytesOpcodes[0x06] = std::make_shared<RegisterInstructionOnDereferencedHl<RegisterRotateLeftCarry>>();
  twoBytesOpcodes[0x07] = std::make_shared<RegisterRotateLeftCarry>(&Cpu::af, false);
  twoBytesOpcodes[0x08] = std::make_shared<RegisterRotateRightCarry>(&Cpu::bc, false);
  twoBytesOpcodes[0x09] = std::make_shared<RegisterRotateRightCarry>(&Cpu::bc, true);
  twoBytesOpcodes[0x0a] = std::make_shared<RegisterRotateRightCarry>(&Cpu::de, false);
  twoBytesOpcodes[0x0b] = std::make_shared<RegisterRotateRightCarry>(&Cpu::de, true);
  twoBytesOpcodes[0x0c] = std::make_shared<RegisterRotateRightCarry>(&Cpu::hl, false);
  twoBytesOpcodes[0x0d] = std::make_shared<RegisterRotateRightCarry>(&Cpu::hl, true);
  twoBytesOpcodes[0x0e] = std::make_shared<RegisterInstructionOnDereferencedHl<RegisterRotateRightCarry>>();
  twoBytesOpcodes[0x0f] = std::make_shared<RegisterRotateRightCarry>(&Cpu::af, false);

  twoBytesOpcodes[0x10] = std::make_shared<RegisterRotateLeft>(&Cpu::bc, false);
  twoBytesOpcodes[0x11] = std::make_shared<RegisterRotateLeft>(&Cpu::bc, true);
  twoBytesOpcodes[0x12] = std::make_shared<RegisterRotateLeft>(&Cpu::de, false);
  twoBytesOpcodes[0x13] = std::make_shared<RegisterRotateLeft>(&Cpu::de, true);
  twoBytesOpcodes[0x14] = std::make_shared<RegisterRotateLeft>(&Cpu::hl, false);
  twoBytesOpcodes[0x15] = std::make_shared<RegisterRotateLeft>(&Cpu::hl, true);
  twoBytesOpcodes[0x16] = std::make_shared<RegisterInstructionOnDereferencedHl<RegisterRotateLeft>>();
  twoBytesOpcodes[0x17] = std::make_shared<RegisterRotateLeft>(&Cpu::af, false);
  twoBytesOpcodes[0x18] = std::make_shared<RegisterRotateRight>(&Cpu::bc, false);
  twoBytesOpcodes[0x19] = std::make_shared<RegisterRotateRight>(&Cpu::bc, true);
  twoBytesOpcodes[0x1a] = std::make_shared<RegisterRotateRight>(&Cpu::de, false);
  twoBytesOpcodes[0x1b] = std::make_shared<RegisterRotateRight>(&Cpu::de, true);
  twoBytesOpcodes[0x1c] = std::make_shared<RegisterRotateRight>(&Cpu::hl, false);
  twoBytesOpcodes[0x1d] = std::make_shared<RegisterRotateRight>(&Cpu::hl, true);
  twoBytesOpcodes[0x1e] = std::make_shared<RegisterInstructionOnDereferencedHl<RegisterRotateRight>>();
  twoBytesOpcodes[0x1f] = std::make_shared<RegisterRotateRight>(&Cpu::af, false);

  twoBytesOpcodes[0x20] = std::make_shared<RegisterShiftLeft>(&Cpu::bc, false);
  twoBytesOpcodes[0x21] = std::make_shared<RegisterShiftLeft>(&Cpu::bc, true);
  twoBytesOpcodes[0x22] = std::make_shared<RegisterShiftLeft>(&Cpu::de, false);
  twoBytesOpcodes[0x23] = std::make_shared<RegisterShiftLeft>(&Cpu::de, true);
  twoBytesOpcodes[0x24] = std::make_shared<RegisterShiftLeft>(&Cpu::hl, false);
  twoBytesOpcodes[0x25] = std::make_shared<RegisterShiftLeft>(&Cpu::hl, true);
  twoBytesOpcodes[0x26] = std::make_shared<RegisterInstructionOnDereferencedHl<RegisterShiftLeft>>();
  twoBytesOpcodes[0x27] = std::make_shared<RegisterShiftLeft>(&Cpu::af, false);
  twoBytesOpcodes[0x28] = std::make_shared<RegisterShiftRight<true>>(&Cpu::bc, false);
  twoBytesOpcodes[0x29] = std::make_shared<RegisterShiftRight<true>>(&Cpu::bc, true);
  twoBytesOpcodes[0x2a] = std::make_shared<RegisterShiftRight<true>>(&Cpu::de, false);
  twoBytesOpcodes[0x2b] = std::make_shared<RegisterShiftRight<true>>(&Cpu::de, true);
  twoBytesOpcodes[0x2c] = std::make_shared<RegisterShiftRight<true>>(&Cpu::hl, false);
  twoBytesOpcodes[0x2d] = std::make_shared<RegisterShiftRight<true>>(&Cpu::hl, true);
  twoBytesOpcodes[0x2e] = std::make_shared<RegisterInstructionOnDereferencedHl<RegisterShiftRight<true>>>();
  twoBytesOpcodes[0x2f] = std::make_shared<RegisterShiftRight<true>>(&Cpu::af, false);

  twoBytesOpcodes[0x30] = std::make_shared<Swap>(&Cpu::bc, false);
  twoBytesOpcodes[0x31] = std::make_shared<Swap>(&Cpu::bc, true);
  twoBytesOpcodes[0x32] = std::make_shared<Swap>(&Cpu::de, false);
  twoBytesOpcodes[0x33] = std::make_shared<Swap>(&Cpu::de, true);
  twoBytesOpcodes[0x34] = std::make_shared<Swap>(&Cpu::hl, false);
  twoBytesOpcodes[0x35] = std::make_shared<Swap>(&Cpu::hl, true);
  twoBytesOpcodes[0x36] = std::make_shared<RegisterInstructionOnDereferencedHl<Swap>>();
  twoBytesOpcodes[0x37] = std::make_shared<Swap>(&Cpu::af, false);
  twoBytesOpcodes[0x38] = std::make_shared<RegisterShiftRight<false>>(&Cpu::bc, false);
  twoBytesOpcodes[0x39] = std::make_shared<RegisterShiftRight<false>>(&Cpu::bc, true);
  twoBytesOpcodes[0x3a] = std::make_shared<RegisterShiftRight<false>>(&Cpu::de, false);
  twoBytesOpcodes[0x3b] = std::make_shared<RegisterShiftRight<false>>(&Cpu::de, true);
  twoBytesOpcodes[0x3c] = std::make_shared<RegisterShiftRight<false>>(&Cpu::hl, false);
  twoBytesOpcodes[0x3d] = std::make_shared<RegisterShiftRight<false>>(&Cpu::hl, true);
  twoBytesOpcodes[0x3e] = std::make_shared<RegisterInstructionOnDereferencedHl<RegisterShiftRight<false>>>();
  twoBytesOpcodes[0x3f] = std::make_shared<RegisterShiftRight<false>>(&Cpu::af, false);  twoBytesOpcodes[0x40] = std::make_shared<GetBit<0>>(&Cpu::bc, false);
  twoBytesOpcodes[0x41] = std::make_shared<GetBit<0>>(&Cpu::bc, true);
  twoBytesOpcodes[0x42] = std::make_shared<GetBit<0>>(&Cpu::de, false);
  twoBytesOpcodes[0x43] = std::make_shared<GetBit<0>>(&Cpu::de, true);
  twoBytesOpcodes[0x44] = std::make_shared<GetBit<0>>(&Cpu::hl, false);
  twoBytesOpcodes[0x45] = std::make_shared<GetBit<0>>(&Cpu::hl, true);
  twoBytesOpcodes[0x46] = std::make_shared<RegisterInstructionOnDereferencedHl<GetBit<0>>>();
  twoBytesOpcodes[0x47] = std::make_shared<GetBit<0>>(&Cpu::af, false);
  twoBytesOpcodes[0x48] = std::make_shared<GetBit<1>>(&Cpu::bc, false);
  twoBytesOpcodes[0x49] = std::make_shared<GetBit<1>>(&Cpu::bc, true);
  twoBytesOpcodes[0x4a] = std::make_shared<GetBit<1>>(&Cpu::de, false);
  twoBytesOpcodes[0x4b] = std::make_shared<GetBit<1>>(&Cpu::de, true);
  twoBytesOpcodes[0x4c] = std::make_shared<GetBit<1>>(&Cpu::hl, false);
  twoBytesOpcodes[0x4d] = std::make_shared<GetBit<1>>(&Cpu::hl, true);
  twoBytesOpcodes[0x4e] = std::make_shared<RegisterInstructionOnDereferencedHl<GetBit<1>>>();
  twoBytesOpcodes[0x4f] = std::make_shared<GetBit<1>>(&Cpu::af, false);

  twoBytesOpcodes[0x50] = std::make_shared<GetBit<2>>(&Cpu::bc, false);
  twoBytesOpcodes[0x51] = std::make_shared<GetBit<2>>(&Cpu::bc, true);
  twoBytesOpcodes[0x52] = std::make_shared<GetBit<2>>(&Cpu::de, false);
  twoBytesOpcodes[0x53] = std::make_shared<GetBit<2>>(&Cpu::de, true);
  twoBytesOpcodes[0x54] = std::make_shared<GetBit<2>>(&Cpu::hl, false);
  twoBytesOpcodes[0x55] = std::make_shared<GetBit<2>>(&Cpu::hl, true);
  twoBytesOpcodes[0x56] = std::make_shared<RegisterInstructionOnDereferencedHl<GetBit<2>>>();
  twoBytesOpcodes[0x57] = std::make_shared<GetBit<2>>(&Cpu::af, false);
  twoBytesOpcodes[0x58] = std::make_shared<GetBit<3>>(&Cpu::bc, false);
  twoBytesOpcodes[0x59] = std::make_shared<GetBit<3>>(&Cpu::bc, true);
  twoBytesOpcodes[0x5a] = std::make_shared<GetBit<3>>(&Cpu::de, false);
  twoBytesOpcodes[0x5b] = std::make_shared<GetBit<3>>(&Cpu::de, true);
  twoBytesOpcodes[0x5c] = std::make_shared<GetBit<3>>(&Cpu::hl, false);
  twoBytesOpcodes[0x5d] = std::make_shared<GetBit<3>>(&Cpu::hl, true);
  twoBytesOpcodes[0x5e] = std::make_shared<RegisterInstructionOnDereferencedHl<GetBit<3>>>();
  twoBytesOpcodes[0x5f] = std::make_shared<GetBit<3>>(&Cpu::af, false);

  twoBytesOpcodes[0x60] = std::make_shared<GetBit<4>>(&Cpu::bc, false);
  twoBytesOpcodes[0x61] = std::make_shared<GetBit<4>>(&Cpu::bc, true);
  twoBytesOpcodes[0x62] = std::make_shared<GetBit<4>>(&Cpu::de, false);
  twoBytesOpcodes[0x63] = std::make_shared<GetBit<4>>(&Cpu::de, true);
  twoBytesOpcodes[0x64] = std::make_shared<GetBit<4>>(&Cpu::hl, false);
  twoBytesOpcodes[0x65] = std::make_shared<GetBit<4>>(&Cpu::hl, true);
  twoBytesOpcodes[0x66] = std::make_shared<RegisterInstructionOnDereferencedHl<GetBit<4>>>();
  twoBytesOpcodes[0x67] = std::make_shared<GetBit<4>>(&Cpu::af, false);
  twoBytesOpcodes[0x68] = std::make_shared<GetBit<5>>(&Cpu::bc, false);
  twoBytesOpcodes[0x69] = std::make_shared<GetBit<5>>(&Cpu::bc, true);
  twoBytesOpcodes[0x6a] = std::make_shared<GetBit<5>>(&Cpu::de, false);
  twoBytesOpcodes[0x6b] = std::make_shared<GetBit<5>>(&Cpu::de, true);
  twoBytesOpcodes[0x6c] = std::make_shared<GetBit<5>>(&Cpu::hl, false);
  twoBytesOpcodes[0x6d] = std::make_shared<GetBit<5>>(&Cpu::hl, true);
  twoBytesOpcodes[0x6e] = std::make_shared<RegisterInstructionOnDereferencedHl<GetBit<5>>>();
  twoBytesOpcodes[0x6f] = std::make_shared<GetBit<5>>(&Cpu::af, false);

  twoBytesOpcodes[0x70] = std::make_shared<GetBit<6>>(&Cpu::bc, false);
  twoBytesOpcodes[0x71] = std::make_shared<GetBit<6>>(&Cpu::bc, true);
  twoBytesOpcodes[0x72] = std::make_shared<GetBit<6>>(&Cpu::de, false);
  twoBytesOpcodes[0x73] = std::make_shared<GetBit<6>>(&Cpu::de, true);
  twoBytesOpcodes[0x74] = std::make_shared<GetBit<6>>(&Cpu::hl, false);
  twoBytesOpcodes[0x75] = std::make_shared<GetBit<6>>(&Cpu::hl, true);
  twoBytesOpcodes[0x76] = std::make_shared<RegisterInstructionOnDereferencedHl<GetBit<6>>>();
  twoBytesOpcodes[0x77] = std::make_shared<GetBit<6>>(&Cpu::af, false);
  twoBytesOpcodes[0x78] = std::make_shared<GetBit<7>>(&Cpu::bc, false);
  twoBytesOpcodes[0x79] = std::make_shared<GetBit<7>>(&Cpu::bc, true);
  twoBytesOpcodes[0x7a] = std::make_shared<GetBit<7>>(&Cpu::de, false);
  twoBytesOpcodes[0x7b] = std::make_shared<GetBit<7>>(&Cpu::de, true);
  twoBytesOpcodes[0x7c] = std::make_shared<GetBit<7>>(&Cpu::hl, false);
  twoBytesOpcodes[0x7d] = std::make_shared<GetBit<7>>(&Cpu::hl, true);
  twoBytesOpcodes[0x7e] = std::make_shared<RegisterInstructionOnDereferencedHl<GetBit<7>>>();
  twoBytesOpcodes[0x7f] = std::make_shared<GetBit<7>>(&Cpu::af, false);

  twoBytesOpcodes[0x80] = std::make_shared<Clear<0>>(&Cpu::bc, false);
  twoBytesOpcodes[0x81] = std::make_shared<Clear<0>>(&Cpu::bc, true);
  twoBytesOpcodes[0x82] = std::make_shared<Clear<0>>(&Cpu::de, false);
  twoBytesOpcodes[0x83] = std::make_shared<Clear<0>>(&Cpu::de, true);
  twoBytesOpcodes[0x84] = std::make_shared<Clear<0>>(&Cpu::hl, false);
  twoBytesOpcodes[0x85] = std::make_shared<Clear<0>>(&Cpu::hl, true);
  twoBytesOpcodes[0x86] = std::make_shared<RegisterInstructionOnDereferencedHl<Clear<0>>>();
  twoBytesOpcodes[0x87] = std::make_shared<Clear<0>>(&Cpu::af, false);
  twoBytesOpcodes[0x88] = std::make_shared<Clear<1>>(&Cpu::bc, false);
  twoBytesOpcodes[0x89] = std::make_shared<Clear<1>>(&Cpu::bc, true);
  twoBytesOpcodes[0x8a] = std::make_shared<Clear<1>>(&Cpu::de, false);
  twoBytesOpcodes[0x8b] = std::make_shared<Clear<1>>(&Cpu::de, true);
  twoBytesOpcodes[0x8c] = std::make_shared<Clear<1>>(&Cpu::hl, false);
  twoBytesOpcodes[0x8d] = std::make_shared<Clear<1>>(&Cpu::hl, true);
  twoBytesOpcodes[0x8e] = std::make_shared<RegisterInstructionOnDereferencedHl<Clear<1>>>();
  twoBytesOpcodes[0x8f] = std::make_shared<Clear<1>>(&Cpu::af, false);

  twoBytesOpcodes[0x90] = std::make_shared<Clear<2>>(&Cpu::bc, false);
  twoBytesOpcodes[0x91] = std::make_shared<Clear<2>>(&Cpu::bc, true);
  twoBytesOpcodes[0x92] = std::make_shared<Clear<2>>(&Cpu::de, false);
  twoBytesOpcodes[0x93] = std::make_shared<Clear<2>>(&Cpu::de, true);
  twoBytesOpcodes[0x94] = std::make_shared<Clear<2>>(&Cpu::hl, false);
  twoBytesOpcodes[0x95] = std::make_shared<Clear<2>>(&Cpu::hl, true);
  twoBytesOpcodes[0x96] = std::make_shared<RegisterInstructionOnDereferencedHl<Clear<2>>>();
  twoBytesOpcodes[0x97] = std::make_shared<Clear<2>>(&Cpu::af, false);
  twoBytesOpcodes[0x98] = std::make_shared<Clear<3>>(&Cpu::bc, false);
  twoBytesOpcodes[0x99] = std::make_shared<Clear<3>>(&Cpu::bc, true);
  twoBytesOpcodes[0x9a] = std::make_shared<Clear<3>>(&Cpu::de, false);
  twoBytesOpcodes[0x9b] = std::make_shared<Clear<3>>(&Cpu::de, true);
  twoBytesOpcodes[0x9c] = std::make_shared<Clear<3>>(&Cpu::hl, false);
  twoBytesOpcodes[0x9d] = std::make_shared<Clear<3>>(&Cpu::hl, true);
  twoBytesOpcodes[0x9e] = std::make_shared<RegisterInstructionOnDereferencedHl<Clear<3>>>();
  twoBytesOpcodes[0x9f] = std::make_shared<Clear<3>>(&Cpu::af, false);

  twoBytesOpcodes[0xa0] = std::make_shared<Clear<4>>(&Cpu::bc, false);
  twoBytesOpcodes[0xa1] = std::make_shared<Clear<4>>(&Cpu::bc, true);
  twoBytesOpcodes[0xa2] = std::make_shared<Clear<4>>(&Cpu::de, false);
  twoBytesOpcodes[0xa3] = std::make_shared<Clear<4>>(&Cpu::de, true);
  twoBytesOpcodes[0xa4] = std::make_shared<Clear<4>>(&Cpu::hl, false);
  twoBytesOpcodes[0xa5] = std::make_shared<Clear<4>>(&Cpu::hl, true);
  twoBytesOpcodes[0xa6] = std::make_shared<RegisterInstructionOnDereferencedHl<Clear<4>>>();
  twoBytesOpcodes[0xa7] = std::make_shared<Clear<4>>(&Cpu::af, false);
  twoBytesOpcodes[0xa8] = std::make_shared<Clear<5>>(&Cpu::bc, false);
  twoBytesOpcodes[0xa9] = std::make_shared<Clear<5>>(&Cpu::bc, true);
  twoBytesOpcodes[0xaa] = std::make_shared<Clear<5>>(&Cpu::de, false);
  twoBytesOpcodes[0xab] = std::make_shared<Clear<5>>(&Cpu::de, true);
  twoBytesOpcodes[0xac] = std::make_shared<Clear<5>>(&Cpu::hl, false);
  twoBytesOpcodes[0xad] = std::make_shared<Clear<5>>(&Cpu::hl, true);
  twoBytesOpcodes[0xae] = std::make_shared<RegisterInstructionOnDereferencedHl<Clear<5>>>();
  twoBytesOpcodes[0xaf] = std::make_shared<Clear<5>>(&Cpu::af, false);

  twoBytesOpcodes[0xb0] = std::make_shared<Clear<6>>(&Cpu::bc, false);
  twoBytesOpcodes[0xb1] = std::make_shared<Clear<6>>(&Cpu::bc, true);
  twoBytesOpcodes[0xb2] = std::make_shared<Clear<6>>(&Cpu::de, false);
  twoBytesOpcodes[0xb3] = std::make_shared<Clear<6>>(&Cpu::de, true);
  twoBytesOpcodes[0xb4] = std::make_shared<Clear<6>>(&Cpu::hl, false);
  twoBytesOpcodes[0xb5] = std::make_shared<Clear<6>>(&Cpu::hl, true);
  twoBytesOpcodes[0xb6] = std::make_shared<RegisterInstructionOnDereferencedHl<Clear<6>>>();
  twoBytesOpcodes[0xb7] = std::make_shared<Clear<6>>(&Cpu::af, false);
  twoBytesOpcodes[0xb8] = std::make_shared<Clear<7>>(&Cpu::bc, false);
  twoBytesOpcodes[0xb9] = std::make_shared<Clear<7>>(&Cpu::bc, true);
  twoBytesOpcodes[0xba] = std::make_shared<Clear<7>>(&Cpu::de, false);
  twoBytesOpcodes[0xbb] = std::make_shared<Clear<7>>(&Cpu::de, true);
  twoBytesOpcodes[0xbc] = std::make_shared<Clear<7>>(&Cpu::hl, false);
  twoBytesOpcodes[0xbd] = std::make_shared<Clear<7>>(&Cpu::hl, true);
  twoBytesOpcodes[0xbe] = std::make_shared<RegisterInstructionOnDereferencedHl<Clear<7>>>();
  twoBytesOpcodes[0xbf] = std::make_shared<Clear<7>>(&Cpu::af, false);

  twoBytesOpcodes[0xc0] = std::make_shared<Set<0>>(&Cpu::bc, false);
  twoBytesOpcodes[0xc1] = std::make_shared<Set<0>>(&Cpu::bc, true);
  twoBytesOpcodes[0xc2] = std::make_shared<Set<0>>(&Cpu::de, false);
  twoBytesOpcodes[0xc3] = std::make_shared<Set<0>>(&Cpu::de, true);
  twoBytesOpcodes[0xc4] = std::make_shared<Set<0>>(&Cpu::hl, false);
  twoBytesOpcodes[0xc5] = std::make_shared<Set<0>>(&Cpu::hl, true);
  twoBytesOpcodes[0xc6] = std::make_shared<RegisterInstructionOnDereferencedHl<Set<0>>>();
  twoBytesOpcodes[0xc7] = std::make_shared<Set<0>>(&Cpu::af, false);
  twoBytesOpcodes[0xc8] = std::make_shared<Set<1>>(&Cpu::bc, false);
  twoBytesOpcodes[0xc9] = std::make_shared<Set<1>>(&Cpu::bc, true);
  twoBytesOpcodes[0xca] = std::make_shared<Set<1>>(&Cpu::de, false);
  twoBytesOpcodes[0xcb] = std::make_shared<Set<1>>(&Cpu::de, true);
  twoBytesOpcodes[0xcc] = std::make_shared<Set<1>>(&Cpu::hl, false);
  twoBytesOpcodes[0xcd] = std::make_shared<Set<1>>(&Cpu::hl, true);
  twoBytesOpcodes[0xce] = std::make_shared<RegisterInstructionOnDereferencedHl<Set<1>>>();
  twoBytesOpcodes[0xcf] = std::make_shared<Set<1>>(&Cpu::af, false);

  twoBytesOpcodes[0xd0] = std::make_shared<Set<2>>(&Cpu::bc, false);
  twoBytesOpcodes[0xd1] = std::make_shared<Set<2>>(&Cpu::bc, true);
  twoBytesOpcodes[0xd2] = std::make_shared<Set<2>>(&Cpu::de, false);
  twoBytesOpcodes[0xd3] = std::make_shared<Set<2>>(&Cpu::de, true);
  twoBytesOpcodes[0xd4] = std::make_shared<Set<2>>(&Cpu::hl, false);
  twoBytesOpcodes[0xd5] = std::make_shared<Set<2>>(&Cpu::hl, true);
  twoBytesOpcodes[0xd6] = std::make_shared<RegisterInstructionOnDereferencedHl<Set<2>>>();
  twoBytesOpcodes[0xd7] = std::make_shared<Set<2>>(&Cpu::af, false);
  twoBytesOpcodes[0xd8] = std::make_shared<Set<3>>(&Cpu::bc, false);
  twoBytesOpcodes[0xd9] = std::make_shared<Set<3>>(&Cpu::bc, true);
  twoBytesOpcodes[0xda] = std::make_shared<Set<3>>(&Cpu::de, false);
  twoBytesOpcodes[0xdb] = std::make_shared<Set<3>>(&Cpu::de, true);
  twoBytesOpcodes[0xdc] = std::make_shared<Set<3>>(&Cpu::hl, false);
  twoBytesOpcodes[0xdd] = std::make_shared<Set<3>>(&Cpu::hl, true);
  twoBytesOpcodes[0xde] = std::make_shared<RegisterInstructionOnDereferencedHl<Set<3>>>();
  twoBytesOpcodes[0xdf] = std::make_shared<Set<3>>(&Cpu::af, false);

  twoBytesOpcodes[0xe0] = std::make_shared<Set<4>>(&Cpu::bc, false);
  twoBytesOpcodes[0xe1] = std::make_shared<Set<4>>(&Cpu::bc, true);
  twoBytesOpcodes[0xe2] = std::make_shared<Set<4>>(&Cpu::de, false);
  twoBytesOpcodes[0xe3] = std::make_shared<Set<4>>(&Cpu::de, true);
  twoBytesOpcodes[0xe4] = std::make_shared<Set<4>>(&Cpu::hl, false);
  twoBytesOpcodes[0xe5] = std::make_shared<Set<4>>(&Cpu::hl, true);
  twoBytesOpcodes[0xe6] = std::make_shared<RegisterInstructionOnDereferencedHl<Set<4>>>();
  twoBytesOpcodes[0xe7] = std::make_shared<Set<4>>(&Cpu::af, false);
  twoBytesOpcodes[0xe8] = std::make_shared<Set<5>>(&Cpu::bc, false);
  twoBytesOpcodes[0xe9] = std::make_shared<Set<5>>(&Cpu::bc, true);
  twoBytesOpcodes[0xea] = std::make_shared<Set<5>>(&Cpu::de, false);
  twoBytesOpcodes[0xeb] = std::make_shared<Set<5>>(&Cpu::de, true);
  twoBytesOpcodes[0xec] = std::make_shared<Set<5>>(&Cpu::hl, false);
  twoBytesOpcodes[0xed] = std::make_shared<Set<5>>(&Cpu::hl, true);
  twoBytesOpcodes[0xee] = std::make_shared<RegisterInstructionOnDereferencedHl<Set<5>>>();
  twoBytesOpcodes[0xef] = std::make_shared<Set<5>>(&Cpu::af, false);

  twoBytesOpcodes[0xf0] = std::make_shared<Set<6>>(&Cpu::bc, false);
  twoBytesOpcodes[0xf1] = std::make_shared<Set<6>>(&Cpu::bc, true);
  twoBytesOpcodes[0xf2] = std::make_shared<Set<6>>(&Cpu::de, false);
  twoBytesOpcodes[0xf3] = std::make_shared<Set<6>>(&Cpu::de, true);
  twoBytesOpcodes[0xf4] = std::make_shared<Set<6>>(&Cpu::hl, false);
  twoBytesOpcodes[0xf5] = std::make_shared<Set<6>>(&Cpu::hl, true);
  twoBytesOpcodes[0xf6] = std::make_shared<RegisterInstructionOnDereferencedHl<Set<6>>>();
  twoBytesOpcodes[0xf7] = std::make_shared<Set<6>>(&Cpu::af, false);
  twoBytesOpcodes[0xf8] = std::make_shared<Set<7>>(&Cpu::bc, false);
  twoBytesOpcodes[0xf9] = std::make_shared<Set<7>>(&Cpu::bc, true);
  twoBytesOpcodes[0xfa] = std::make_shared<Set<7>>(&Cpu::de, false);
  twoBytesOpcodes[0xfb] = std::make_shared<Set<7>>(&Cpu::de, true);
  twoBytesOpcodes[0xfc] = std::make_shared<Set<7>>(&Cpu::hl, false);
  twoBytesOpcodes[0xfd] = std::make_shared<Set<7>>(&Cpu::hl, true);
  twoBytesOpcodes[0xfe] = std::make_shared<RegisterInstructionOnDereferencedHl<Set<7>>>();
  twoBytesOpcodes[0xff] = std::make_shared<Set<7>>(&Cpu::af, false);
}

std::shared_ptr<Instruction> InstructionsTable::get(const bool fromExtendedSet, const uint8_t opcode) {
  const auto table = fromExtendedSet ? twoBytesOpcodes : oneByteOpcodes;

  return table[opcode];
}
