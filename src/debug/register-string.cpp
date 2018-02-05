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
    twoBytesRegisters[&Cpu::af] = "af";
    twoBytesRegisters[&Cpu::bc] = "bc";
    twoBytesRegisters[&Cpu::de] = "de";
    twoBytesRegisters[&Cpu::hl] = "hl";
    twoBytesRegisters[&Cpu::pc] = "pc";
    twoBytesRegisters[&Cpu::sp] = "sp";

    lowBytesRegisters[&Cpu::af] = "f";
    lowBytesRegisters[&Cpu::bc] = "c";
    lowBytesRegisters[&Cpu::de] = "e";
    lowBytesRegisters[&Cpu::hl] = "l";

    highBytesRegisters[&Cpu::af] = "a";
    highBytesRegisters[&Cpu::bc] = "b";
    highBytesRegisters[&Cpu::de] = "d";
    highBytesRegisters[&Cpu::hl] = "h";
  }

  prepared = true;

  auto &nameHash = (
    singleByte
    ? (low ? lowBytesRegisters : highBytesRegisters)
    : twoBytesRegisters
  );

  return nameHash[cpuRegister];
}

