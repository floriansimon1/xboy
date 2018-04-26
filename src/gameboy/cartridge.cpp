#include <algorithm>
#include <fstream>

#include "cartridge.hpp"

constexpr auto maxRomSize = 0x200000;

Cartridge::Cartridge(const std::string path) {
  std::ifstream file(path, std::ios::binary);

  const auto fileSize = file.rdbuf()->pubseekoff(0, file.end, file.in);

  rom = new uint8_t[std::min(maxRomSize, fileSize)];

  file.read(rom, fileSize);

  file.close();
}

Cartridge::~Cartridge() {
  delete[] rom;
}
