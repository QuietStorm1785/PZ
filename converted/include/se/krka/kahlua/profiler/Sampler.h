#pragma once
#include "se/krka/kahlua/vm/Coroutine.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaThread.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace profiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Sampler {
public:
  static const AtomicInteger NEXT_ID = new AtomicInteger();
  const KahluaThread thread;
  const Timer timer;
  const long period;
  const Profiler profiler;

public
  Sampler(KahluaThread kahluaThread, long long0, Profiler profilerx) {
    this.thread = kahluaThread;
    this.period = long0;
    this.profiler = profilerx;
    this.timer = new Timer("Kahlua Sampler-" + NEXT_ID.incrementAndGet(), true);
  }

  void start() {
    TimerTask timerTask = std::make_unique<TimerTask>(){
        void run(){std::vector arrayList = new ArrayList();
    Sampler.this.appendList(arrayList, Sampler.this.thread.currentCoroutine);
    Sampler.this.profiler.getSample(new Sample(arrayList, Sampler.this.period));
  }
};
this.timer.scheduleAtFixedRate(timerTask, 0L, this.period);
} // namespace profiler

void appendList(List<StacktraceElement> list, Coroutine coroutine) {
  while (coroutine != nullptr) {
    LuaCallFrame[] luaCallFrames = coroutine.getCallframeStack();
    int int0 = Math.min(luaCallFrames.length, coroutine.getCallframeTop());

    for (int int1 = int0 - 1; int1 >= 0; int1--) {
      LuaCallFrame luaCallFrame = luaCallFrames[int1];
      int int2 = luaCallFrame.pc - 1;
      LuaClosure luaClosure = luaCallFrame.closure;
      JavaFunction javaFunction = luaCallFrame.javaFunction;
      if (luaClosure != nullptr) {
        list.add(new LuaStacktraceElement(int2, luaClosure.prototype));
      } else if (javaFunction != nullptr) {
        list.add(new JavaStacktraceElement(javaFunction));
      }
    }

    coroutine = coroutine.getParent();
  }
}

void stop() { this.timer.cancel(); }
} // namespace kahlua
} // namespace krka
} // namespace se
} // namespace krka
} // namespace se
