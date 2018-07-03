#include "gui.hpp"

constexpr float scale = 2;

Gui::Gui(): window(sf::VideoMode(screenWidth * scale, screenHeight * scale), "XBoy") {
}

void SfmlFrameBuffer::setPixel(Coordinate x, Coordinate y, const Color &color) {
  sf::Color sfmlPixel(color.red, color.green, color.blue);

  image.setPixel(x, y, sfmlPixel);
}

Color SfmlFrameBuffer::getPixel(Coordinate x, Coordinate y) const {
  const auto sfmlPixel = image.getPixel(x, y);

  return Color { sfmlPixel.r, sfmlPixel.g, sfmlPixel.b };
}

SfmlFrameBuffer::SfmlFrameBuffer() {
  image.create(screenWidth, screenHeight, sf::Color::Black);
}

FrameBuffer& Gui::getFrameBuffer() {
  return frameBuffer;
}

void Gui::display() {
  sf::Texture texture;

  texture.loadFromImage(frameBuffer.image);

  sf::Sprite sprite(texture);

  sprite.setPosition(0, 0);
  sprite.setScale(scale, scale);

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
