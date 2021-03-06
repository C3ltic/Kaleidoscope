/* Kaleidoscope-NumPad - A NumPad plugin for Kaleidoscope.
 * Copyright (C) 2017-2018  Keyboard.io, Inc.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "Kaleidoscope-LEDControl.h"

namespace kaleidoscope {
namespace plugin {

class GamingPad : public kaleidoscope::Plugin {
 public:
  GamingPad(void) {}

  static uint8_t gamingPadLayer;
  static cRGB color;
  static uint8_t lock_hue;

  EventHandlerResult onSetup(void);
  EventHandlerResult afterEachCycle();

 private:

  void setKeyboardLEDColors(void);

  static KeyAddr gamingpadLayerToggleKeyAddr;
  static bool gamingpadActive;
};
}
}

extern kaleidoscope::plugin::GamingPad GamingPad;
