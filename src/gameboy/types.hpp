#ifndef CPU_TYPES_HPP
#define CPU_TYPES_HPP

#include <chrono>
#include <experimental/optional>

template <typename T> using Optional = std::experimental::optional<T>;

typedef unsigned long long                                          Tick;
typedef uint8_t                                                     Pixel;
typedef uint8_t                                                     Palette;
typedef unsigned short                                              Scanline;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;
typedef unsigned short                                              Coordinate;
typedef Optional<Tick>                                              OptionalTick;
typedef Optional<Scanline>                                          OptionalScanline;

#endif
