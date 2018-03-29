#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>

#include "gameboy/gpu/screen.hpp"

struct Gui: Screen {
  Gui();

  sf::RenderWindow window;

  virtual void display(const FrameBuffer &frameBuffer) override;

  private:
    sf::Texture texture;
    sf::Sprite  sprite;
    sf::Image   image;
};

#endif
