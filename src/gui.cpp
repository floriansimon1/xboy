#include "gui.hpp"

constexpr float scale = 2;

Gui::Gui(): window(sf::VideoMode(screenWidth * scale, screenHeight * scale), "XBoy") {
  sprite.setPosition(0, 0);
  sprite.setScale(scale, scale);
}

void Gui::display(const FrameBuffer &frameBuffer) {
  image.create(screenWidth, screenHeight, frameBuffer);

  texture.loadFromImage(image);

  sprite.setTexture(texture);

  window.draw(sprite);

  window.display();
}
