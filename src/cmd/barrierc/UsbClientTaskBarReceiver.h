#pragma once

#include "barrier/ClientTaskBarReceiver.h"

class BufferedLogOutputter;
class IEventQueue;

class UsbClientTaskBarReceiver : public ClientTaskBarReceiver {
public:
  UsbClientTaskBarReceiver(const BufferedLogOutputter *, IEventQueue *events);
  virtual ~UsbClientTaskBarReceiver();

  // IArchTaskBarReceiver overrides
  virtual void showStatus();
  virtual void runMenu(int x, int y);
  virtual void primaryAction();
  virtual const Icon getIcon() const;
};
