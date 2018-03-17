#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>

#include "gameboy/screen.hpp"

struct Gui: Screen {
  Gui();

  sf::RenderWindow window;
};

#endif
