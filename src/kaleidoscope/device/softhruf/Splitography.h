/* -*- mode: c++ -*-
 * Kaleidoscope-Hardware-SOFTHRUF-Splitography -- Splitography hardware support for Kaleidoscope
 * Copyright (C) 2018, 2019  Keyboard.io, Inc
 *
 * Based on QMK (commit e9a67f8fd) and sdothum's fork (commit 8616b44)
 *  (C) Jack Humbert, Jun Wako, Steven Hum, and others
 * Original QMK sources:
 *  - keyboards/splitography/config.h
 *  - keyboards/splitography/splitography.h
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef ARDUINO_AVR_SPLITOGRAPHY

#define KALEIDOSCOPE_BOOTLOADER_FLIP_WORKAROUND 1

#include <Arduino.h>

#include "kaleidoscope/driver/keyscanner/AVR.h"
#include "kaleidoscope/driver/bootloader/avr/FLIP.h"
#include "kaleidoscope/device/ATMega32U4Keyboard.h"

namespace kaleidoscope {
namespace device {
namespace softhruf {

struct SplitographyProps : kaleidoscope::device::ATMega32U4KeyboardProps {
  struct KeyScannerProps : public kaleidoscope::driver::keyscanner::AVRProps {
    AVR_KEYSCANNER_PROPS(
      ROW_PIN_LIST({ PIN_D0, PIN_D1, PIN_D2, PIN_D3 }),
      COL_PIN_LIST({ PIN_F0, PIN_F1, PIN_F4, PIN_F5, PIN_F6, PIN_F7, PIN_C7, PIN_C6, PIN_B6, PIN_B5, PIN_B4, PIN_D7 })
    );
  };
  typedef kaleidoscope::driver::keyscanner::AVR<KeyScannerProps> KeyScanner;
  typedef kaleidoscope::driver::bootloader::avr::FLIP BootLoader;
};

class Splitography: public kaleidoscope::device::ATMega32U4Keyboard<SplitographyProps> {
 public:
  Splitography() {
    mcu_.disableJTAG();
  }
};

#define PER_KEY_DATA(dflt,                                                       \
      r0c0 ,r0c1 ,r0c2 ,r0c3 ,r0c4 ,r0c5   ,r0c6 ,r0c7 ,r0c8 ,r0c9 ,r0c10 ,r0c11   \
     ,r1c0 ,r1c1 ,r1c2 ,r1c3 ,r1c4 ,r1c5   ,r1c6 ,r1c7 ,r1c8 ,r1c9 ,r1c10 ,r1c11   \
     ,r2c0 ,r2c1 ,r2c2 ,r2c3 ,r2c4 ,r2c5   ,r2c6 ,r2c7 ,r2c8 ,r2c9 ,r2c10 ,r2c11   \
                             ,r3c4 ,r3c5   ,r3c6 ,r3c7                             \
  )                                                                                \
                                                                                   \
      r0c0 ,r0c1 ,r0c2 ,r0c3 ,r0c4 ,r0c5 , r0c6 ,r0c7 ,r0c8 ,r0c9 ,r0c10 ,r0c11,   \
      r1c0 ,r1c1 ,r1c2 ,r1c3 ,r1c4 ,r1c5 , r1c6 ,r1c7 ,r1c8 ,r1c9 ,r1c10 ,r1c11,   \
      r2c0 ,r2c1 ,r2c2 ,r2c3 ,r2c4 ,r2c5 , r2c6 ,r2c7 ,r2c8 ,r2c9 ,r2c10 ,r2c11,   \
      dflt ,dflt ,dflt ,dflt ,r3c4 ,r3c5  ,r3c6 ,r3c7 ,dflt ,dflt ,dflt  ,dflt

#define PER_KEY_DATA_STACKED(dflt,                                           \
      r0c0 ,r0c1 ,r0c2 ,r0c3 ,r0c4  ,r0c5                                      \
     ,r1c0 ,r1c1 ,r1c2 ,r1c3 ,r1c4  ,r1c5                                      \
     ,r2c0 ,r2c1 ,r2c2 ,r2c3 ,r2c4  ,r2c5                                      \
                             ,r3c4  ,r3c5                                      \
                                                                               \
     ,r0c6 ,r0c7 ,r0c8 ,r0c9 ,r0c10 ,r0c11                                     \
     ,r1c6 ,r1c7 ,r1c8 ,r1c9 ,r1c10 ,r1c11                                     \
     ,r2c6 ,r2c7 ,r2c8 ,r2c9 ,r2c10 ,r2c11                                     \
     ,r3c6 ,r3c7                                                               \
  )                                                                            \
    r0c0 ,r0c1 ,r0c2 ,r0c3 ,r0c4 ,r0c5 ,r0c6 ,r0c7 ,r0c8 ,r0c9 ,r0c10 ,r0c11,  \
    r1c0 ,r1c1 ,r1c2 ,r1c3 ,r1c4 ,r1c5 ,r1c6 ,r1c7 ,r1c8 ,r1c9 ,r1c10 ,r1c11,  \
    r2c0 ,r2c1 ,r2c2 ,r2c3 ,r2c4 ,r2c5 ,r2c6 ,r2c7 ,r2c8 ,r2c9 ,r2c10 ,r2c11,  \
    dflt ,dflt ,dflt ,dflt ,r3c4 ,r3c5 ,r3c6 ,r3c7 ,dflt ,dflt ,dflt  ,dflt

}
}

typedef kaleidoscope::device::softhruf::Splitography Device;

}

extern kaleidoscope::device::softhruf::Splitography DEPRECATED(NAMED_HARDWARE) &Splitography;

#endif
