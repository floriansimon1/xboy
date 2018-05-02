#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP

#include <cstdint>
#include <string>

struct Cartridge {
  Cartridge(const std::string path);
  ~Cartridge();

  uint8_t *rom;
};

#endif
