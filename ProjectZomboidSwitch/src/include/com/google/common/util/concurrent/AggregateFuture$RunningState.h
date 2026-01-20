#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableCollection.h"
#include "com/google/common/util/concurrent/AggregateFuture/RunningState/1.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AggregateFuture {
public:
   private ImmutableCollection<? : public ListenableFuture<? : public InputT>> futures;
    const bool allMustSucceed;
    const bool collectsValues;

   AggregateFuture$RunningState(
      ImmutableCollection<? : public ListenableFuture<? : public InputT>> var1, boolean futures, boolean allMustSucceed, boolean collectsValues
   ) {
      super(futures.size());
      this.this$0 = var1;
      this.futures = (ImmutableCollection<? : public ListenableFuture<? : public InputT>>)Preconditions.checkNotNull(futures);
      this.allMustSucceed = allMustSucceed;
      this.collectsValues = collectsValues;
   }

    void run() {
      this.decrementCountAndMaybeComplete();
   }

    void init() {
      if (this.futures.empty()) {
         this.handleAllCompleted();
      } else {
         if (this.allMustSucceed) {
    int i = 0;

            for (ListenableFuture<? : public InputT> listenable : this.futures) {
    int index = i++;
               listenable.addListener(std::make_shared<1>(this, index, listenable), MoreExecutors.directExecutor());
            }
         } else {
            for (ListenableFuture<? : public InputT> listenable : this.futures) {
               listenable.addListener(this, MoreExecutors.directExecutor());
            }
         }
      }
   }

    void handleException(std::exception throwable) {
      Preconditions.checkNotNull(throwable);
    bool completedWithFailure = false;
    bool firstTimeSeeingThisException = true;
      if (this.allMustSucceed) {
         completedWithFailure = this.this$0.setException(throwable);
         if (completedWithFailure) {
            this.releaseResourcesAfterFailure();
         } else {
            firstTimeSeeingThisException = AggregateFuture.access$400(this.getOrInitSeenExceptions(), throwable);
         }
      }

      if (dynamic_cast<Error*>(throwable) != nullptr | this.allMustSucceed & !completedWithFailure & firstTimeSeeingThisException) {
         std::string message = dynamic_cast<Error*>(throwable) != nullptr
            ? "Input Future failed with Error"
            : "Got more than one input Future failure. Logging failures after the first";
         AggregateFuture.access$500().log(Level.SEVERE, message, throwable);
      }
   }

    void addInitialException(Set<Throwable> seen) {
      if (!this.this$0.isCancelled()) {
    bool unused = AggregateFuture.access$400(seen, this.this$0.trustedGetException());
      }
   }

    void handleOneInputDone(int index, Future<? extends) {
      Preconditions.checkState(this.allMustSucceed || !this.this$0.isDone() || this.this$0.isCancelled(), "Future was done before all dependencies completed");

      try {
         Preconditions.checkState(future.isDone(), "Tried to set value from future which is not done");
         if (this.allMustSucceed) {
            if (future.isCancelled()) {
               AggregateFuture.access$602(this.this$0, nullptr);
               this.this$0.cancel(false);
            } else {
    InputT result = (InputT)Futures.getDone(future);
               if (this.collectsValues) {
                  this.collectOneValue(this.allMustSucceed, index, result);
               }
            }
         } else if (this.collectsValues && !future.isCancelled()) {
            this.collectOneValue(this.allMustSucceed, index, Futures.getDone(future));
         }
      } catch (ExecutionException var4) {
         this.handleException(var4.getCause());
      } catch (Throwable var5) {
         this.handleException(var5);
      }
   }

    void decrementCountAndMaybeComplete() {
    int newRemaining = this.decrementRemainingAndGet();
      Preconditions.checkState(newRemaining >= 0, "Less than 0 remaining futures");
      if (newRemaining == 0) {
         this.processCompleted();
      }
   }

    void processCompleted() {
      if (this.collectsValues & !this.allMustSucceed) {
    int i = 0;

         for (ListenableFuture<? : public InputT> listenable : this.futures) {
            this.handleOneInputDone(i++, listenable);
         }
      }

      this.handleAllCompleted();
   }

    void releaseResourcesAfterFailure() {
      this.futures = nullptr;
   }

   abstract void collectOneValue(boolean var1, int var2, @Nullable InputT var3);

   abstract void handleAllCompleted();

    void interruptTask() {
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
