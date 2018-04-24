#ifndef TIMER_FREQUENCIES_HPP
#define TIMER_FREQUENCIES_HPP

#include "../types.hpp"

constexpr Tick ticksPerSecond = 4194304;

constexpr unsigned int frequencyToTicks(const unsigned int frequency) {
  return ticksPerSecond / frequency;
}

constexpr unsigned int dividerTicks = frequencyToTicks(16384);

constexpr unsigned int incrementTicks[] = {
  frequencyToTicks(4096),
  frequencyToTicks(262144),
  frequencyToTicks(65536),
  frequencyToTicks(16384)
};

#endif
