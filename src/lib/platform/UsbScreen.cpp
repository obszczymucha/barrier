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
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

UsbScreen *UsbScreen::s_screen = NULL;

UsbScreen::UsbScreen(IEventQueue *events)
    : PlatformScreen(events), m_isPrimary(false), m_isOnScreen(false), m_x(0),
      m_y(0), m_w(1920), m_h(1080), m_xCenter(1920 / 2), m_yCenter(1080 / 2),
      m_xCursor(0), m_yCursor(0), m_button(0), m_events(events),
      m_keyState(NULL), m_fd(0), m_fd2(0) {
  try {
    assert(s_screen == NULL);
    s_screen = this;

    m_keyState = new UsbKeyState(m_events, m_keyMap);
    m_fd = open("/dev/hidg0", O_RDWR);
    m_fd2 = open("/dev/hidg2", O_RDWR);
  } catch (...) {
    if (m_keyState) {
      delete m_keyState;
    }

    s_screen = NULL;
    throw;
  }
}

UsbScreen::~UsbScreen() {
  assert(s_screen != NULL);

  delete m_keyState;
  m_events->adoptBuffer(NULL);
  m_events->removeHandler(Event::kSystem, m_events->getSystemTarget());

  if (m_fd) {
    close(m_fd);
  }

  if (m_fd2) {
    close(m_fd2);
  }

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

void UsbScreen::fakeMouseButton(ButtonID id, bool press) {
  /*LOG((CLOG_INFO "UsgScreen::fakeMouseButton(%d, %d)\n", id, press));*/

  if (press) {
    switch (id) {
    case 1:
      m_button |= 0x01;
      break;
    case 3:
      m_button |= 0x02;
      break;
    case 2:
      m_button |= 0x04;
      break;
    }
  } else {
    switch (id) {
    case 1:
      m_button &= ~0x01;
      break;
    case 3:
      m_button &= ~0x02;
      break;
    case 2:
      m_button &= ~0x04;
      break;
    }
  }

  unsigned char report[4] = {static_cast<unsigned char>(m_button), 0, 0, 0};
  int result = write(m_fd, report, sizeof(report));

  if (result < 0) {
    LOG((CLOG_INFO "Couldn't send mouse report!\n"));
  }
}

void UsbScreen::fakeMouseMove(SInt32 x, SInt32 y) {
  /*LOG((CLOG_INFO "UsbScreen::fakeMouseMove(%lld, %lld)\n", x, y));*/
  uint16_t rx = (uint16_t)((x * 32768LL) / 1920);
  uint16_t ry = (uint16_t)((y * 32768LL) / 1080);

  unsigned char report[6];
  report[0] = 0;
  report[1] = rx & 0xFF;
  report[2] = (rx >> 8) & 0xFF;
  report[3] = ry & 0xFF;
  report[4] = (ry >> 8) & 0xFF;
  report[5] = 0;

  int result = write(m_fd2, report, sizeof(report));
  m_x = x;
  m_y = y;

  if (result < 0) {
    LOG((CLOG_INFO "Couldn't send mouse report!\n"));
  }
}

void UsbScreen::fakeMouseRelativeMove(SInt32 dx, SInt32 dy) const {
  unsigned char report[4] = {0, static_cast<unsigned char>(dx),
                             static_cast<unsigned char>(dy), 0};
  int result = write(m_fd, report, sizeof(report));

  if (result < 0) {
    LOG((CLOG_INFO "Couldn't send mouse report!\n"));
  }
}

void UsbScreen::fakeMouseWheel(SInt32 xDelta, SInt32 yDelta) const {
  /*LOG((CLOG_INFO "UsgScreen::fakeMouseWheel(%d, %d)\n", xDelta, yDelta));*/

  unsigned char report[4] = {0, 0, 0, static_cast<unsigned char>(yDelta)};
  int result = write(m_fd, report, sizeof(report));

  if (result < 0) {
    LOG((CLOG_INFO "Couldn't send mouse report!\n"));
  }
}

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
