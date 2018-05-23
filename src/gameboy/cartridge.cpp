#include <fstream>
#include <iostream>

#include "cartridge.hpp"

constexpr auto maxRomSize = 0x200000;

Cartridge::Cartridge(const std::string path) {
  std::ifstream file(path, std::ios::binary);

  if (!file) {
    std::cout << path << std::endl;

    throw "Cannot open " + path;
  }

  const size_t fileSize = file.rdbuf()->pubseekoff(0, file.end, file.in);

  // Go back to the beginning of the file
  file.seekg(std::ios::beg);

  const auto romSize = maxRomSize < fileSize ? maxRomSize : fileSize;

  rom = new uint8_t[romSize];

  file.read(reinterpret_cast<char*>(rom), fileSize);

  file.close();
}

Cartridge::~Cartridge() {
  delete[] rom;
}
