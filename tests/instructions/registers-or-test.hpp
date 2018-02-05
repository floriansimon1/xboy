#ifndef REGISTERS_OR_TEST_HPP
#define REGISTERS_OR_TEST_HPP

#include "../test.hpp"

struct RegistersOrTest: Test {
  RegistersOrTest();

  bool run() override;

  private:
    bool runOrTests() const;
    bool runXorTests() const;
};

#endif
