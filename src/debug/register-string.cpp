#include <unordered_map>

#include "register-string.hpp"

using namespace std;

// Pointer-to-members cannot be cast to numbers.
static Cpu dummyCpu;

struct CpuRegisterPointerHasher {
  size_t operator()(CpuRegisterPointer pointer) const {
    return reinterpret_cast<size_t>(&(dummyCpu.*pointer));
  }
};

typedef unordered_map<CpuRegisterPointer, const char*, CpuRegisterPointerHasher> RegisterNameHash;

static RegisterNameHash twoBytesRegisters;
static RegisterNameHash lowBytesRegisters;
static RegisterNameHash highBytesRegisters;

const char* registerString(CpuRegisterPointer cpuRegister, bool singleByte, bool low) {
  static bool prepared = false;

  if (!prepared) {
    twoBytesRegisters[&Cpu::af] = "AF";
    twoBytesRegisters[&Cpu::bc] = "BC";
    twoBytesRegisters[&Cpu::de] = "DE";
    twoBytesRegisters[&Cpu::hl] = "HL";
    twoBytesRegisters[&Cpu::pc] = "PC";
    twoBytesRegisters[&Cpu::sp] = "SP";

    lowBytesRegisters[&Cpu::af] = "F";
    lowBytesRegisters[&Cpu::bc] = "C";
    lowBytesRegisters[&Cpu::de] = "E";
    lowBytesRegisters[&Cpu::hl] = "L";

    highBytesRegisters[&Cpu::af] = "A";
    highBytesRegisters[&Cpu::bc] = "B";
    highBytesRegisters[&Cpu::de] = "D";
    highBytesRegisters[&Cpu::hl] = "H";
  }

  prepared = true;

  auto &nameHash = (
    singleByte
    ? (low ? lowBytesRegisters : highBytesRegisters)
    : twoBytesRegisters
  );

  return nameHash[cpuRegister];
}
