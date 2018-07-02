#ifndef ROM_NOT_FOUND_ERROR_HPP
#define ROM_NOT_FOUND_ERROR_HPP

#include "./xboy-error.hpp"

struct RomNotFoundError: XboyError {
  RomNotFoundError(std::string path): XboyError("Could not open '" + path + "'!") {
  }
};

#endif
