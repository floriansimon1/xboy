#ifndef CPU_TYPES_HPP
#define CPU_TYPES_HPP

#include <experimental/optional>

typedef unsigned long long Tick;
typedef unsigned short     Scanline;

typedef std::experimental::optional<Tick>     OptionalTick;
typedef std::experimental::optional<Scanline> OptionalScanline;

#endif
