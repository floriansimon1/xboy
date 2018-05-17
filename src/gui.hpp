#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>

#include "gameboy/gpu/screen.hpp"
#include "gameboy/joypad/input-medium.hpp"

struct SfmlFrameBuffer: FrameBuffer {
  void setPixel(Coordinate x, Coordinate y, const Color &color) override;
  Color getPixel(Coordinate x, Coordinate y) const override;
  SfmlFrameBuffer();

  sf::Image image;
};

struct Gui: Screen, InputMedium {
  Gui();

  sf::RenderWindow window;

  virtual void display() override;
  virtual FrameBuffer &getFrameBuffer() override;

  virtual bool aIsPressed() const override;
  virtual bool bIsPressed() const override;
  virtual bool upIsPressed() const override;
  virtual bool downIsPressed() const override;
  virtual bool leftIsPressed() const override;
  virtual bool rightIsPressed() const override;
  virtual bool startIsPressed() const override;
  virtual bool selectIsPressed() const override;

  private:
    SfmlFrameBuffer frameBuffer;
};

#endif
