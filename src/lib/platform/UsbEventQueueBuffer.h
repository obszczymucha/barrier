#pragma once

#include "base/IEventQueueBuffer.h"
#include "common/stdvector.h"
#include "mt/Mutex.h"

class IEventQueue;

class UsbEventQueueBuffer : public IEventQueueBuffer {
public:
  UsbEventQueueBuffer(IEventQueue *events);
  virtual ~UsbEventQueueBuffer();

  // IEventQueueBuffer overrides
  virtual void init() {}
  virtual void waitForEvent(double timeout);
  virtual Type getEvent(Event &event, UInt32 &dataID);
  virtual bool addEvent(UInt32 dataID);
  virtual bool isEmpty() const;
  virtual EventQueueTimer *newTimer(double duration, bool oneShot) const;
  virtual void deleteTimer(EventQueueTimer *) const;

private:
  IEventQueue *m_events;
};
