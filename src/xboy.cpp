#include <cstdlib>
#include <unistd.h>

#include "gameboy/gameboy.hpp"
#include "gui.hpp"

int main(int, char **) {
  Gui       gui;
  sf::Event event;
  Gameboy   gameboy;

  gameboy.setScreen(&gui);

  while (gui.window.isOpen()) {
    Frame frame;

    gameboy.tick();

    while (gui.window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        gui.window.close();
      }
    }

    for (auto i = 0; i < screenWidth; i++) {
      for (auto j = 0; j < screenHeight; j++) {
        const auto pixel = (i + screenWidth * j);

        const uint8_t color = pixel % 256;

        frame[pixel * 4]     = color;
        frame[pixel * 4 + 1] = color;
        frame[pixel * 4 + 2] = color;
        frame[pixel * 4 + 3] = 255;
      }
    }

    gui.display(frame);

    usleep(100000);
  }

  return EXIT_SUCCESS;
}
