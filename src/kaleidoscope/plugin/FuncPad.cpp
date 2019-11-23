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

#include "Kaleidoscope-FuncPad.h"

namespace kaleidoscope {
namespace plugin {

// public:
uint8_t FuncPad::funcPadLayer;
cRGB FuncPad::color = CRGB(160, 0, 0);
uint8_t FuncPad::lock_hue = 170;

// private:
KeyAddr FuncPad::funcpadLayerToggleKeyAddr;
bool FuncPad::funcpadActive = false;

EventHandlerResult FuncPad::onSetup(void) {
  return EventHandlerResult::OK;
}

void FuncPad::setKeyboardLEDColors(void) {
  ::LEDControl.set_mode(::LEDControl.get_mode_index());

  for (auto key_addr : KeyAddr::all()) {
    Key k = Layer.lookupOnActiveLayer(key_addr);
    Key layer_key = Layer.getKey(funcPadLayer, key_addr);

    if (k == LockLayer(funcPadLayer)) {
      funcpadLayerToggleKeyAddr = key_addr;
    }

    if ((k != layer_key) || (k == Key_NoKey) || (k.flags != KEY_FLAGS)) {
      ::LEDControl.refreshAt(KeyAddr(key_addr));
    } else {
      ::LEDControl.setCrgbAt(KeyAddr(key_addr), color);
    }
  }

  if (funcpadLayerToggleKeyAddr.isValid()) {
    cRGB lock_color = breath_compute(lock_hue);
    ::LEDControl.setCrgbAt(KeyAddr(funcpadLayerToggleKeyAddr), lock_color);
  }
}

EventHandlerResult FuncPad::afterEachCycle() {
  if (!Layer.isActive(funcPadLayer)) {
    if (funcpadActive) {
      ::LEDControl.set_mode(::LEDControl.get_mode_index());
      funcpadActive = false;
    }
  } else {
    if (!funcpadActive)  {
      funcpadActive = true;
    }
    setKeyboardLEDColors();
  }
  return EventHandlerResult::OK;
}

}
}

kaleidoscope::plugin::FuncPad FuncPad;
