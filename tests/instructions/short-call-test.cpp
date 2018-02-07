#include <iostream>

#include "short-call-test.hpp"
#include "../../src/cpu/instructions/short-call.hpp"

ShortCallTest::ShortCallTest():
  Test("Short call instruction name")
{
}

bool ShortCallTest::run() {
  ShortCall i00(0);
  ShortCall i0a(10);
  ShortCall i10(0x10);

  if (i00.toString() != "RST 00h") {
    std::cout << "'RST 00h' != '" << i00.toString() << '\'' << std::endl;

    return false;
  }

  if (i0a.toString() != "RST 0ah") {
    std::cout << "'RST 0ah' != '" << i0a.toString() << '\'' << std::endl;

    return false;
  }

  if (i10.toString() != "RST 10h") {
    std::cout << "'RST 10h' != '" << i10.toString() << '\'' << std::endl;

    return false;
  }

  return true;
}
