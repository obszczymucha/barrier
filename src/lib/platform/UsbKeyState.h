#pragma once

#include "barrier/KeyState.h"

class UsbKeyState : public KeyState {
public:
  UsbKeyState(IEventQueue *events, barrier::KeyMap &keyMap);
  virtual ~UsbKeyState();

public:
  virtual bool fakeCtrlAltDel();
  virtual KeyModifierMask pollActiveModifiers() const;
  virtual SInt32 pollActiveGroup() const;
  virtual void pollPressedKeys(KeyButtonSet &pressedKeys) const;

public:
  // IKeyState overrides
  virtual void fakeKeyDown(KeyID id, KeyModifierMask mask, KeyButton button);
  virtual bool fakeKeyRepeat(KeyID id, KeyModifierMask mask, SInt32 count,
                             KeyButton button);
  virtual bool fakeKeyUp(KeyButton button);

protected:
  // KeyState overrides
  virtual void getKeyMap(barrier::KeyMap &keyMap);
  virtual void fakeKey(const Keystroke &keystroke);

private:
  int m_fd;
  UInt8 m_modifier;
};
