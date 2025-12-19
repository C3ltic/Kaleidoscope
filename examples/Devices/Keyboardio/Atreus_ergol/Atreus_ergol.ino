/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018-2022  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-FirmwareVersion.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-DynamicMacros.h"
#include "Kaleidoscope-LayerNames.h"
#include "Atreus_ergol.h"

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

enum {
  MACRO_ERGOL,
  MACRO_VERSION_INFO
};

enum {
  ERGOL,
  NAV,
  SYS
};

// clang-format off
KEYMAPS(
  [ERGOL] = KEYMAP_STACKED
  (
     Key_fre_Q              ,Key_fre_C                ,Key_fre_O			    ,Key_fre_P                ,Key_fre_W
    ,Key_fre_A              ,Key_fre_S                ,Key_fre_E			    ,Key_fre_N                ,Key_fre_F
    ,Key_fre_Z              ,Key_fre_X                ,Key_fre_Minus	    ,Key_fre_V                ,Key_fre_B				    ,Key_Backtick
    ,Key_Esc                ,Key_Tab                  ,Key_LeftGui		    ,Key_LeftShift            ,Key_Backspace		    ,Key_LeftControl

                            ,Key_fre_J                ,Key_fre_M          ,Key_fre_D                ,Key_fre_DeadL        ,Key_fre_Y
                            ,Key_fre_L                ,Key_fre_R          ,Key_fre_T                ,Key_fre_I            ,Key_fre_U
    ,Key_Backslash          ,Key_fre_Period		      	,Key_fre_H			    ,Key_fre_G                ,Key_fre_Comma        ,Key_fre_K
    ,Key_LeftAlt            ,Key_Space				      	,MO(NAV)			      ,Key_fre_ALTGR            ,Key_Quote            ,Key_Enter
  ),

  [NAV] = KEYMAP_STACKED
  (
     Key_Tab                ,Key_Home                 ,Key_UpArrow          ,Key_End                  ,Key_PageUp
    ,Key_CapsLock           ,Key_LeftArrow            ,Key_DownArrow		    ,Key_RightArrow           ,Key_PageDown
    ,XXX                    ,Consumer_VolumeDecrement ,Consumer_Mute        ,Consumer_VolumeIncrement ,Key_Backspace      ,Key_fre_And
    ,Key_fre_Cut            ,Key_fre_Copy             ,Key_fre_Paste        ,Key_Insert               ,Key_Delete         ,XXX

                            ,Key_fre_Slash            ,Key_7                ,Key_8                    ,Key_9              ,Key_fre_Star
                            ,Key_fre_Minus            ,Key_4                ,Key_5                    ,Key_6              ,Key_Keypad0
    ,Key_fre_Add            ,Key_fre_Comma            ,Key_1                ,Key_2                    ,Key_3              ,Key_fre_Period
    ,Key_fre_Undo           ,Key_fre_Redo             ,XXX                  ,TG(SYS)                  ,Key_fre_Equals     ,Key_Enter
  ),

  [SYS] = KEYMAP_STACKED
  (
     Key_PrintScreen        ,Key_Home                 ,Key_UpArrow          ,Key_End                  ,Key_PageUp
    ,Key_ScrollLock         ,Key_LeftArrow            ,Key_DownArrow        ,Key_RightArrow           ,Key_PageDown
    ,M(MACRO_VERSION_INFO)	,XXX                      ,XXX                  ,XXX                      ,XXX                ,XXX
    ,Key_Esc                ,Key_Tab                  ,Key_LeftGui          ,Key_LeftShift            ,Key_Delete         ,Key_LeftControl

                            ,XXX                      ,Key_F7               ,Key_F8                   ,Key_F9             ,Key_F10
                            ,XXX                      ,Key_F4               ,Key_F5                   ,Key_F6             ,Key_F11
    ,Consumer_PlaySlashPause,XXX                      ,Key_F1               ,Key_F2                   ,Key_F3             ,Key_F12
    ,Key_LeftAlt            ,XXX                      ,XXX                  ,MoveToLayer(ERGOL)       ,XXX                ,XXX
  )
)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
  // ----------------------------------------------------------------------
  // Chrysalis plugins

  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion,

  // The LayerNames plugin allows Chrysalis to display - and edit - custom layer
  // names, to be shown instead of the default indexes.
  LayerNames,

  // ----------------------------------------------------------------------
  // Keystroke-handling plugins

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  Qukeys,

  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  SpaceCadet,
  SpaceCadetConfig,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  OneShot,
  OneShotConfig,
  EscapeOneShot,
  EscapeOneShotConfig,

  // The macros plugin adds support for macros
  Macros,

  // Enables dynamic, Chrysalis-editable macros.
  DynamicMacros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,
  MouseKeysConfig  //,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  // MagicCombo,

  // Enables the GeminiPR Stenography protocol. Unused by default, but with the
  // plugin enabled, it becomes configurable - and then usable - via Chrysalis.
  // GeminiPR,
);

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    switch (macro_id) {
    case MACRO_ERGOL:
      // This macro is currently unused, but is kept around for compatibility
      // reasons. We used to use it in place of `MoveToLayer(ERGOL)`, but no
      // longer do. We keep it so that if someone still has the old layout with
      // the macro in EEPROM, it will keep working after a firmware update.
      Layer.move(ERGOL);
      break;
    case MACRO_VERSION_INFO:
      Macros.type(PSTR("Keyboardio Atreus - Ergo-L - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
      break;
    default:
      break;
    }
  }
  return MACRO_NONE;
}

void setup() {
  Kaleidoscope.setup();
  EEPROMKeymap.setup(9);

  DynamicMacros.reserve_storage(48);

  LayerNames.reserve_storage(63);

  Layer.move(EEPROMSettings.default_layer());

  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();
}

void loop() {
  Kaleidoscope.loop();
}
