#include "platform/UsbEventQueueBuffer.h"

#include "base/Event.h"
#include "base/IEventQueue.h"
#include "mt/Lock.h"
#include "mt/Thread.h"

#include <fcntl.h>
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#if HAVE_POLL
#include <poll.h>
#else
#if HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif
#if HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#endif

class EventQueueTimer {};

UsbEventQueueBuffer::UsbEventQueueBuffer(IEventQueue *events)
    : m_events(events) {}

UsbEventQueueBuffer::~UsbEventQueueBuffer() {}

void UsbEventQueueBuffer::waitForEvent(double dtimeout) {}

IEventQueueBuffer::Type UsbEventQueueBuffer::getEvent(Event &event,
                                                      UInt32 &dataID) {
  return kSystem;
}

bool UsbEventQueueBuffer::addEvent(UInt32 dataID) { return false; }

bool UsbEventQueueBuffer::isEmpty() const { return true; }

EventQueueTimer *UsbEventQueueBuffer::newTimer(double, bool) const {
  return new EventQueueTimer;
}

void UsbEventQueueBuffer::deleteTimer(EventQueueTimer *timer) const {
  delete timer;
}
