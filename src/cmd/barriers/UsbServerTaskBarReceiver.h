#pragma once

#include "barrier/ServerTaskBarReceiver.h"

class BufferedLogOutputter;
class IEventQueue;

class UsbServerTaskBarReceiver : public ServerTaskBarReceiver {
public:
  UsbServerTaskBarReceiver(const BufferedLogOutputter *, IEventQueue *events);
  virtual ~UsbServerTaskBarReceiver();

  // IArchTaskBarReceiver overrides
  virtual void showStatus();
  virtual void runMenu(int x, int y);
  virtual void primaryAction();
  virtual const Icon getIcon() const;
};
