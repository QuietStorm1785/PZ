#pragma once
#include "org/lwjglx/Sys.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Sync {
public:
 static const long NANOS_IN_SECOND = 1000000000L;
 static long nextFrame = 0L;
 static bool initialised = false;
private
 static Sync.RunningAvg sleepDurations = new Sync.RunningAvg(10);
private
 static Sync.RunningAvg yieldDurations = new Sync.RunningAvg(10);

 static void sync(int int0) {
 if (int0 > 0) {
 if (!initialised) {
 initialise();
 }

 try {
 long long0 = getTime();

 while (nextFrame - long0 > sleepDurations.avg()) {
 Thread.sleep(1L);
 long long1;
 sleepDurations.add((long1 = getTime()) - long0);
 long0 = long1;
 }

 sleepDurations.dampenForLowResTicker();
 long0 = getTime();

 while (nextFrame - long0 > yieldDurations.avg()) {
 Thread.yield();
 long long2;
 yieldDurations.add((long2 = getTime()) - long0);
 long0 = long2;
 }
 } catch (InterruptedException interruptedException) {
 }

 nextFrame = Math.max(nextFrame + 1000000000L / int0, getTime());
 }
 }

 static void initialise() {
 initialised = true;
 sleepDurations.init(1000000L);
 yieldDurations.init((int)(-(getTime() - getTime()) * 1.333);
 nextFrame = getTime();
 std::string string = System.getProperty("os.name");
 if (string.startsWith("Win")) {
 Thread thread = new Thread(std::make_unique<Runnable>() {
 void run() {
 try {
 Thread.sleep(Long.MAX_VALUE);
 }
 catch (Exception exception) {
 }
 }
 });
 thread.setName("LWJGL Timer");
 thread.setDaemon(true);
 thread.start();
 } // namespace opengl
 } // namespace lwjglx

 static long getTime() {
 return Sys.getTime() * 1000000000L / Sys.getTimerResolution();
 }

 private
 static class RunningAvg {
 private
 long[] slots;
 int offset;
 static const long DAMPEN_THRESHOLD = 10000000L;
 static const float DAMPEN_FACTOR = 0.9F;

 public
 RunningAvg(int int0) {
 this->slots = new long[int0];
 this->offset = 0;
 }

 void init(long long0) {
 while (this->offset < this->slots.length) {
 this->slots[this->offset++] = long0;
 }
 }

 void add(long long0) {
 this->slots[this->offset++ % this->slots.length] = long0;
 this->offset = this->offset % this->slots.length;
 }

 long avg() {
 long long0 = 0L;

 for (int int0 = 0; int0 < this->slots.length; int0++) {
 long0 += this->slots[int0];
 }

 return long0 / this->slots.length;
 }

 void dampenForLowResTicker() {
 if (this->avg() > 10000000L) {
 for (int int0 = 0; int0 < this->slots.length; int0++) {
 this->slots[int0] = (long)((float)this->slots[int0] * 0.9F);
 }
 }
 }
 }
 } // namespace org
 } // namespace opengl
 } // namespace lwjglx
 } // namespace org
