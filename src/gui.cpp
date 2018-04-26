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

bool Gui::aIsPressed() const {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
}

bool Gui::bIsPressed() const {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

bool Gui::upIsPressed() const {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}

bool Gui::downIsPressed() const {
return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

bool Gui::leftIsPressed() const {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}

bool Gui::rightIsPressed() const {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

bool Gui::startIsPressed() const {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

bool Gui::selectIsPressed() const {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
}
