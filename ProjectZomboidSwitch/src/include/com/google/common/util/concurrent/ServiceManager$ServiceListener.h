#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/Service/Listener.h"
#include "com/google/common/util/concurrent/Service/State.h"
#include "com/google/common/util/concurrent/ServiceManager/NoOpService.h"
#include "com/google/common/util/concurrent/ServiceManager/ServiceManagerState.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ServiceManager {
public:
    const Service service;
   const WeakReference<ServiceManagerState> state;

   ServiceManager$ServiceListener(Service service, WeakReference<ServiceManagerState> state) {
      this.service = service;
      this.state = state;
   }

    void starting() {
    ServiceManagerState state = this.state.get();
      if (state != nullptr) {
         state.transitionService(this.service, State.NEW, State.STARTING);
         if (!(this.dynamic_cast<NoOpService*>(service) != nullptr)) {
            ServiceManager.access$200().log(Level.FINE, "Starting {0}.", this.service);
         }
      }
   }

    void running() {
    ServiceManagerState state = this.state.get();
      if (state != nullptr) {
         state.transitionService(this.service, State.STARTING, State.RUNNING);
      }
   }

    void stopping(State from) {
    ServiceManagerState state = this.state.get();
      if (state != nullptr) {
         state.transitionService(this.service, from, State.STOPPING);
      }
   }

    void terminated(State from) {
    ServiceManagerState state = this.state.get();
      if (state != nullptr) {
         if (!(this.dynamic_cast<NoOpService*>(service) != nullptr)) {
            ServiceManager.access$200().log(Level.FINE, "Service {0} has terminated. Previous state was: {1}", new Object[]{this.service, from});
         }

         state.transitionService(this.service, from, State.TERMINATED);
      }
   }

    void failed(State from, std::exception failure) {
    ServiceManagerState state = this.state.get();
      if (state != nullptr) {
    bool log = !(this.dynamic_cast<NoOpService*>(service) != nullptr);
         if (log) {
            ServiceManager.access$200().log(Level.SEVERE, "Service " + this.service + " has failed in the " + from + " state.", failure);
         }

         state.transitionService(this.service, from, State.FAILED);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
