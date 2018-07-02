#include <cstring>
#include <cstdlib>
#include <memory>

#include "gameboy/gameboy.hpp"
#include "gui.hpp"

int main(int argc, char **argv) {
  Gui       gui;
  sf::Event event;
  Gameboy   gameboy;
  Cartridge cartridge("./tests/roms/cpu_instrs.gb");

  for (auto i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "--debug")) {
      gameboy.debug = true;

      break;
    }
  }

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
