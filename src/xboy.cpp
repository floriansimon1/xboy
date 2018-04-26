#include <cstdlib>
#include <memory>

#include "gameboy/gameboy.hpp"
#include "gui.hpp"

int main(int, char **) {
  Gui       gui;
  sf::Event event;
  Gameboy   gameboy;
  Cartridge cartridge("../tests/roms/cpu_instrs.gb");

  gameboy.cartridge  = &cartridge;
  gameboy.gpu.screen = &gui;

  for (uint16_t i = 0; gui.window.isOpen(); i++) {
    gameboy.tick(gui);

    // Polling events at each iteration is way too slow.
    if (!i) {
      while (gui.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          gui.window.close();
        }
      }
    }
  }

  return EXIT_SUCCESS;
}
