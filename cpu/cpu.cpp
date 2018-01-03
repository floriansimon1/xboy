#include "cpu.hpp"

Cpu::Cpu() {
  reset();
}

void Cpu::reset() {
  af = 0;
  bc = 0;
  de = 0;
  hl = 0;
  sp = 0;
  pc = 0;
}

