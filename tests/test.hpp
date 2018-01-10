#ifndef TEST_HPP
#define TEST_HPP

struct Test {
  const char *name;

  virtual bool run() = 0;

  Test(const char *name);
};

#endif
