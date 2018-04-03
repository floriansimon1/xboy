#ifndef CPU_TYPES_HPP
#define CPU_TYPES_HPP

#include <experimental/optional>

typedef unsigned long long Tick;
typedef uint8_t            Pixel;
typedef unsigned short     Scanline;
typedef unsigned short     Coordinate;

typedef std::experimental::optional<Tick>     OptionalTick;
typedef std::experimental::optional<Scanline> OptionalScanline;

#endif
