#include "flag-string.hpp"
#include "../gameboy/cpu/cpu.hpp"

char flagString(unsigned short flag) {
  switch (flag) {
    case Cpu::carryFlag:     return 'C';
    case Cpu::halfCarryFlag: return 'H';
    case Cpu::subtractFlag:  return 'N';
    case Cpu::zeroFlag:      return 'Z';

    default: return '?';
  }
}
