#ifndef PROGRAM_READER_HPP
#define PROGRAM_READER_HPP

#include <cstdint>
#include <cstdlib>

constexpr size_t biosSize = 256;

struct Gameboy;

struct ProgramReader {
  virtual uint8_t read(const Gameboy &gameboy, uint16_t address) const = 0;
};

struct BiosProgramReader: ProgramReader {
  uint8_t read(const Gameboy &gameboy, uint16_t address) const override;
};

struct RomProgramReader: ProgramReader {
  uint8_t read(const Gameboy &gameboy, uint16_t address) const override;
};

#endif
