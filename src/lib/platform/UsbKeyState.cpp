/*
 * barrier -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2003 Chris Schoeneman
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "platform/UsbKeyState.h"

UsbKeyState::UsbKeyState(IEventQueue *events) : KeyState(events) {}

UsbKeyState::UsbKeyState(IEventQueue *events, barrier::KeyMap &keyMap)
    : KeyState(events, keyMap) {}

UsbKeyState::~UsbKeyState() {}

bool UsbKeyState::fakeCtrlAltDel() { return true; }

KeyModifierMask UsbKeyState::pollActiveModifiers() const {
  KeyModifierMask state = 0;
  return state;
}

SInt32 UsbKeyState::pollActiveGroup() const { return 0; }

void UsbKeyState::pollPressedKeys(KeyButtonSet &pressedKeys) const {}

void UsbKeyState::getKeyMap(barrier::KeyMap &keyMap) {}

void UsbKeyState::fakeKey(const Keystroke &keystroke) {}
