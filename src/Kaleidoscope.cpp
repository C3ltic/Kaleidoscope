#include "Kaleidoscope.h"
#include <stdarg.h>

Kaleidoscope_::eventHandlerHook Kaleidoscope_::eventHandlers[HOOK_MAX];
Kaleidoscope_::loopHook Kaleidoscope_::loopHooks[HOOK_MAX];

Kaleidoscope_::Kaleidoscope_(void) {
}

void
Kaleidoscope_::setup(void) {
  KeyboardHardware.setup();
#ifndef HARDWARE_EVENT_DISPATCHER
  /** KALEIDOSCOPE_HARDWARE_H is expected to define HARDWARE_EVENT_DISPATCHER
   * if it has registered a dispatcher.  The goal is to remove this once
   * all of the hardware implementations have been updated to register
   * their dispatchers.
   * The purpose of this block is to ensure that the default implementation
   * is linked in, as it is otherwise unreferenced. */
  defaultHIDDispatcher.begin();
#endif

  EventDispatcher::eventDispatchers()
      .apply([](EventDispatcher *disp) {
               disp->begin();
             });

  // A workaround, so that the compiler does not optimize handleKeyswitchEvent out...
  // This is a no-op, but tricks the compiler into not being too helpful
  // TODO(anyone): figure out how to hint the compiler in a more reasonable way
  handleKeyswitchEvent(Key_NoKey, 255, 255, 0);

  // Update the keymap cache, so we start with a non-empty state.
  Layer.updateActiveLayers();
  for (byte row = 0; row < ROWS; row++) {
    for (byte col = 0; col < COLS; col++) {
      Layer.updateLiveCompositeKeymap(row, col);
    }
  }
}

void
Kaleidoscope_::loop(void) {
  // Re-probe available endpoints.  We could adjust this so that
  // it only happens once per second or ideally is triggered
  // by connectivity changes.
  connectionMask = 0;
  EventDispatcher::eventDispatchers().apply([=](
      EventDispatcher *disp) { disp->queryConnectionTypes(connectionMask); });

  KeyboardHardware.scanMatrix();

  for (byte i = 0; loopHooks[i] != NULL && i < HOOK_MAX; i++) {
    loopHook hook = loopHooks[i];
    (*hook)(false);
  }

  kaleidoscope::hid::sendKeyboardReport();
  kaleidoscope::hid::releaseAllKeys();

  for (byte i = 0; loopHooks[i] != NULL && i < HOOK_MAX; i++) {
    loopHook hook = loopHooks[i];
    (*hook)(true);
  }
}

void
Kaleidoscope_::replaceEventHandlerHook(eventHandlerHook oldHook, eventHandlerHook newHook) {
  for (byte i = 0; i < HOOK_MAX; i++) {
    if (eventHandlers[i] == oldHook) {
      eventHandlers[i] = newHook;
      return;
    }
  }
}

void
Kaleidoscope_::appendEventHandlerHook(eventHandlerHook hook) {
  replaceEventHandlerHook((eventHandlerHook)NULL, hook);
}

void
Kaleidoscope_::useEventHandlerHook(eventHandlerHook hook) {
  for (byte i = 0; i < HOOK_MAX; i++) {
    if (eventHandlers[i] == hook)
      return;
  }
  appendEventHandlerHook(hook);
}

void
Kaleidoscope_::replaceLoopHook(loopHook oldHook, loopHook newHook) {
  for (byte i = 0; i < HOOK_MAX; i++) {
    if (loopHooks[i] == oldHook) {
      loopHooks[i] = newHook;
      return;
    }
  }
}

void
Kaleidoscope_::appendLoopHook(loopHook hook) {
  replaceLoopHook((loopHook)NULL, hook);
}

void
Kaleidoscope_::useLoopHook(loopHook hook) {
  for (byte i = 0; i < HOOK_MAX; i++) {
    if (loopHooks[i] == hook)
      return;
  }
  appendLoopHook(hook);
}

bool
Kaleidoscope_::focusHook(const char *command) {
  enum {
    ON,
    OFF,
    GETSTATE,
  } subCommand;

  if (strncmp_P(command, PSTR("layer."), 6) != 0)
    return false;

  if (strcmp_P(command + 6, PSTR("on")) == 0)
    subCommand = ON;
  else if (strcmp_P(command + 6, PSTR("off")) == 0)
    subCommand = OFF;
  else if (strcmp_P(command + 6, PSTR("getState")) == 0)
    subCommand = GETSTATE;
  else
    return false;

  switch (subCommand) {
  case ON: {
    uint8_t layer = Serial.parseInt();
    Layer.on(layer);
    break;
  }

  case OFF: {
    uint8_t layer = Serial.parseInt();
    Layer.off(layer);
    break;
  }

  case GETSTATE:
    Serial.println(Layer.getLayerState(), BIN);
    break;
  }

  return true;
}

Kaleidoscope_ Kaleidoscope;

/* Deprecated functions */

void event_handler_hook_use(Kaleidoscope_::eventHandlerHook hook) {
  Kaleidoscope.useEventHandlerHook(hook);
}

void loop_hook_use(Kaleidoscope_::loopHook hook) {
  Kaleidoscope.useLoopHook(hook);
}

void __USE_PLUGINS(KaleidoscopePlugin *plugin, ...) {
  va_list ap;

  Kaleidoscope.use(plugin);

  va_start(ap, plugin);
  while ((plugin = (KaleidoscopePlugin *)va_arg(ap, KaleidoscopePlugin *)) != NULL)
    Kaleidoscope.use(plugin);
  va_end(ap);
}
