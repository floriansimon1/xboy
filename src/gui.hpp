#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>

#include "gameboy/screen.hpp"

struct Gui: Screen {
  Gui();

  sf::RenderWindow window;

  virtual void display(const Frame &frame) override;

  private:
    sf::Texture texture;
    sf::Sprite  sprite;
    sf::Image   image;
};

#endif
