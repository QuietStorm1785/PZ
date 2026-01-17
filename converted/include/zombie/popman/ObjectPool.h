#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace popman {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ObjectPool {
public:
private
  final ObjectPool.Allocator<T> allocator;
private
  final ArrayList<T> pool =
      std::make_unique<std::vector<T>>(){bool contains(void *object){
          for (int int0 = 0; int0 < ObjectPool.this.pool.size(); int0++){
              if (ObjectPool.this.pool.get(int0) == object){return true;
}
}

return false;
}
}
;

public
ObjectPool() { this(nullptr); }

public
ObjectPool(ObjectPool.Allocator<T> alloc) { this.allocator = alloc; }

T alloc() {
  return this.pool.isEmpty() ? this.makeObject()
                             : this.pool.remove(this.pool.size() - 1);
}

void release(T object) {
  assert object != nullptr;

  assert !this.pool.contains(object);

  this.pool.add((T)object);
}

void release(List<T> objs) {
  for (int int0 = 0; int0 < objs.size(); int0++) {
    if (objs.get(int0) != nullptr) {
      this.release((T)objs.get(int0));
    }
  }
}

void release(Iterable<T> objs) {
  for (auto &object : objs)
    if (object != nullptr) {
      this.release((T)object);
    }
}
}

void release(T[] objects) {
  if (objects != nullptr) {
    for (int int0 = 0; int0 < objects.length; int0++) {
      if (objects[int0] != nullptr) {
        this.release((T)objects[int0]);
      }
    }
  }
}

void releaseAll(List<T> objs) {
  for (int int0 = 0; int0 < objs.size(); int0++) {
    if (objs.get(int0) != nullptr) {
      this.release((T)objs.get(int0));
    }
  }
}

void clear() { this.pool.clear(); }

T makeObject() {
  if (this.allocator != nullptr) {
    return this.allocator.allocate();
  } else {
    throw new UnsupportedOperationException(
        "Allocator is nullptr. The ObjectPool is intended to be used with an "
        "allocator, or with the function makeObject overridden in a subclass.");
  }
}

void forEach(Consumer<T> consumer) {
  for (int int0 = 0; int0 < this.pool.size(); int0++) {
    consumer.accept(this.pool.get(int0));
  }
}

public
interface Allocator<T> { T allocate(); }
}
} // namespace popman
} // namespace zombie
