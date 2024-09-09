#include "platform/UsbScreen.h"

#include "arch/Arch.h"
#include "arch/XArch.h"
#include "barrier/Clipboard.h"
#include "barrier/KeyMap.h"
#include "barrier/XScreen.h"
#include "base/IEventQueue.h"
#include "base/Log.h"
#include "base/Stopwatch.h"
#include "base/TMethodEventJob.h"
#include "platform/UsbEventQueueBuffer.h"
#include "platform/UsbKeyState.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>

UsbScreen *UsbScreen::s_screen = NULL;

UsbScreen::UsbScreen(IEventQueue *events)
    : PlatformScreen(events), m_isPrimary(false), m_isOnScreen(false), m_x(0),
      m_y(0), m_w(1920), m_h(1080), m_xCenter(1920 / 2), m_yCenter(1080 / 2),
      m_xCursor(0), m_yCursor(0), m_events(events) {
  assert(s_screen == NULL);

  s_screen = this;

  try {
    m_keyState = new UsbKeyState(m_events);
  } catch (...) {
    delete m_keyState;
    s_screen = NULL;
    throw;
  }

  // install event handlers
  m_events->adoptHandler(
      Event::kSystem, m_events->getSystemTarget(),
      new TMethodEventJob<UsbScreen>(this, &UsbScreen::handleSystemEvent));

  // install the platform event queue
  /*m_events->adoptBuffer(new UsbEventQueueBuffer(m_events));*/
}

UsbScreen::~UsbScreen() {
  assert(s_screen != NULL);

  m_events->adoptBuffer(NULL);
  m_events->removeHandler(Event::kSystem, m_events->getSystemTarget());

  s_screen = NULL;
}

void *UsbScreen::getEventTarget() const {
  return const_cast<UsbScreen *>(this);
}

bool UsbScreen::getClipboard(ClipboardID, IClipboard *dst) const {
  return true;
}

void UsbScreen::getShape(SInt32 &x, SInt32 &y, SInt32 &w, SInt32 &h) const {
  x = m_x;
  y = m_y;
  w = m_w;
  h = m_h;
}

void UsbScreen::getCursorPos(SInt32 &x, SInt32 &y) const {
  x = 0;
  y = 0;
}

void UsbScreen::reconfigure(UInt32 activeSides) {}

void UsbScreen::warpCursor(SInt32 x, SInt32 y) {}

UInt32 UsbScreen::registerHotKey(KeyID key, KeyModifierMask mask) { return 0; }

void UsbScreen::unregisterHotKey(UInt32 id) {}

void UsbScreen::fakeInputBegin() {}

void UsbScreen::fakeInputEnd() {}

SInt32 UsbScreen::getJumpZoneSize() const { return 1; }

bool UsbScreen::isAnyMouseButtonDown(UInt32 &buttonID) const { return false; }

void UsbScreen::getCursorCenter(SInt32 &x, SInt32 &y) const {
  x = m_xCenter;
  y = m_yCenter;
}

void UsbScreen::fakeMouseButton(ButtonID id, bool press) {}

void UsbScreen::fakeMouseMove(SInt32 x, SInt32 y) {}

void UsbScreen::fakeMouseRelativeMove(SInt32 dx, SInt32 dy) const {

}

void UsbScreen::fakeMouseWheel(SInt32 xDelta, SInt32 yDelta) const {}

void UsbScreen::enable() { LOG((CLOG_INFO "UsbScreen::enable()")); }

void UsbScreen::disable() { LOG((CLOG_INFO "UsbScreen::disable()")); }

void UsbScreen::enter() {
  LOG((CLOG_INFO "UsbScreen::enter()"));
  m_isOnScreen = true;
}

bool UsbScreen::leave() {
  LOG((CLOG_INFO "UsbScreen::leave()"));
  m_isOnScreen = false;
  return true;
}

void UsbScreen::handleSystemEvent(const Event &event, void *) {}

void UsbScreen::updateButtons() {}

IKeyState *UsbScreen::getKeyState() const { return m_keyState; }

bool UsbScreen::setClipboard(ClipboardID id, const IClipboard *clipboard) {
  return true;
}

void UsbScreen::checkClipboards() {
  // do nothing, we're always up to date
}

void UsbScreen::openScreensaver(bool notify) {}

void UsbScreen::closeScreensaver() {}

void UsbScreen::screensaver(bool activate) {}

void UsbScreen::resetOptions() {}

void UsbScreen::setOptions(const OptionsList &options) {}

void UsbScreen::setSequenceNumber(UInt32 seqNum) {}

bool UsbScreen::isPrimary() const { return m_isPrimary; }
