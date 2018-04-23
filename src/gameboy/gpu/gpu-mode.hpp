#ifndef GPU_MODE_HPP
#define GPU_MODE_HPP

namespace Gpu {
  enum Mode {
    Hblank     = 0,
    Vblank     = 1,
    OamAccess  = 2,
    VramAccess = 3
  };
}

#endif
