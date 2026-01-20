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
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Collections2.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/ImmutableMultimap.h"
#include "com/google/common/util/concurrent/ListenerCallQueue/Callback.h"
#include "com/google/common/util/concurrent/Service/State.h"
#include "com/google/common/util/concurrent/ServiceManager/1.h"
#include "com/google/common/util/concurrent/ServiceManager/2.h"
#include "com/google/common/util/concurrent/ServiceManager/EmptyServiceManagerWarning.h"
#include "com/google/common/util/concurrent/ServiceManager/Listener.h"
#include "com/google/common/util/concurrent/ServiceManager/NoOpService.h"
#include "com/google/common/util/concurrent/ServiceManager/ServiceListener.h"
#include "com/google/common/util/concurrent/ServiceManager/ServiceManagerState.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ServiceManager {
public:
    static const Logger logger = Logger.getLogger(ServiceManager.class.getName());
   private static const Callback<Listener> HEALTHY_CALLBACK = std::make_shared<1>("healthy()");
   private static const Callback<Listener> STOPPED_CALLBACK = std::make_shared<2>("stopped()");
    const ServiceManagerState state;
   private const ImmutableList<Service> services;

    public ServiceManager(Iterable<? extends) {
      ImmutableList<Service> copy = ImmutableList.copyOf(services);
      if (copy.empty()) {
         logger.log(
            Level.WARNING,
            "ServiceManager configured with no services.  Is your application configured properly?",
            (Throwable)(std::make_shared<EmptyServiceManagerWarning>(nullptr))
         );
         copy = ImmutableList.of(std::make_shared<NoOpService>(nullptr));
      }

      this.state = std::make_shared<ServiceManagerState>(copy);
      this.services = copy;
      WeakReference<ServiceManagerState> stateReference = new WeakReference<>(this.state);

    for (auto& service : copy)         service.addListener(std::make_shared<ServiceListener>(service, stateReference), MoreExecutors.directExecutor());
         Preconditions.checkArgument(service.state() == State.NEW, "Can only manage NEW services, %s", service);
      }

      this.state.markReady();
   }

    void addListener(Listener listener, Executor executor) {
      this.state.addListener(listener, executor);
   }

    void addListener(Listener listener) {
      this.state.addListener(listener, MoreExecutors.directExecutor());
   }

    ServiceManager startAsync() {
      for (Service service : this.services) {
    State state = service.state();
         Preconditions.checkState(state == State.NEW, "Service %s is %s, cannot start it.", service, state);
      }

      for (Service service : this.services) {
         try {
            this.state.tryStartTiming(service);
            service.startAsync();
         } catch (IllegalStateException var4) {
            logger.log(Level.WARNING, "Unable to start Service " + service, (Throwable)var4);
         }
      }

    return this;
   }

    void awaitHealthy() {
      this.state.awaitHealthy();
   }

    void awaitHealthy(long timeout, TimeUnit unit) {
      this.state.awaitHealthy(timeout, unit);
   }

    ServiceManager stopAsync() {
      for (Service service : this.services) {
         service.stopAsync();
      }

    return this;
   }

    void awaitStopped() {
      this.state.awaitStopped();
   }

    void awaitStopped(long timeout, TimeUnit unit) {
      this.state.awaitStopped(timeout, unit);
   }

    bool isHealthy() {
      for (Service service : this.services) {
         if (!service.isRunning()) {
    return false;
         }
      }

    return true;
   }

   public ImmutableMultimap<State, Service> servicesByState() {
      return this.state.servicesByState();
   }

   public ImmutableMap<Service, int64_t> startupTimes() {
      return this.state.startupTimes();
   }

    std::string toString() {
      return MoreObjects.toStringHelper(ServiceManager.class)
         .push_back("services", Collections2.filter(this.services, Predicates.not(Predicates.instanceOf(NoOpService.class))))
         ;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
