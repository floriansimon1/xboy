#ifndef INPUT_MEDIUM_HPP
#define INPUT_MEDIUM_HPP

struct InputMedium {
  virtual bool aIsPressed() const = 0;
  virtual bool bIsPressed() const = 0;
  virtual bool upIsPressed() const = 0;
  virtual bool downIsPressed() const = 0;
  virtual bool leftIsPressed() const = 0;
  virtual bool rightIsPressed() const = 0;
  virtual bool startIsPressed() const = 0;
  virtual bool selectIsPressed() const = 0;
};

#endif
