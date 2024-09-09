#include "platform/UsbScreen.h"

/*#include "platform/XWindowsClipboard.h"*/
/*#include "platform/XWindowsEventQueueBuffer.h"*/
/*#include "platform/XWindowsKeyState.h"*/
/*#include "platform/XWindowsScreenSaver.h"*/
/*#include "platform/XWindowsUtil.h"*/
#include "arch/Arch.h"
#include "arch/XArch.h"
#include "barrier/Clipboard.h"
#include "barrier/KeyMap.h"
#include "barrier/XScreen.h"
#include "base/IEventQueue.h"
#include "base/Log.h"
#include "base/Stopwatch.h"
#include "base/TMethodEventJob.h"
#include "platform/UsbKeyState.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>

UsbScreen *UsbScreen::s_screen = NULL;

UsbScreen::UsbScreen(IEventQueue *events)
    : PlatformScreen(events), m_isPrimary(true), m_isOnScreen(false), m_x(0),
      m_y(0), m_w(0), m_h(0), m_xCenter(0), m_yCenter(0), m_xCursor(0),
      m_yCursor(0), m_events(events) {
  assert(s_screen == NULL);

  s_screen = this;

  try {
    m_keyState = new UsbKeyState(m_events);
  } catch (...) {
    delete m_keyState;
    s_screen = NULL;
    throw;
  }
  /*    m_screensaver = new MSWindowsScreenSaver();*/
  /*    m_desks       = new MSWindowsDesks(*/
  /*                        m_isPrimary,*/
  /*                        m_noHooks,*/
  /*                        m_screensaver,*/
  /*                        m_events,*/
  /*                                       [this]() { updateKeysCB(); },*/
  /*                        stopOnDeskSwitch);*/
  /**/
  /*    updateScreenShape();*/
  /*    m_class       = createWindowClass();*/
  /*    m_window      = createWindow(m_class, "Barrier");*/
  /*    forceShowCursor();*/
  /*    LOG((CLOG_DEBUG "screen shape: %d,%d %dx%d %s", m_x, m_y, m_w, m_h,
   * m_multimon ? "(multi-monitor)" : ""));*/
  /*    LOG((CLOG_DEBUG "window is 0x%08x", m_window));*/
  /**/
  /*    OleInitialize(0);*/
  /*    m_dropWindow = createDropWindow(m_class, "DropWindow");*/
  /*    m_dropTarget = new MSWindowsDropTarget();*/
  /*    RegisterDragDrop(m_dropWindow, m_dropTarget);*/
  /*}*/
  /*catch (...) {*/
  /*    delete m_keyState;*/
  /*    delete m_desks;*/
  /*    delete m_screensaver;*/
  /*    destroyWindow(m_window);*/
  /*    destroyClass(m_class);*/
  /*    s_screen = NULL;*/
  /*    throw;*/
  /*}*/
  /**/
  /*// install event handlers*/
  /*m_events->adoptHandler(Event::kSystem, m_events->getSystemTarget(),*/
  /*                        new TMethodEventJob<MSWindowsScreen>(this,*/
  /*                            &MSWindowsScreen::handleSystemEvent));*/
  /**/
  /*// install the platform event queue*/
  /*m_events->adoptBuffer(new MSWindowsEventQueueBuffer(m_events));*/
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

void UsbScreen::fakeMouseRelativeMove(SInt32 dx, SInt32 dy) const {}

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
