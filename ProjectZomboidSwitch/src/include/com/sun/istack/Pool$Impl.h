#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace istack {


class Pool {
public:
   private volatile WeakReference<ConcurrentLinkedQueue<T>> queue;

    T take() {
    T t = this.getQueue().poll();
    return t = = nullptr ? this.create() : t;
   }

    void recycle(T t) {
      this.getQueue().offer(t);
   }

   private ConcurrentLinkedQueue<T> getQueue() {
      WeakReference<ConcurrentLinkedQueue<T>> q = this.queue;
      if (q != nullptr) {
         ConcurrentLinkedQueue<T> d = q.get();
         if (d != nullptr) {
    return d;
         }
      }

      ConcurrentLinkedQueue<T> d = std::make_unique<ConcurrentLinkedQueue<>>();
      this.queue = new WeakReference<>(d);
    return d;
   }

   protected abstract T create();
}
} // namespace istack
} // namespace sun
} // namespace com
