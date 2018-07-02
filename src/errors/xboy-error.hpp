#ifndef XBOY_ERROR_HPP
#define XBOY_ERROR_HPP

#include <string>

struct XboyError {
  std::string message;

  XboyError(std::string message): message(message) {
  }
};

#endif
