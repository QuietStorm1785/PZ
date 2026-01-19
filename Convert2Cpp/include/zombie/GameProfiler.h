#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameProfiler/ProfileArea.h"
#include "zombie/GameProfiler/RecordingFrame.h"
#include "zombie/core/profiling/TriggerGameProfilerFile.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/ui/TextManager.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/lambda/Invokers/Params1/ICallback.h"
#include <algorithm>

namespace zombie {


class GameProfiler {
public:
    static const std::string s_currentSessionUUID = UUID.randomUUID().toString();
   private static final ThreadLocal<GameProfiler> s_instance = ThreadLocal.withInitial(GameProfiler::new);
   private final Stack<ProfileArea> m_stack = std::make_unique<Stack<>>();
    auto m_currentFrame = std::make_shared<RecordingFrame>();
    auto m_previousFrame = std::make_shared<RecordingFrame>();
    bool m_isInFrame;
    const GameProfileRecording m_recorder;
    static const void* m_gameProfilerRecordingTriggerLock = "Game Profiler Recording Watcher, synchronization lock";
    static PredicatedFileWatcher m_gameProfilerRecordingTriggerWatcher;

    private GameProfiler() {
    std::string var1 = Thread.currentThread().getName();
    std::string var2 = var1.replace("-", "").replace(" ", "");
    std::string var3 = String.format("%s_GameProfiler_%s", this.getCurrentSessionUUID(), var2);
      this.m_recorder = new GameProfileRecording(var3);
   }

    static void onTrigger_setAnimationRecorderTriggerFile(TriggerGameProfilerFile var0) {
      DebugOptions.instance.GameProfilerEnabled.setValue(var0.isRecording);
   }

    std::string getCurrentSessionUUID() {
    return s_currentSessionUUID;
   }

    static GameProfiler getInstance() {
      return s_instance.get();
   }

    void startFrame(const std::string& var1) {
      if (this.m_isInFrame) {
         throw new RuntimeException("Already inside a frame.");
      } else {
         this.m_isInFrame = true;
         if (!this.m_stack.empty()) {
            throw new RuntimeException("Recording stack should be empty.");
         } else {
    int var2 = IsoCamera.frameState.frameCount;
            if (this.m_currentFrame.FrameNo != var2) {
               this.m_previousFrame.transferFrom(this.m_currentFrame);
               if (this.m_previousFrame.FrameNo != -1) {
                  this.m_recorder.writeLine();
               }

    long var3 = getTimeNs();
               this.m_currentFrame.FrameNo = var2;
               this.m_currentFrame.m_frameInvokerKey = var1;
               this.m_currentFrame.m_startTime = var3;
               this.m_recorder.reset();
               this.m_recorder.setFrameNumber(this.m_currentFrame.FrameNo);
               this.m_recorder.setStartTime(this.m_currentFrame.m_startTime);
            }
         }
      }
   }

    void endFrame() {
      this.m_currentFrame.m_endTime = getTimeNs();
      this.m_currentFrame.m_totalTime = this.m_currentFrame.m_endTime - this.m_currentFrame.m_startTime;
      this.m_isInFrame = false;
   }

    void invokeAndMeasureFrame(const std::string& var1, Runnable var2) {
      if (!isRunning()) {
         var2.run();
      } else {
         this.startFrame(var1);

         try {
            this.invokeAndMeasure(var1, var2);
         } finally {
            this.endFrame();
         }
      }
   }

    void invokeAndMeasure(const std::string& var1, Runnable var2) {
      if (!isRunning()) {
         var2.run();
      } else if (!this.m_isInFrame) {
         DebugLog.General.warn("Not inside in a frame. Find the root caller function for this thread, and add call to invokeAndMeasureFrame.");
      } else {
    ProfileArea var3 = this.start(var1);

         try {
            var2.run();
         } finally {
            this.end(var3);
         }
      }
   }

    static bool isRunning() {
      return DebugOptions.instance.GameProfilerEnabled.getValue();
   }

