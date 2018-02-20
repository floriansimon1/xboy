#include "instructions/dereference-combined-into-single-increment.hpp"
#include "instructions/single-byte-register-to-memory-increment.hpp"
#include "instructions/write-two-bytes-register-to-address.hpp"
#include "instructions/subtract-memory-byte-to-register.hpp"
#include "instructions/dereference-combined-into-single.hpp"
#include "instructions/dereference-into-single-register.hpp"
#include "instructions/unsigned-registers-subtraction.hpp"
#include "instructions/single-byte-register-to-memory.hpp"
#include "instructions/two-bytes-registers-addition.hpp"
#include "instructions/add-memory-byte-to-register.hpp"
#include "instructions/unsigned-registers-addition.hpp"
#include "instructions/dereference-single-register.hpp"
#include "instructions/unsigned-immediate-addition.hpp"
#include "instructions/write-immediate-to-address.hpp"
#include "instructions/signed-immediate-addition.hpp"
#include "instructions/dereference-high-byte.hpp"
#include "instructions/return-from-interrupt.hpp"
#include "instructions/increment-dereference.hpp"
#include "instructions/single-byte-increment.hpp"
#include "instructions/a-rotate-right-carry.hpp"
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
#include "instructions/push-two-bytes.hpp"
#include "instructions/dereference-or.hpp"
#include "instructions/set-carry-flag.hpp"
#include "instructions/decimal-adjust.hpp"
#include "instructions/a-rotate-right.hpp"
#include "instructions/a-rotate-left.hpp"
#include "instructions/copy-register.hpp"
#include "instructions/pop-two-bytes.hpp"
#include "instructions/registers-and.hpp"
#include "instructions/registers-or.hpp"
#include "instructions/return-flag.hpp"
#include "instructions/short-call.hpp"
#include "instructions/unmapped.hpp"
#include "instructions/negate.hpp"
#include "instructions-table.hpp"
#include "instructions/jump.hpp"
#include "instructions/call.hpp"
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
  oneByteOpcodes[0xc1] = std::make_shared<PopTwoBytes>(&Cpu::bc);
  oneByteOpcodes[0xc2] = std::make_shared<Jump>(true, Cpu::zeroFlag, true);
  oneByteOpcodes[0xc3] = std::make_shared<Jump>(false);
  oneByteOpcodes[0xc4] = std::make_shared<Call>(true, Cpu::zeroFlag, true);
  oneByteOpcodes[0xc5] = std::make_shared<PushTwoBytes>(&Cpu::bc);
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
  oneByteOpcodes[0xd1] = std::make_shared<PopTwoBytes>(&Cpu::de);
  oneByteOpcodes[0xd2] = std::make_shared<Jump>(true, Cpu::carryFlag, true);
  oneByteOpcodes[0xd3] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xd4] = std::make_shared<Call>(true, Cpu::carryFlag, true);
  oneByteOpcodes[0xd5] = std::make_shared<PushTwoBytes>(&Cpu::de);
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

  oneByteOpcodes[0xe0] = std::make_shared<DereferenceHighByte>();
  oneByteOpcodes[0xe1] = std::make_shared<PopTwoBytes>(&Cpu::hl);
  oneByteOpcodes[0xe2] = std::make_shared<DereferenceIntoSingleRegister>(&Cpu::bc, true, &Cpu::af, false);
  oneByteOpcodes[0xe3] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xe4] = std::make_shared<Unmapped>();
  oneByteOpcodes[0xe5] = std::make_shared<PushTwoBytes>(&Cpu::hl);
  oneByteOpcodes[0xe6] = std::make_shared<ImmediateAnd>();
  oneByteOpcodes[0xe7] = std::make_shared<ShortCall>(0x20);
  oneByteOpcodes[0xe8] = std::make_shared<SignedImmediateAddition>();
  oneByteOpcodes[0xe9] = std::make_shared<DereferenceJump>();

  oneByteOpcodes[0xf1] = std::make_shared<PopTwoBytes>(&Cpu::hl);
  oneByteOpcodes[0xf2] = std::make_shared<DereferenceSingleRegister>(&Cpu::bc, true, &Cpu::af, false);
  oneByteOpcodes[0xf3] = std::make_shared<EnableInterrupts>(false);
}

std::shared_ptr<Instruction> InstructionsTable::get(const bool fromExtendedSet, const uint8_t opcode) {
  const auto table = fromExtendedSet ? twoBytesOpcodes : oneByteOpcodes;

  return table[opcode];
}
