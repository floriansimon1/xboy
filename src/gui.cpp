#include "gui.hpp"

constexpr float scale = 2;

Gui::Gui(): window(sf::VideoMode(screenWidth * scale, screenHeight * scale), "XBoy") {
  sprite.setPosition(0, 0);
  sprite.setScale(scale, scale);
}

void Gui::display(const Frame &frame) {
  image.create(screenWidth, screenHeight, frame);

  texture.loadFromImage(image);

  sprite.setTexture(texture);

  window.draw(sprite);

  window.display();
}
