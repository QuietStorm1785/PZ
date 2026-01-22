#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

class GameProfiler {
public:
    std::string m_frameInvokerKey = "";
    int FrameNo = -1;
    long m_startTime = 0L;
    long m_endTime = 0L;
    long m_totalTime = 0L;

    void transferFrom(GameProfiler$RecordingFrame var1) {
      this.clear();
      this.FrameNo = var1.FrameNo;
      this.m_frameInvokerKey = var1.m_frameInvokerKey;
      this.m_startTime = var1.m_startTime;
      this.m_endTime = var1.m_endTime;
      this.m_totalTime = var1.m_totalTime;
      var1.clear();
   }

    void clear() {
      this.FrameNo = -1;
      this.m_frameInvokerKey = "";
      this.m_startTime = 0L;
      this.m_endTime = 0L;
      this.m_totalTime = 0L;
   }
}
} // namespace zombie
