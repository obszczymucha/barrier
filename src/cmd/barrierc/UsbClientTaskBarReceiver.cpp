#include "UsbClientTaskBarReceiver.h"
#include "arch/Arch.h"

UsbClientTaskBarReceiver::UsbClientTaskBarReceiver(const BufferedLogOutputter *,
                                                   IEventQueue *events)
    : ClientTaskBarReceiver(events) {
  // add ourself to the task bar
  ARCH->addReceiver(this);
}

UsbClientTaskBarReceiver::~UsbClientTaskBarReceiver() {
  ARCH->removeReceiver(this);
}

void UsbClientTaskBarReceiver::showStatus() {
  // do nothing
}

void UsbClientTaskBarReceiver::runMenu(int, int) {
  // do nothing
}

void UsbClientTaskBarReceiver::primaryAction() {
  // do nothing
}

const IArchTaskBarReceiver::Icon UsbClientTaskBarReceiver::getIcon() const {
  return NULL;
}

IArchTaskBarReceiver *
createTaskBarReceiver(const BufferedLogOutputter *logBuffer,
                      IEventQueue *events) {
  return new UsbClientTaskBarReceiver(logBuffer, events);
}
