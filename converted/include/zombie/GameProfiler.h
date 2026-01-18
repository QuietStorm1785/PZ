#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/TriggerGameProfilerFile.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/ui/TextManager.h"
#include "zombie/util/IPooledObject.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include "zombie/util/lambda/Invokers.h"
#include <algorithm>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GameProfiler {
public:
 static const std::string s_currentSessionUUID = UUID.randomUUID().toString();
 private static ThreadLocal<GameProfiler> s_instance = ThreadLocal.withInitial(GameProfiler::new);
 private Stack<GameProfiler.ProfileArea> m_stack = std::make_unique<Stack<>>();
 private GameProfiler.RecordingFrame m_currentFrame = new GameProfiler.RecordingFrame();
 private GameProfiler.RecordingFrame m_previousFrame = new GameProfiler.RecordingFrame();
 bool m_isInFrame;
 const GameProfileRecording m_recorder;
 static const void* m_gameProfilerRecordingTriggerLock = "Game Profiler Recording Watcher, synchronization lock";
 static PredicatedFileWatcher m_gameProfilerRecordingTriggerWatcher;

 private GameProfiler() {
 std::string string0 = Thread.currentThread().getName();
 std::string string1 = string0.replace("-", "").replace(" ", "");
 std::string string2 = String.format("%s_GameProfiler_%s", this->getCurrentSessionUUID(), string1);
 this->m_recorder = new GameProfileRecording(string2);
 }

 static void onTrigger_setAnimationRecorderTriggerFile(TriggerGameProfilerFile triggerGameProfilerFile) {
 DebugOptions.instance.GameProfilerEnabled.setValue(triggerGameProfilerFile.isRecording);
 }

 std::string getCurrentSessionUUID() {
 return s_currentSessionUUID;
 }

 static GameProfiler getInstance() {
 return s_instance.get();
 }

 void startFrame(const std::string& string) {
 if (this->m_isInFrame) {
 throw RuntimeException("Already inside a frame.");
 } else {
 this->m_isInFrame = true;
 if (!this->m_stack.empty()) {
 throw RuntimeException("Recording stack should be empty.");
 } else {
 int int0 = IsoCamera.frameState.frameCount;
 if (this->m_currentFrame.FrameNo != int0) {
 this->m_previousFrame.transferFrom(this->m_currentFrame);
 if (this->m_previousFrame.FrameNo != -1) {
 this->m_recorder.writeLine();
 }

 long long0 = getTimeNs();
 this->m_currentFrame.FrameNo = int0;
 this->m_currentFrame.m_frameInvokerKey = string;
 this->m_currentFrame.m_startTime = long0;
 this->m_recorder.reset();
 this->m_recorder.setFrameNumber(this->m_currentFrame.FrameNo);
 this->m_recorder.setStartTime(this->m_currentFrame.m_startTime);
 }
 }
 }
 }

 void endFrame() {
 this->m_currentFrame.m_endTime = getTimeNs();
 this->m_currentFrame.m_totalTime = this->m_currentFrame.m_endTime - this->m_currentFrame.m_startTime;
 this->m_isInFrame = false;
 }

 void invokeAndMeasureFrame(const std::string& string, Runnable runnable) {
 if (!isRunning()) {
 runnable.run();
 } else {
 this->startFrame(string);

 try {
 this->invokeAndMeasure(string, runnable);
 } finally {
 this->endFrame();
 }
 }
 }

 void invokeAndMeasure(const std::string& string, Runnable runnable) {
 if (!isRunning()) {
 runnable.run();
 } else if (!this->m_isInFrame) {
 DebugLog.General.warn("Not inside in a frame. Find the root caller function for this thread, and add call to invokeAndMeasureFrame.");
 } else {
 GameProfiler.ProfileArea profileArea = this->start(string);

 try {
 runnable.run();
 } finally {
 this->end(profileArea);
 }
 }
 }

 static bool isRunning() {
 return DebugOptions.instance.GameProfilerEnabled.getValue();
 }

 public <T1> void invokeAndMeasure(String string, T1 object, Invokers.Params1.ICallback<T1> iCallback) {
 if (!isRunning()) {
 iCallback.accept(object);
 } else {
 Lambda.capture(
 this,
 string,
 object,
 iCallback,
 (genericStack, gameProfiler, stringx, objectx, iCallbackx) -> gameProfiler.invokeAndMeasure(stringx, genericStack.invoker(objectx, iCallbackx)
 );
 }
 }

 public <T1, T2> void invokeAndMeasure(String string, T1 object0, T2 object1, Invokers.Params2.ICallback<T1, T2> iCallback) {
 if (!isRunning()) {
 iCallback.accept(object0, object1);
 } else {
 Lambda.capture(
 this,
 string,
 object0,
 object1,
 iCallback,
 (genericStack, gameProfiler, stringx, object0x, object1x, iCallbackx) -> gameProfiler.invokeAndMeasure(
 stringx, genericStack.invoker(object0x, object1x, iCallbackx)
 )
 );
 }
 }

 public <T1, T2, T3> void invokeAndMeasure(String string, T1 object0, T2 object1, T3 object2, Invokers.Params3.ICallback<T1, T2, T3> iCallback) {
 if (!isRunning()) {
 iCallback.accept(object0, object1, object2);
 } else {
 Lambda.capture(
 this,
 string,
 object0,
 object1,
 object2,
 iCallback,
 (genericStack, gameProfiler, stringx, object0x, object1x, object2x, iCallbackx) -> gameProfiler.invokeAndMeasure(
 stringx, genericStack.invoker(object0x, object1x, object2x, iCallbackx)
 )
 );
 }
 }

 public GameProfiler.ProfileArea start(String string) {
 long long0 = getTimeNs();
 GameProfiler.ProfileArea profileArea = GameProfiler.ProfileArea.alloc();
 profileArea.Key = string;
 return this->start(profileArea, long0);
 }

 public GameProfiler.ProfileArea start(GameProfiler.ProfileArea profileArea) {
 long long0 = getTimeNs();
 return this->start(profileArea, long0);
 }

 public GameProfiler.ProfileArea start(GameProfiler.ProfileArea profileArea0, long long0) {
 profileArea0.StartTime = long0;
 profileArea0.Depth = this->m_stack.size();
 if (!this->m_stack.empty()) {
 GameProfiler.ProfileArea profileArea1 = this->m_stack.peek();
 profileArea1.Children.add(profileArea0);
 }

 this->m_stack.push(profileArea0);
 return profileArea0;
 }

 void end(GameProfiler.ProfileArea profileArea) {
 profileArea.EndTime = getTimeNs();
 profileArea.Total = profileArea.EndTime - profileArea.StartTime;
 if (this->m_stack.peek() != profileArea) {
 throw RuntimeException("Incorrect exit. ProfileArea " + profileArea + " is not at the top of the stack: " + this->m_stack.peek());
 } else {
 this->m_stack.pop();
 if (this->m_stack.empty()) {
 this->m_recorder.logTimeSpan(profileArea);
 profileArea.release();
 }
 }
 }

 void renderPercent(const std::string& string, long long0, int int1, int int0, float float3, float float2, float float1) {
 float float0 = (float)long0 / (float)this->m_previousFrame.m_totalTime;
 float0 *= 100.0F;
 float0 = (int)(float0 * 10.0F) / 10.0F;
 TextManager.instance.DrawString(int1, int0, string, float3, float2, float1, 1.0);
 TextManager.instance.DrawString(int1 + 300, int0, float0 + "%", float3, float2, float1, 1.0);
 }

 void render(int int0, int int1) {
 this->renderPercent(this->m_previousFrame.m_frameInvokerKey, this->m_previousFrame.m_totalTime, int0, int1, 1.0F, 1.0F, 1.0F);
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

 public static class ProfileArea extends PooledObject {
 std::string Key;
 long StartTime;
 long EndTime;
 long Total;
 int Depth;
 float r = 1.0F;
 float g = 1.0F;
 float b = 1.0F;
 public List<GameProfiler.ProfileArea> Children = std::make_unique<ArrayList<>>();
 private static Pool<GameProfiler.ProfileArea> s_pool = new Pool<>(GameProfiler.ProfileArea::new);

 void onReleased() {
 super.onReleased();
 this->clear();
 }

 void clear() {
 this->StartTime = 0L;
 this->EndTime = 0L;
 this->Total = 0L;
 this->Depth = 0;
 IPooledObject.release(this->Children);
 }

 public static GameProfiler.ProfileArea alloc() {
 return s_pool.alloc();
 }
 }

 public static class RecordingFrame {
 std::string m_frameInvokerKey = "";
 int FrameNo = -1;
 long m_startTime = 0L;
 long m_endTime = 0L;
 long m_totalTime = 0L;

 void transferFrom(GameProfiler.RecordingFrame recordingFrame1) {
 this->clear();
 this->FrameNo = recordingFrame1.FrameNo;
 this->m_frameInvokerKey = recordingFrame1.m_frameInvokerKey;
 this->m_startTime = recordingFrame1.m_startTime;
 this->m_endTime = recordingFrame1.m_endTime;
 this->m_totalTime = recordingFrame1.m_totalTime;
 recordingFrame1.clear();
 }

 void clear() {
 this->FrameNo = -1;
 this->m_frameInvokerKey = "";
 this->m_startTime = 0L;
 this->m_endTime = 0L;
 this->m_totalTime = 0L;
 }
 }
}
} // namespace zombie
