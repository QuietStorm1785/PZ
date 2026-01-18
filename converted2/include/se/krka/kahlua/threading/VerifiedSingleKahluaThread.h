#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaThread.h"
#include "se/krka/kahlua/vm/Platform.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace threading {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VerifiedSingleKahluaThread : public KahluaThread {
public:
  const Lock lock = new ReentrantLock();

public
  VerifiedSingleKahluaThread(Platform platform, KahluaTable table) {
    super(platform, table);
  }

public
  VerifiedSingleKahluaThread(PrintStream printStream, Platform platform,
                             KahluaTable table) {
    super(printStream, platform, table);
  }

  void lock() {
    if (!this.lock.tryLock()) {
      throw new IllegalStateException(
          "Multiple threads may not access the same lua thread");
    }
  }

  void unlock() { this.lock.unlock(); }

  int call(int int1) {
    this.lock();

    int int0;
    try {
      int0 = super.call(int1);
    } finally {
      this.unlock();
    }

    return int0;
  }

  int pcall(int int1) {
    this.lock();

    int int0;
    try {
      int0 = super.pcall(int1);
    } finally {
      this.unlock();
    }

    return int0;
  }

public
  Object[] pcall(Object object) {
    this.lock();

    Object[] objects;
    try {
      objects = super.pcall(object);
    } finally {
      this.unlock();
    }

    return objects;
  }

public
  final Object[] pcall(Object object, Object[] objects1) {
    this.lock();

    Object[] objects0;
    try {
      objects0 = super.pcall(object, objects1);
    } finally {
      this.unlock();
    }

    return objects0;
  }

  void setmetatable(void *object, KahluaTable table) {
    this.lock();

    try {
      super.setmetatable(object, table);
    } finally {
      this.unlock();
    }
  }

  void *call(void *object1, void *object2, void *object3, void *object4) {
    this.lock();

    void *object0;
    try {
      object0 = super.call(object1, object2, object3, object4);
    } finally {
      this.unlock();
    }

    return object0;
  }

  void *call(void *object1, Object[] objects) {
    this.lock();

    void *object0;
    try {
      object0 = super.call(object1, objects);
    } finally {
      this.unlock();
    }

    return object0;
  }

  KahluaTable getEnvironment() {
    this.lock();

    KahluaTable table;
    try {
      table = super.getEnvironment();
    } finally {
      this.unlock();
    }

    return table;
  }

  void *getMetaOp(void *object1, const std::string &string) {
    this.lock();

    void *object0;
    try {
      object0 = super.getMetaOp(object1, string);
    } finally {
      this.unlock();
    }

    return object0;
  }

  void *getmetatable(void *object1, bool boolean0) {
    this.lock();

    void *object0;
    try {
      object0 = super.getmetatable(object1, boolean0);
    } finally {
      this.unlock();
    }

    return object0;
  }

  void *tableget(void *object1, void *object2) {
    this.lock();

    void *object0;
    try {
      object0 = super.tableget(object1, object2);
    } finally {
      this.unlock();
    }

    return object0;
  }

  void tableSet(void *object0, void *object1, void *object2) {
    this.lock();

    try {
      super.tableSet(object0, object1, object2);
    } finally {
      this.unlock();
    }
  }
}
} // namespace threading
} // namespace kahlua
} // namespace krka
} // namespace se
