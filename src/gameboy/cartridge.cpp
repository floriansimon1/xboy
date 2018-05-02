#include <fstream>

#include "cartridge.hpp"

constexpr auto maxRomSize = 0x200000;

Cartridge::Cartridge(const std::string path) {
  std::ifstream file(path, std::ios::binary);

  const size_t fileSize = file.rdbuf()->pubseekoff(0, file.end, file.in);

  const auto romSize = maxRomSize < fileSize ? maxRomSize : fileSize;

  rom = new uint8_t[romSize];

  file.read(reinterpret_cast<char*>(rom), fileSize);

  file.close();
}

Cartridge::~Cartridge() {
  delete[] rom;
}
