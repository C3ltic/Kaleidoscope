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

#include "Kaleidoscope-GamingPad.h"

namespace kaleidoscope {
namespace plugin {

// public:
uint8_t GamingPad::gamingPadLayer;
cRGB GamingPad::color = CRGB(160, 0, 0);
uint8_t GamingPad::lock_hue = 170;

// private:
KeyAddr GamingPad::gamingpadLayerToggleKeyAddr;
bool GamingPad::gamingpadActive = false;

EventHandlerResult GamingPad::onSetup(void) {
  return EventHandlerResult::OK;
}

void GamingPad::setKeyboardLEDColors(void) {
  ::LEDControl.set_mode(::LEDControl.get_mode_index());

  for (auto key_addr : KeyAddr::all()) {
    Key k = Layer.lookupOnActiveLayer(key_addr);
    Key layer_key = Layer.getKey(gamingPadLayer, key_addr);

    if (k == LockLayer(gamingPadLayer)) {
      gamingpadLayerToggleKeyAddr = key_addr;
    }

    ::LEDControl.setCrgbAt(KeyAddr(key_addr), color);
  }

  if (gamingpadLayerToggleKeyAddr.isValid()) {
    cRGB lock_color = breath_compute(lock_hue);
    ::LEDControl.setCrgbAt(KeyAddr(gamingpadLayerToggleKeyAddr), lock_color);
  }
}

EventHandlerResult GamingPad::afterEachCycle() {
  if (!Layer.isActive(gamingPadLayer)) {
    if (gamingpadActive) {
      ::LEDControl.set_mode(::LEDControl.get_mode_index());
      gamingpadActive = false;
    }
  } else {
    if (!gamingpadActive)  {
      gamingpadActive = true;
    }
    setKeyboardLEDColors();
  }
  return EventHandlerResult::OK;
}

}
}

kaleidoscope::plugin::GamingPad GamingPad;
