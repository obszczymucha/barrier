#pragma once

#include "barrier/KeyMap.h"
#include "barrier/PlatformScreen.h"
#include "common/stdset.h"
#include "common/stdvector.h"

/*class UsbClipboard;*/
class UsbKeyState;
/*class UsbScreenSaver;*/

class UsbScreen : public PlatformScreen {
public:
  UsbScreen(IEventQueue *events);
  virtual ~UsbScreen();

public:
  // IScreen overrides
  virtual void *getEventTarget() const;
  virtual bool getClipboard(ClipboardID id, IClipboard *) const;
  virtual void getShape(SInt32 &x, SInt32 &y, SInt32 &width,
                        SInt32 &height) const;
  virtual void getCursorPos(SInt32 &x, SInt32 &y) const;

  // IPrimaryScreen overrides
  virtual void reconfigure(UInt32 activeSides);
  virtual void warpCursor(SInt32 x, SInt32 y);
  virtual UInt32 registerHotKey(KeyID key, KeyModifierMask mask);
  virtual void unregisterHotKey(UInt32 id);
  virtual void fakeInputBegin();
  virtual void fakeInputEnd();
  virtual SInt32 getJumpZoneSize() const;
  virtual bool isAnyMouseButtonDown(UInt32 &buttonID) const;
  virtual void getCursorCenter(SInt32 &x, SInt32 &y) const;

  // ISecondaryScreen overrides
  virtual void fakeMouseButton(ButtonID id, bool press);
  virtual void fakeMouseMove(SInt32 x, SInt32 y);
  virtual void fakeMouseRelativeMove(SInt32 dx, SInt32 dy) const;
  virtual void fakeMouseWheel(SInt32 xDelta, SInt32 yDelta) const;

  // IPlatformScreen overrides
  virtual void enable();
  virtual void disable();
  virtual void enter();
  virtual bool leave();
  virtual bool setClipboard(ClipboardID, const IClipboard *);
  virtual void checkClipboards();
  virtual void openScreensaver(bool notify);
  virtual void closeScreensaver();
  virtual void screensaver(bool activate);
  virtual void resetOptions();
  virtual void setOptions(const OptionsList &options);
  virtual void setSequenceNumber(UInt32);
  virtual bool isPrimary() const;

protected:
  // IPlatformScreen overrides
  virtual void handleSystemEvent(const Event &, void *);
  virtual void updateButtons();
  virtual IKeyState *getKeyState() const;

private:
  // true if mouse has entered the screen
  bool m_isOnScreen;

  // screen shape stuff
  SInt32 m_x, m_y;
  SInt32 m_w, m_h;
  SInt32 m_xCenter, m_yCenter;

private:
  // true if screen is being used as a primary screen, false otherwise
  bool m_isPrimary;

  // last mouse position
  SInt32 m_xCursor, m_yCursor;

  static UsbScreen *s_screen;
  IEventQueue *m_events;

  // keyboard stuff
  UsbKeyState *m_keyState;
};
