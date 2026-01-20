#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/base/Stopwatch.h"
#include "com/google/common/collect/ImmutableCollection.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/ImmutableMultimap.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/collect/ImmutableSetMultimap.h"
#include "com/google/common/collect/ImmutableSetMultimap/Builder.h"
#include "com/google/common/collect/Lists.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/collect/MultimapBuilder.h"
#include "com/google/common/collect/Multimaps.h"
#include "com/google/common/collect/Multiset.h"
#include "com/google/common/collect/Ordering.h"
#include "com/google/common/collect/SetMultimap.h"
#include "com/google/common/util/concurrent/Monitor/Guard.h"
#include "com/google/common/util/concurrent/Service/State.h"
#include "com/google/common/util/concurrent/ServiceManager/Listener.h"
#include "com/google/common/util/concurrent/ServiceManager/NoOpService.h"
#include "com/google/common/util/concurrent/ServiceManager/ServiceManagerState/1.h"
#include "com/google/common/util/concurrent/ServiceManager/ServiceManagerState/2.h"
#include "com/google/common/util/concurrent/ServiceManager/ServiceManagerState/AwaitHealthGuard.h"
#include "com/google/common/util/concurrent/ServiceManager/ServiceManagerState/StoppedGuard.h"
#include "javax/annotation/concurrent/GuardedBy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ServiceManager {
public:
    const Monitor monitor = std::make_shared<Monitor>();
   const SetMultimap<State, Service> servicesByState = MultimapBuilder.enumKeys(State.class).linkedHashSetValues().build();
   const Multiset<State> states = this.servicesByState.keys();
   const Map<Service, Stopwatch> startupTimers = Maps.newIdentityHashMap();
    bool ready;
    bool transitioned;
    const int numberOfServices;
    const Guard awaitHealthGuard = std::make_shared<AwaitHealthGuard>(this);
    const Guard stoppedGuard = std::make_shared<StoppedGuard>(this);
   const List<ListenerCallQueue<Listener>> listeners = Collections.synchronizedList(std::make_unique<std::vector<>>());

   ServiceManager$ServiceManagerState(ImmutableCollection<Service> services) {
      this.numberOfServices = services.size();
      this.servicesByState.putAll(State.NEW, services);
   }

    void tryStartTiming(Service service) {
      this.monitor.enter();

      try {
    Stopwatch stopwatch = this.startupTimers.get(service);
         if (stopwatch == nullptr) {
            this.startupTimers.put(service, Stopwatch.createStarted());
         }
      } finally {
         this.monitor.leave();
      }
   }

    void markReady() {
      this.monitor.enter();

      try {
         if (this.transitioned) {
            List<Service> servicesInBadStates = Lists.newArrayList();

            for (Service service : this.servicesByState().values()) {
               if (service.state() != State.NEW) {
                  servicesInBadStates.push_back(service);
               }
            }

            throw IllegalArgumentException(
               "Services started transitioning asynchronously before the ServiceManager was constructed: " + servicesInBadStates
            );
         }

         this.ready = true;
      } finally {
         this.monitor.leave();
      }
   }

    void addListener(Listener listener, Executor executor) {
      Preconditions.checkNotNull(listener, "listener");
      Preconditions.checkNotNull(executor, "executor");
      this.monitor.enter();

      try {
         if (!this.stoppedGuard.isSatisfied()) {
            this.listeners.push_back(std::make_shared<ListenerCallQueue>(listener, executor));
         }
      } finally {
         this.monitor.leave();
      }
   }

    void awaitHealthy() {
      this.monitor.enterWhenUninterruptibly(this.awaitHealthGuard);

      try {
         this.checkHealthy();
      } finally {
         this.monitor.leave();
      }
   }

    void awaitHealthy(long timeout, TimeUnit unit) {
      this.monitor.enter();

      try {
         if (!this.monitor.waitForUninterruptibly(this.awaitHealthGuard, timeout, unit)) {
            throw TimeoutException(
               "Timeout waiting for the services to become healthy. The following services have not started: "
                  + Multimaps.filterKeys(this.servicesByState, Predicates.in(ImmutableSet.of(State.NEW, State.STARTING)))
            );
         }

         this.checkHealthy();
      } finally {
         this.monitor.leave();
      }
   }

    void awaitStopped() {
      this.monitor.enterWhenUninterruptibly(this.stoppedGuard);
      this.monitor.leave();
   }

    void awaitStopped(long timeout, TimeUnit unit) {
      this.monitor.enter();

      try {
         if (!this.monitor.waitForUninterruptibly(this.stoppedGuard, timeout, unit)) {
            throw TimeoutException(
               "Timeout waiting for the services to stop. The following services have not stopped: "
                  + Multimaps.filterKeys(this.servicesByState, Predicates.not(Predicates.in(EnumSet.of(State.TERMINATED, State.FAILED))))
            );
         }
      } finally {
         this.monitor.leave();
      }
   }

   ImmutableMultimap<State, Service> servicesByState() {
      Builder<State, Service> builder = ImmutableSetMultimap.builder();
      this.monitor.enter();

      try {
         for (Entry<State, Service> entry : this.servicesByState.entries()) {
            if (!(entry.getValue() instanceof NoOpService)) {
               builder.put(entry);
            }
         }
      } finally {
         this.monitor.leave();
      }

      return builder.build();
   }

   ImmutableMap<Service, int64_t> startupTimes() {
      this.monitor.enter();

      List<Entry<Service, int64_t>> loadTimes;
      try {
         loadTimes = Lists.newArrayListWithCapacity(this.startupTimers.size());

         for (Entry<Service, Stopwatch> entry : this.startupTimers.entrySet()) {
    Service service = entry.getKey();
    Stopwatch stopWatch = entry.getValue();
            if (!stopWatch.isRunning() && !(dynamic_cast<NoOpService*>(service) != nullptr)) {
               loadTimes.push_back(Maps.immutableEntry(service, stopWatch.elapsed(TimeUnit.MILLISECONDS)));
            }
         }
      } finally {
         this.monitor.leave();
      }

      Collections.sort(loadTimes, Ordering.natural().onResultOf(std::make_shared<1>(this)));
      return ImmutableMap.copyOf(loadTimes);
   }

    void transitionService(Service service, State from, State to) {
      Preconditions.checkNotNull(service);
      Preconditions.checkArgument(from != to);
      this.monitor.enter();

      try {
         this.transitioned = true;
         if (!this.ready) {
            return;
         }

         Preconditions.checkState(this.servicesByState.remove(from, service), "Service %s not at the expected location in the state map %s", service, from);
         Preconditions.checkState(this.servicesByState.put(to, service), "Service %s in the state map unexpectedly at %s", service, to);
    Stopwatch stopwatch = this.startupTimers.get(service);
         if (stopwatch == nullptr) {
            stopwatch = Stopwatch.createStarted();
            this.startupTimers.put(service, stopwatch);
         }

         if (to.compareTo(State.RUNNING) >= 0 && stopwatch.isRunning()) {
            stopwatch.stop();
            if (!(dynamic_cast<NoOpService*>(service) != nullptr)) {
               ServiceManager.access$200().log(Level.FINE, "Started {0} in {1}.", new Object[]{service, stopwatch});
            }
         }

         if (to == State.FAILED) {
            this.fireFailedListeners(service);
         }

         if (this.states.count(State.RUNNING) == this.numberOfServices) {
            this.fireHealthyListeners();
         } else if (this.states.count(State.TERMINATED) + this.states.count(State.FAILED) == this.numberOfServices) {
            this.fireStoppedListeners();
         }
      } finally {
         this.monitor.leave();
         this.executeListeners();
      }
   }

    void fireStoppedListeners() {
      ServiceManager.access$300().enqueueOn(this.listeners);
   }

    void fireHealthyListeners() {
      ServiceManager.access$400().enqueueOn(this.listeners);
   }

    void fireFailedListeners(Service service) {
    std::make_shared<2>("failed({service=" +);
   }

    void executeListeners() {
      Preconditions.checkState(!this.monitor.isOccupiedByCurrentThread(), "It is incorrect to execute listeners with the monitor held.");

      for (int i = 0; i < this.listeners.size(); i++) {
         this.listeners.get(i).execute();
      }
   }

    void checkHealthy() {
      if (this.states.count(State.RUNNING) != this.numberOfServices) {
         IllegalStateException exception = std::make_shared<IllegalStateException>(
            "Expected to be healthy after starting. The following services are not running: "
               + Multimaps.filterKeys(this.servicesByState, Predicates.not(Predicates.equalTo(State.RUNNING)))
         );
    throw exception;
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
