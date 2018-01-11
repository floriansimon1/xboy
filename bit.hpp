#ifndef BIT_HPP
#define BIT_HPP

#include <cstdint>

template <typename T> T setBit(const T value, unsigned short bit, bool enable) {
  auto flag = 1 << bit;

  if (enable) {
    return value | flag;
  } else {
    return (value | flag) ^ flag;
  }
}

template <typename T> T getBit(const T value, unsigned short bit) {
  return value & (1 << bit);
}

const uint16_t lowByteMask     = 0b11111111;
const uint8_t  lowHalfByteMask = 0b1111;

constexpr uint16_t highByteMask     = lowByteMask << 8;
constexpr uint8_t  highHalfByteMask = lowHalfByteMask << 4;

constexpr uint16_t maxUint16 = highByteMask | lowByteMask;

#endif