   public <T1> void invokeAndMeasure(String var1, T1 var2, ICallback<T1> var3) {
      if (!isRunning()) {
         var3.accept(var2);
      } else {
         Lambda.capture(this, var1, var2, var3, (var0, var1x, var2x, var3x, var4) -> var1x.invokeAndMeasure(var2x, var0.invoker(var3x, var4)));
      }
   }

   public <T1, T2> void invokeAndMeasure(String var1, T1 var2, T2 var3, zombie.util.lambda.Invokers.Params2.ICallback<T1, T2> var4) {
      if (!isRunning()) {
         var4.accept(var2, var3);
      } else {
         Lambda.capture(
            this, var1, var2, var3, var4, (var0, var1x, var2x, var3x, var4x, var5) -> var1x.invokeAndMeasure(var2x, var0.invoker(var3x, var4x, var5))
         );
      }
   }

   public <T1, T2, T3> void invokeAndMeasure(String var1, T1 var2, T2 var3, T3 var4, zombie.util.lambda.Invokers.Params3.ICallback<T1, T2, T3> var5) {
      if (!isRunning()) {
         var5.accept(var2, var3, var4);
      } else {
         Lambda.capture(
            this,
            var1,
            var2,
            var3,
            var4,
            var5,
            (var0, var1x, var2x, var3x, var4x, var5x, var6) -> var1x.invokeAndMeasure(var2x, var0.invoker(var3x, var4x, var5x, var6))
         );
      }
   }

    ProfileArea start(const std::string& var1) {
    long var2 = getTimeNs();
    ProfileArea var4 = ProfileArea.alloc();
      var4.Key = var1;
      return this.start(var4, var2);
   }

    ProfileArea start(ProfileArea var1) {
    long var2 = getTimeNs();
      return this.start(var1, var2);
   }

    ProfileArea start(ProfileArea var1, long var2) {
      var1.StartTime = var2;
      var1.Depth = this.m_stack.size();
      if (!this.m_stack.isEmpty()) {
    ProfileArea var4 = this.m_stack.peek();
         var4.Children.add(var1);
      }

      this.m_stack.push(var1);
    return var1;
   }

    void end(ProfileArea var1) {
      var1.EndTime = getTimeNs();
      var1.Total = var1.EndTime - var1.StartTime;
      if (this.m_stack.peek() != var1) {
         throw new RuntimeException("Incorrect exit. ProfileArea " + var1 + " is not at the top of the stack: " + this.m_stack.peek());
      } else {
         this.m_stack.pop();
         if (this.m_stack.isEmpty()) {
            this.m_recorder.logTimeSpan(var1);
            var1.release();
         }
      }
   }

    void renderPercent(const std::string& var1, long var2, int var4, int var5, float var6, float var7, float var8) {
    float var9 = (float)var2 / (float)this.m_previousFrame.m_totalTime;
      var9 *= 100.0F;
      var9 = (int)(var9 * 10.0F) / 10.0F;
      TextManager.instance.DrawString(var4, var5, var1, var6, var7, var8, 1.0);
      TextManager.instance.DrawString(var4 + 300, var5, var9 + "%", var6, var7, var8, 1.0);
   }

    void render(int var1, int var2) {
      this.renderPercent(this.m_previousFrame.m_frameInvokerKey, this.m_previousFrame.m_totalTime, var1, var2, 1.0F, 1.0F, 1.0F);
   }

    static long getTimeNs() {
      return System.nanoTime();
   }

    static void init() {
      initTriggerWatcher();
   }

    static void initTriggerWatcher() {
      if (m_gameProfilerRecordingTriggerWatcher == nullptr) {
         synchronized (m_gameProfilerRecordingTriggerLock) {
            if (m_gameProfilerRecordingTriggerWatcher == nullptr) {
               m_gameProfilerRecordingTriggerWatcher = new PredicatedFileWatcher(
                  ZomboidFileSystem.instance.getMessagingDirSub("Trigger_PerformanceProfiler.xml"),
                  TriggerGameProfilerFile.class,
                  GameProfiler::onTrigger_setAnimationRecorderTriggerFile
               );
               DebugFileWatcher.instance.add(m_gameProfilerRecordingTriggerWatcher);
            }
         }
      }
   }
}
} // namespace zombie
