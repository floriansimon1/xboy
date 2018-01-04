#ifndef MMU_HPP
#define MMU_HPP

#include <cstdint>

struct Mmu {
  uint8_t memory[65536];

  void reset();
};

#endif

