#include "platform/UsbKeyState.h"
#include "base/Log.h"
#include <ctime>
#include <fcntl.h>
#include <unistd.h>

UsbKeyState::UsbKeyState(IEventQueue *events, barrier::KeyMap &keyMap)
    : KeyState(events, keyMap), m_modifier(0) {
  m_fd = open("/dev/hidg1", O_RDWR);
}

UsbKeyState::~UsbKeyState() {
  if (m_fd) {
    close(m_fd);
  }
}

bool UsbKeyState::fakeCtrlAltDel() { return true; }

KeyModifierMask UsbKeyState::pollActiveModifiers() const {
  KeyModifierMask state = 0;
  return state;
}

SInt32 UsbKeyState::pollActiveGroup() const { return 0; }

void UsbKeyState::pollPressedKeys(KeyButtonSet &pressedKeys) const {}

void UsbKeyState::getKeyMap(barrier::KeyMap &keyMap) {}

void UsbKeyState::fakeKey(const Keystroke &k) {
  /*LOG((CLOG_INFO "UsbKeyState::fakeKey()"));*/
}

UInt8 map_key(KeyID id) {
  switch (id) {
  case 104:
    return 0x0B;
  case 108:
    return 0x0F;
  default:
    return 0;
  }
}

void UsbKeyState::send_key(unsigned char modifier, unsigned char key) {
  unsigned char report[8] = {modifier, 0, key, 0, 0, 0, 0, 0};
  int result = write(m_fd, report, sizeof(report));
  if (result < 0) {
    LOG((CLOG_INFO "Couldn't send keyboard report!\n"));
  }
}

unsigned char map_mask(KeyModifierMask mask) {
  switch (mask) {
  case 16:
    return 0x08; // LEFT_SUPER
  default:
    return 0;
  }
}

void UsbKeyState::send_barrier_key(KeyID id, KeyModifierMask mask) {
  UInt8 key = map_key(id);

  if (key == 0) {
    return;
  }

  unsigned char modifier = map_mask(mask);

  send_key(modifier, key);
}

void UsbKeyState::fakeKeyDown(KeyID id, KeyModifierMask mask,
                              KeyButton button) {
  /*LOG((CLOG_INFO "UsbKeyState::fakeKeyDown(%d, %d, %d)", id, mask, button));*/
  UInt8 key = 0;

  switch (button) {
  case 0:
    send_barrier_key(id, mask);
    return;
  case 29: // LEFT_CTRL
    m_modifier |= 0x01;
    break;
  case 42: // LEFT_SHIFT
    m_modifier |= 0x02;
    break;
  case 56: // LEFT_ALT
    m_modifier |= 0x04;
    break;
  case 347: // LEFT_SUPER
    m_modifier |= 0x08;
    break;
  case 285: // RIGHT_CTRL
    m_modifier |= 0x10;
    break;
  case 54: // RIGHT_SHIFT
    m_modifier |= 0x20;
    break;
  case 312: // RIGHT_ALT
    m_modifier |= 0x40;
    break;
  case 348: // RIGHT_SUPER
    m_modifier |= 0x80;
    break;
  case 1: // ESC
    key = 0x29;
    break;
  case 2: // 1
    key = 0x1e;
    break;
  case 3: // 2
    key = 0x1f;
    break;
  case 4: // 3
    key = 0x20;
    break;
  case 5: // 4
    key = 0x21;
    break;
  case 6: // 5
    key = 0x22;
    break;
  case 7: // 6
    key = 0x23;
    break;
  case 8: // 7
    key = 0x24;
    break;
  case 9: // 8
    key = 0x25;
    break;
  case 10: // 9
    key = 0x26;
    break;
  case 11: // 0
    key = 0x27;
    break;
  case 12: // -
    key = 0x2D;
    break;
  case 13: // =
    key = 0x2E;
    break;
  case 14: // Backspace
    key = 0x2A;
    break;
  case 15: // Tab
    key = 0x2B;
    break;
  case 16: // Q
    key = 0x14;
    break;
  case 17: // W
    key = 0x1A;
    break;
  case 18: // E
    key = 0x08;
    break;
  case 19: // R
    key = 0x15;
    break;
  case 20: // T
    key = 0x17;
    break;
  case 21: // Y
    key = 0x1C;
    break;
  case 22: // U
    key = 0x18;
    break;
  case 23: // I
    key = 0x0C;
    break;
  case 24: // O
    key = 0x12;
    break;
  case 25: // P
    key = 0x13;
    break;
  case 26: // [
    key = 0x2F;
    break;
  case 27: // ]
    key = 0x30;
    break;
  case 28: // Enter
    key = 0x28;
    break;
  case 30: // A
    key = 0x04;
    break;
  case 31: // S
    key = 0x16;
    break;
  case 32: // D
    key = 0x07;
    break;
  case 33: // F
    key = 0x09;
    break;
  case 34: // G
    key = 0x0A;
    break;
  case 35: // H
    key = 0x0B;
    break;
  case 36: // J
    key = 0x0D;
    break;
  case 37: // K
    key = 0x0E;
    break;
  case 38: // L
    key = 0x0F;
    break;
  case 39: // ;
    key = 0x33;
    break;
  case 40: // '
    key = 0x34;
    break;
  case 41: // `
    key = 0x35;
    break;
  case 43: // Backslash
    key = 0x31;
    break;
  case 44: // Z
    key = 0x1D;
    break;
  case 45: // X
    key = 0x1B;
    break;
  case 46: // C
    key = 0x06;
    break;
  case 47: // V
    key = 0x19;
    break;
  case 48: // B
    key = 0x05;
    break;
  case 49: // N
    key = 0x11;
    break;
  case 50: // M
    key = 0x10;
    break;
  case 51: // ,
    key = 0x36;
    break;
  case 52: // .
    key = 0x37;
    break;
  case 53: // /
    key = 0x38;
    break;
  case 57: // Spacebar
    key = 0x2C;
    break;
  case 58: // CapsLock
    key = 0x39;
    break;
  case 59: // F1
    key = 0x3A;
    break;
  case 60: // F2
    key = 0x3B;
    break;
  case 61: // F3
    key = 0x3C;
    break;
  case 62: // F4
    key = 0x3D;
    break;
  case 63: // F5
    key = 0x3E;
    break;
  case 64: // F6
    key = 0x3F;
    break;
  case 65: // F7
    key = 0x40;
    break;
  case 66: // F8
    key = 0x41;
    break;
  case 67: // F9
    key = 0x42;
    break;
  case 68: // F10
    key = 0x43;
    break;
  case 69: // Pause
    key = 0x48;
    break;
  case 87: // F11
    key = 0x44;
    break;
  case 88: // F12
    key = 0x45;
    break;
  case 311: // PrntScr
    key = 0x46;
    break;
  case 338: // Insert
    key = 0x49;
    break;
  case 339: // Delete
    key = 0x4C;
    break;
  case 327: // Home
    key = 0x4A;
    break;
  case 335: // End
    key = 0x4D;
    break;
  case 329: // PageUp
    key = 0x4B;
    break;
  case 337: // PageDown
    key = 0x4E;
    break;
  case 331: // Left
    key = 0x50;
    break;
  case 333: // Right
    key = 0x4F;
    break;
  case 328: // Up
    key = 0x52;
    break;
  case 336: // Down
    key = 0x51;
    break;
  }

  /*LOG((CLOG_INFO "modifier: %d", m_modifier));*/

  send_key(m_modifier, key);
}

