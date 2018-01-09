#ifndef BIT_HPP
#define BIT_HPP

template <typename T> T setBit(const T value, unsigned short bit, bool enable) {
  auto flag = 1 << bit;

  if (enable) {
    return value | flag;
  } else {
    return (value | flag) ^ flag;
  }
}

#endif

