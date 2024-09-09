#include "UsbServerTaskBarReceiver.h"
#include "arch/Arch.h"

UsbServerTaskBarReceiver::UsbServerTaskBarReceiver(const BufferedLogOutputter *,
                                                   IEventQueue *events)
    : ServerTaskBarReceiver(events) {
  // add ourself to the task bar
  ARCH->addReceiver(this);
}

UsbServerTaskBarReceiver::~UsbServerTaskBarReceiver() {
  ARCH->removeReceiver(this);
}

void UsbServerTaskBarReceiver::showStatus() {
  // do nothing
}

void UsbServerTaskBarReceiver::runMenu(int, int) {
  // do nothing
}

void UsbServerTaskBarReceiver::primaryAction() {
  // do nothing
}

const IArchTaskBarReceiver::Icon UsbServerTaskBarReceiver::getIcon() const {
  return NULL;
}

IArchTaskBarReceiver *
createTaskBarReceiver(const BufferedLogOutputter *logBuffer,
                      IEventQueue *events) {
  return new UsbServerTaskBarReceiver(logBuffer, events);
}
