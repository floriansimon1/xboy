#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP

#include <string>

struct Cartridge {
  Cartridge(const std::string path);
  ~Cartridge();

  private:
    char *rom;
};

#endif
