#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP

#include <string>
#include <cstdint>

struct Cartridge {
  Cartridge(const std::string path);
  ~Cartridge();

  private:
    uint8_t rom[];
};

#endif
