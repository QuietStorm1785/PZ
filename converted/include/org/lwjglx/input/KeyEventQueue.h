#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/Sys.h"

namespace org {
namespace lwjglx {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class KeyEventQueue {
public:
 static const int MAX_EVENTS = 32;
 const EventQueue queue = new EventQueue(32);
 private int[] keyEvents = new int[32];
 private boolean[] keyEventStates = new boolean[32];
 private long[] nanoTimeEvents = new long[32];
 private char[] keyEventChars = new char[256];

 void addKeyEvent(int arg0, int arg1) {
 switch (arg1) {
 case 2:
 if (!Keyboard.isRepeatEvent()) {
 break;
 }
 case 0:
 case 1:
 this->keyEvents[this->queue.getNextPos()] = KeyCodes.toLwjglKey(arg0);
 this->keyEventStates[this->queue.getNextPos()] = arg1 == 1 || arg1 == 2;
 this->keyEventChars[this->queue.getNextPos()] = 0;
 this->nanoTimeEvents[this->queue.getNextPos()] = Sys.getNanoTime();
 this->queue.add();
 }
 }

 void addCharEvent(char arg0) {
 this->keyEvents[this->queue.getNextPos()] = 0;
 this->keyEventStates[this->queue.getNextPos()] = true;
 this->keyEventChars[this->queue.getNextPos()] = arg0;
 this->nanoTimeEvents[this->queue.getNextPos()] = Sys.getNanoTime();
 this->queue.add();
 }

 bool next() {
 return this->queue.next();
 }

 int getEventKey() {
 return this->keyEvents[this->queue.getCurrentPos()];
 }

 char getEventCharacter() {
 return this->keyEventChars[this->queue.getCurrentPos()];
 }

 bool getEventKeyState() {
 return this->keyEventStates[this->queue.getCurrentPos()];
 }

 long getEventNanoseconds() {
 return this->nanoTimeEvents[this->queue.getCurrentPos()];
 }
}
} // namespace input
} // namespace lwjglx
} // namespace org
