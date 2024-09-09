#pragma once

#include "barrier/KeyState.h"
/*#include "common/stdvector.h"*/

/*class Event;*/
/*class EventQueueTimer;*/
/*class MSWindowsDesks;*/
class IEventQueue;

class UsbKeyState : public KeyState {
public:
  UsbKeyState(IEventQueue *events);
  UsbKeyState(IEventQueue *events, barrier::KeyMap &keyMap);
  virtual ~UsbKeyState();

public:
  virtual bool fakeCtrlAltDel();
  virtual KeyModifierMask pollActiveModifiers() const;
  virtual SInt32 pollActiveGroup() const;
  virtual void pollPressedKeys(KeyButtonSet &pressedKeys) const;

protected:
  // KeyState overrides
  virtual void getKeyMap(barrier::KeyMap &keyMap);
  virtual void fakeKey(const Keystroke &keystroke);
};
