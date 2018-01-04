#include <cstring>
#include <cstdint>

#include "mmu.hpp"
#include "../bios.hpp"

void Mmu::reset() {
  memset(memory, 0, sizeof(memory));
  memcpy(memory, bios, sizeof(bios));
}

