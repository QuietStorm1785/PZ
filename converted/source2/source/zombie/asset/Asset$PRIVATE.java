package zombie.asset;

import zombie.asset.Asset.ObserverCallback;
import zombie.asset.Asset.State;

final class Asset$PRIVATE implements AssetStateObserver {
   State m_current_state;
   State m_desired_state;
   int m_empty_dep_count;
   int m_failed_dep_count;
   ObserverCallback m_cb;
   AssetTask m_task;

   Asset$PRIVATE(Asset var1) {
      this.this$0 = var1;
      this.m_current_state = State.EMPTY;
      this.m_desired_state = State.EMPTY;
      this.m_empty_dep_count = 1;
      this.m_failed_dep_count = 0;
      this.m_task = null;
   }

   void onCreated(State var1) {
      if (!$assertionsDisabled && this.m_empty_dep_count != 1) {
         throw new AssertionError();
      } else if (!$assertionsDisabled && this.m_failed_dep_count != 0) {
         throw new AssertionError();
      } else {
         this.m_current_state = var1;
         this.m_desired_state = State.READY;
         this.m_failed_dep_count = var1 == State.FAILURE ? 1 : 0;
         this.m_empty_dep_count = 0;
      }
   }

   void addDependency(Asset var1) {
      if (!$assertionsDisabled && this.m_desired_state == State.EMPTY) {
         throw new AssertionError();
      } else {
         var1.getObserverCb().add(this);
         if (var1.isEmpty()) {
            this.m_empty_dep_count++;
         }

         if (var1.isFailure()) {
            this.m_failed_dep_count++;
         }

         this.checkState();
      }
   }

   void removeDependency(Asset var1) {
      var1.getObserverCb().remove(this);
      if (var1.isEmpty()) {
         if (!$assertionsDisabled && this.m_empty_dep_count <= 0) {
            throw new AssertionError();
         }

         this.m_empty_dep_count--;
      }

      if (var1.isFailure()) {
         if (!$assertionsDisabled && this.m_failed_dep_count <= 0) {
            throw new AssertionError();
         }

         this.m_failed_dep_count--;
      }

      this.checkState();
   }

   public void onStateChanged(State var1, State var2, Asset var3) {
      if (!$assertionsDisabled && var1 == var2) {
         throw new AssertionError();
      } else if (!$assertionsDisabled && this.m_current_state == State.EMPTY && this.m_desired_state == State.EMPTY) {
         throw new AssertionError();
      } else {
         if (var1 == State.EMPTY) {
            if (!$assertionsDisabled && this.m_empty_dep_count <= 0) {
               throw new AssertionError();
            }

            this.m_empty_dep_count--;
         }

         if (var1 == State.FAILURE) {
            if (!$assertionsDisabled && this.m_failed_dep_count <= 0) {
               throw new AssertionError();
            }

            this.m_failed_dep_count--;
         }

         if (var2 == State.EMPTY) {
            this.m_empty_dep_count++;
         }

         if (var2 == State.FAILURE) {
            this.m_failed_dep_count++;
         }

         this.checkState();
      }
   }

   void onLoadingSucceeded() {
      if (!$assertionsDisabled && this.m_current_state == State.READY) {
         throw new AssertionError();
      } else if (!$assertionsDisabled && this.m_empty_dep_count != 1) {
         throw new AssertionError();
      } else {
         this.m_empty_dep_count--;
         this.m_task = null;
         this.checkState();
      }
   }

   void onLoadingFailed() {
      if (!$assertionsDisabled && this.m_current_state == State.READY) {
         throw new AssertionError();
      } else if (!$assertionsDisabled && this.m_empty_dep_count != 1) {
         throw new AssertionError();
      } else {
         this.m_failed_dep_count++;
         this.m_empty_dep_count--;
         this.m_task = null;
         this.checkState();
      }
   }

   void checkState() {
      State var1 = this.m_current_state;
      if (this.m_failed_dep_count > 0 && this.m_current_state != State.FAILURE) {
         this.m_current_state = State.FAILURE;
         this.this$0.getAssetManager().onStateChanged(var1, this.m_current_state, this.this$0);
         if (this.m_cb != null) {
            this.m_cb.invoke(var1, this.m_current_state, this.this$0);
         }
      }

      if (this.m_failed_dep_count == 0) {
         if (this.m_empty_dep_count == 0 && this.m_current_state != State.READY && this.m_desired_state != State.EMPTY) {
            this.this$0.onBeforeReady();
            this.m_current_state = State.READY;
            this.this$0.getAssetManager().onStateChanged(var1, this.m_current_state, this.this$0);
            if (this.m_cb != null) {
               this.m_cb.invoke(var1, this.m_current_state, this.this$0);
            }
         }

         if (this.m_empty_dep_count > 0 && this.m_current_state != State.EMPTY) {
            this.this$0.onBeforeEmpty();
            this.m_current_state = State.EMPTY;
            this.this$0.getAssetManager().onStateChanged(var1, this.m_current_state, this.this$0);
            if (this.m_cb != null) {
               this.m_cb.invoke(var1, this.m_current_state, this.this$0);
            }
         }
      }
   }
}
