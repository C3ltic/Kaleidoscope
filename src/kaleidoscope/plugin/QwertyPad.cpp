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

#include "Kaleidoscope-QwertyPad.h"

namespace kaleidoscope {
namespace plugin {

// public:
uint8_t QwertyPad::qwertyPadLayer;
cRGB QwertyPad::color = CRGB(160, 0, 0);
uint8_t QwertyPad::lock_hue = 170;

// private:
KeyAddr QwertyPad::qwertypadLayerToggleKeyAddr;
bool QwertyPad::qwertypadActive = false;

EventHandlerResult QwertyPad::onSetup(void) {
  return EventHandlerResult::OK;
}

void QwertyPad::setKeyboardLEDColors(void) {
  ::LEDControl.set_mode(::LEDControl.get_mode_index());

  for (auto key_addr : KeyAddr::all()) {
    Key k = Layer.lookupOnActiveLayer(key_addr);
    Key layer_key = Layer.getKey(qwertyPadLayer, key_addr);

    if (k == LockLayer(qwertyPadLayer)) {
      qwertypadLayerToggleKeyAddr = key_addr;
    }

    ::LEDControl.setCrgbAt(KeyAddr(key_addr), color);
  }

  if (qwertypadLayerToggleKeyAddr.isValid()) {
    cRGB lock_color = breath_compute(lock_hue);
    ::LEDControl.setCrgbAt(KeyAddr(qwertypadLayerToggleKeyAddr), lock_color);
  }
}

EventHandlerResult QwertyPad::afterEachCycle() {
  if (!Layer.isActive(qwertyPadLayer)) {
    if (qwertypadActive) {
      ::LEDControl.set_mode(::LEDControl.get_mode_index());
      qwertypadActive = false;
    }
  } else {
    if (!qwertypadActive)  {
      qwertypadActive = true;
    }
    setKeyboardLEDColors();
  }
  return EventHandlerResult::OK;
}

}
}

kaleidoscope::plugin::QwertyPad QwertyPad;
