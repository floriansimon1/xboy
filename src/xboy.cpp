#include <cstdlib>
#include <unistd.h>

#include "gameboy/gameboy.hpp"
#include "gui.hpp"

int main(int, char **) {
  Gui       gui;
  sf::Event event;
  Gameboy   gameboy;

  gameboy.gpu.screen = &gui;

  for (uint16_t i = 0; gui.window.isOpen(); i++) {
    gameboy.tick();

    // Polling event at each iteration is way too slow.
    if (!i) {
      while (gui.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          gui.window.close();
        }
      }
    }

    usleep(100000);
  }

  return EXIT_SUCCESS;
}
