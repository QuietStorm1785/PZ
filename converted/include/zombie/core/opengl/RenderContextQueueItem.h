#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RenderContextQueueItem {
public:
 Runnable m_runnable;
 bool m_isFinished;
 bool m_isWaiting;
 std::exception m_runnableThrown = nullptr;
 const void* m_waitLock = "RenderContextQueueItem Wait Lock";

 private RenderContextQueueItem() {
 }

 static RenderContextQueueItem alloc(Runnable runnable) {
 RenderContextQueueItem renderContextQueueItem = new RenderContextQueueItem();
 renderContextQueueItem.resetInternal();
 renderContextQueueItem.m_runnable = runnable;
 return renderContextQueueItem;
 }

 void resetInternal() {
 this->m_runnable = nullptr;
 this->m_isFinished = false;
 this->m_runnableThrown = nullptr;
 }

 void waitUntilFinished(BooleanSupplier booleanSupplier) {
 while (!this->isFinished()) {
 if (!booleanSupplier.getAsBoolean()) {
 return;
 }

 synchronized (this->m_waitLock) {
 if (!this->isFinished()) {
 this->m_waitLock.wait();
 }
 }
 }
 }

 bool isFinished() {
 return this->m_isFinished;
 }

 void setWaiting() {
 this->m_isWaiting = true;
 }

 bool isWaiting() {
 return this->m_isWaiting;
 }

 void invoke() {
 try {
 this->m_runnableThrown = nullptr;
 this->m_runnable.run();
 } catch (Throwable throwable) {
 this->m_runnableThrown = throwable;
 DebugLog.General.error("%s thrown during invoke().", throwable.toString());
 ExceptionLogger.logException(throwable);
 } finally {
 synchronized (this->m_waitLock) {
 this->m_isFinished = true;
 this->m_waitLock.notifyAll();
 }
 }
 }

 std::exception getThrown() {
 return this->m_runnableThrown;
 }

 void notifyWaitingListeners() {
 synchronized (this->m_waitLock) {
 this->m_waitLock.notifyAll();
 }
 }
}
} // namespace opengl
} // namespace core
} // namespace zombie
