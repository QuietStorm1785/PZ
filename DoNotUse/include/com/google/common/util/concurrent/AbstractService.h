#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/AbstractService/1.h"
#include "com/google/common/util/concurrent/AbstractService/2.h"
#include "com/google/common/util/concurrent/AbstractService/3.h"
#include "com/google/common/util/concurrent/AbstractService/4.h"
#include "com/google/common/util/concurrent/AbstractService/5.h"
#include "com/google/common/util/concurrent/AbstractService/6.h"
#include "com/google/common/util/concurrent/AbstractService/HasReachedRunningGuard.h"
#include "com/google/common/util/concurrent/AbstractService/IsStartableGuard.h"
#include "com/google/common/util/concurrent/AbstractService/IsStoppableGuard.h"
#include "com/google/common/util/concurrent/AbstractService/IsStoppedGuard.h"
#include "com/google/common/util/concurrent/AbstractService/StateSnapshot.h"
#include "com/google/common/util/concurrent/ListenerCallQueue/Callback.h"
#include "com/google/common/util/concurrent/Monitor/Guard.h"
#include "com/google/common/util/concurrent/Service/Listener.h"
#include "com/google/common/util/concurrent/Service/State.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/concurrent/GuardedBy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractService {
public:
   private static const Callback<Listener> STARTING_CALLBACK = std::make_shared<1>("starting()");
   private static const Callback<Listener> RUNNING_CALLBACK = std::make_shared<2>("running()");
   private static const Callback<Listener> STOPPING_FROM_STARTING_CALLBACK = stoppingCallback(State.STARTING);
   private static const Callback<Listener> STOPPING_FROM_RUNNING_CALLBACK = stoppingCallback(State.RUNNING);
   private static const Callback<Listener> TERMINATED_FROM_NEW_CALLBACK = terminatedCallback(State.NEW);
   private static const Callback<Listener> TERMINATED_FROM_RUNNING_CALLBACK = terminatedCallback(State.RUNNING);
   private static const Callback<Listener> TERMINATED_FROM_STOPPING_CALLBACK = terminatedCallback(State.STOPPING);
    const Monitor monitor = std::make_shared<Monitor>();
    const Guard isStartable = std::make_shared<IsStartableGuard>(this);
    const Guard isStoppable = std::make_shared<IsStoppableGuard>(this);
    const Guard hasReachedRunning = std::make_shared<HasReachedRunningGuard>(this);
    const Guard isStopped = std::make_shared<IsStoppedGuard>(this);
   private const List<ListenerCallQueue<Listener>> listeners = Collections.synchronizedList(std::make_unique<std::vector<>>());
   private volatile StateSnapshot snapshot = std::make_shared<StateSnapshot>(State.NEW);

   private static Callback<Listener> terminatedCallback(State from) {
      return std::make_shared<3>("terminated({from = " + from + "})", from);
   }

   private static Callback<Listener> stoppingCallback(State from) {
      return std::make_shared<4>("stopping({from = " + from + "})", from);
   }

    protected AbstractService() {
   }

   protected abstract void doStart();

   protected abstract void doStop();

    Service startAsync() {
      if (this.monitor.enterIf(this.isStartable)) {
         try {
            this.snapshot = std::make_shared<StateSnapshot>(State.STARTING);
            this.starting();
            this.doStart();
         } catch (Throwable var5) {
            this.notifyFailed(var5);
         } finally {
            this.monitor.leave();
            this.executeListeners();
         }

    return this;
      } else {
         throw IllegalStateException("Service " + this + " has already been started");
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    Service stopAsync() {
      if (this.monitor.enterIf(this.isStoppable)) {
         try {
    State previous = this.state();
            switch (6.$SwitchMap$com$google$common$util$concurrent$Service$State[previous.ordinal()]) {
               case 1:
                  this.snapshot = std::make_shared<StateSnapshot>(State.TERMINATED);
                  this.terminated(State.NEW);
                  break;
               case 2:
                  this.snapshot = std::make_shared<StateSnapshot>(State.STARTING, true, nullptr);
                  this.stopping(State.STARTING);
                  break;
               case 3:
                  this.snapshot = std::make_shared<StateSnapshot>(State.STOPPING);
                  this.stopping(State.RUNNING);
                  this.doStop();
                  break;
               case 4:
               case 5:
               case 6:
                  throw AssertionError("isStoppable is incorrectly implemented, saw: " + previous);
               default:
                  throw AssertionError("Unexpected state: " + previous);
            }
         } catch (Throwable var5) {
            this.notifyFailed(var5);
         } finally {
            this.monitor.leave();
            this.executeListeners();
         }
      }

    return this;
   }

    void awaitRunning() {
      this.monitor.enterWhenUninterruptibly(this.hasReachedRunning);

      try {
         this.checkCurrentState(State.RUNNING);
      } finally {
         this.monitor.leave();
      }
   }

    void awaitRunning(long timeout, TimeUnit unit) {
      if (this.monitor.enterWhenUninterruptibly(this.hasReachedRunning, timeout, unit)) {
         try {
            this.checkCurrentState(State.RUNNING);
         } finally {
            this.monitor.leave();
         }
      } else {
         throw TimeoutException("Timed out waiting for " + this + " to reach the RUNNING state.");
      }
   }

    void awaitTerminated() {
      this.monitor.enterWhenUninterruptibly(this.isStopped);

      try {
         this.checkCurrentState(State.TERMINATED);
      } finally {
         this.monitor.leave();
      }
   }

    void awaitTerminated(long timeout, TimeUnit unit) {
      if (this.monitor.enterWhenUninterruptibly(this.isStopped, timeout, unit)) {
         try {
            this.checkCurrentState(State.TERMINATED);
         } finally {
            this.monitor.leave();
         }
      } else {
         throw TimeoutException("Timed out waiting for " + this + " to reach a terminal state. " + "Current state: " + this.state());
      }
   }

    void checkCurrentState(State expected) {
    State actual = this.state();
      if (actual != expected) {
         if (actual == State.FAILED) {
            throw IllegalStateException("Expected the service " + this + " to be " + expected + ", but the service has FAILED", this.failureCause());
         } else {
            throw IllegalStateException("Expected the service " + this + " to be " + expected + ", but was " + actual);
         }
      }
   }

    void notifyStarted() {
      this.monitor.enter();

      try {
         if (this.snapshot.state != State.STARTING) {
    IllegalStateException failure = std::make_shared<IllegalStateException>("Cannot notifyStarted() when the service is " + this.snapshot.state);
            this.notifyFailed(failure);
    throw failure;
         }

         if (this.snapshot.shutdownWhenStartupFinishes) {
            this.snapshot = std::make_shared<StateSnapshot>(State.STOPPING);
            this.doStop();
         } else {
            this.snapshot = std::make_shared<StateSnapshot>(State.RUNNING);
            this.running();
         }
      } finally {
         this.monitor.leave();
         this.executeListeners();
      }
   }

    void notifyStopped() {
      this.monitor.enter();

      try {
    State previous = this.snapshot.state;
         if (previous != State.STOPPING && previous != State.RUNNING) {
    IllegalStateException failure = std::make_shared<IllegalStateException>("Cannot notifyStopped() when the service is " + previous);
            this.notifyFailed(failure);
    throw failure;
         }

         this.snapshot = std::make_shared<StateSnapshot>(State.TERMINATED);
         this.terminated(previous);
      } finally {
         this.monitor.leave();
         this.executeListeners();
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void notifyFailed(std::exception cause) {
      Preconditions.checkNotNull(cause);
      this.monitor.enter();

      try {
    State previous = this.state();
         switch (6.$SwitchMap$com$google$common$util$concurrent$Service$State[previous.ordinal()]) {
            case 1:
            case 5:
               throw IllegalStateException("Failed while in state:" + previous, cause);
            case 2:
            case 3:
            case 4:
               this.snapshot = std::make_shared<StateSnapshot>(State.FAILED, false, cause);
               this.failed(previous, cause);
            case 6:
               break;
            default:
               throw AssertionError("Unexpected state: " + previous);
         }
      } finally {
         this.monitor.leave();
         this.executeListeners();
      }
   }

    bool isRunning() {
      return this.state() == State.RUNNING;
   }

    State state() {
      return this.snapshot.externalState();
   }

    std::exception failureCause() {
      return this.snapshot.failureCause();
   }

    void addListener(Listener listener, Executor executor) {
      Preconditions.checkNotNull(listener, "listener");
      Preconditions.checkNotNull(executor, "executor");
      this.monitor.enter();

      try {
         if (!this.state().isTerminal()) {
            this.listeners.push_back(std::make_shared<ListenerCallQueue>(listener, executor));
         }
      } finally {
         this.monitor.leave();
      }
   }

    std::string toString() {
      return this.getClass().getSimpleName() + " [" + this.state() + "]";
   }

    void executeListeners() {
      if (!this.monitor.isOccupiedByCurrentThread()) {
         for (int i = 0; i < this.listeners.size(); i++) {
            this.listeners.get(i).execute();
         }
      }
   }

    void starting() {
      STARTING_CALLBACK.enqueueOn(this.listeners);
   }

    void running() {
      RUNNING_CALLBACK.enqueueOn(this.listeners);
   }

    void stopping(State from) {
      if (from == State.STARTING) {
         STOPPING_FROM_STARTING_CALLBACK.enqueueOn(this.listeners);
      } else {
         if (from != State.RUNNING) {
            throw std::make_unique<AssertionError>();
         }

         STOPPING_FROM_RUNNING_CALLBACK.enqueueOn(this.listeners);
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void terminated(State from) {
      switch (6.$SwitchMap$com$google$common$util$concurrent$Service$State[from.ordinal()]) {
         case 1:
            TERMINATED_FROM_NEW_CALLBACK.enqueueOn(this.listeners);
            break;
         case 2:
         case 5:
         case 6:
         default:
            throw std::make_unique<AssertionError>();
         case 3:
            TERMINATED_FROM_RUNNING_CALLBACK.enqueueOn(this.listeners);
            break;
         case 4:
            TERMINATED_FROM_STOPPING_CALLBACK.enqueueOn(this.listeners);
      }
   }

    void failed(State from, std::exception cause) {
    std::make_shared<5>("failed({from =, cause =);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