bool UsbKeyState::fakeKeyRepeat(KeyID id, KeyModifierMask mask, SInt32 count,
                                KeyButton button) {
  /*LOG((CLOG_INFO "UsbKeyState::fakeKeyRepeat(%d %d %d %d)", id, mask, count,*/
  /*     button));*/

  for (int i = 0; i < count; ++i) {
    fakeKeyUp(button);
    fakeKeyDown(id, mask, button);
  }

  return true;
}

bool UsbKeyState::fakeKeyUp(KeyButton button) {
  /*LOG((CLOG_INFO "UsbKeyState::fakeKeyUp(%d)", button));*/

  switch (button) {
  case 29: // LEFT_CTRL
    m_modifier &= ~0x01;
    break;
  case 42: // LEFT_SHIFT
    m_modifier &= ~0x02;
    break;
  case 56: // LEFT_ALT
    m_modifier &= ~0x04;
    break;
  case 347: // LEFT_SUPER
    m_modifier &= ~0x08;
    break;
  case 285: // RIGHT_CTRL
    m_modifier &= ~0x10;
    break;
  case 54: // RIGHT_SHIFT
    m_modifier &= ~0x20;
    break;
  case 312: // RIGHT_ALT
    m_modifier &= ~0x40;
    break;
  case 348: // RIGHT_SUPER
    m_modifier &= ~0x80;
    break;
  }

  unsigned char report[8] = {m_modifier, 0, 0, 0, 0, 0, 0, 0};
  int result = write(m_fd, report, sizeof(report));

  if (result < 0) {
    LOG((CLOG_INFO "Couldn't send keyboard report!\n"));
  }

  /*LOG((CLOG_INFO "modifier: %d", m_modifier));*/
  return true;
}

bool UsbKeyState::is_ctrl_pressed() const {
  return m_modifier & 0x01 || m_modifier & 0x10;
}

bool UsbKeyState::is_shift_pressed() const {
  return m_modifier & 0x02 || m_modifier & 0x20;
}

bool UsbKeyState::is_alt_pressed() const {
  return m_modifier & 0x04 || m_modifier & 0x40;
}
