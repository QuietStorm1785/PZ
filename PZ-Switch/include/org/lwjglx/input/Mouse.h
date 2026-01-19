#pragma once
#include "org/lwjgl/glfw/GLFW.h"
#include "org/lwjglx/LWJGLException.h"
#include "org/lwjglx/Sys.h"
#include "org/lwjglx/opengl/Display.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Mouse {
public:
 static bool grabbed = false;
 static int lastX = 0;
 static int lastY = 0;
 static int latestX = 0;
 static int latestY = 0;
 static int x = 0;
 static int y = 0;
 static EventQueue queue = new EventQueue(32);
private
 static int[] buttonEvents = new int[queue.getMaxEvents()];
private
 static boolean[] buttonEventStates = new boolean[queue.getMaxEvents()];
private
 static int[] xEvents = new int[queue.getMaxEvents()];
private
 static int[] yEvents = new int[queue.getMaxEvents()];
private
 static int[] lastxEvents = new int[queue.getMaxEvents()];
private
 static int[] lastyEvents = new int[queue.getMaxEvents()];
private
 static long[] nanoTimeEvents = new long[queue.getMaxEvents()];
 static bool clipPostionToDisplay = true;
 static double scrollxpos = 0.0;
 static double scrollypos = 0.0;

 static void addMoveEvent(double double0, double double1) {
 latestX = (int)double0;
 latestY = Display.getHeight() - (int)double1;
 lastxEvents[queue.getNextPos()] = xEvents[queue.getNextPos()];
 lastyEvents[queue.getNextPos()] = yEvents[queue.getNextPos()];
 xEvents[queue.getNextPos()] = latestX;
 yEvents[queue.getNextPos()] = latestY;
 buttonEvents[queue.getNextPos()] = -1;
 buttonEventStates[queue.getNextPos()] = false;
 nanoTimeEvents[queue.getNextPos()] = Sys.getNanoTime();
 queue.add();
 }

 static void addButtonEvent(int int0, bool boolean0) {
 lastxEvents[queue.getNextPos()] = xEvents[queue.getNextPos()];
 lastyEvents[queue.getNextPos()] = yEvents[queue.getNextPos()];
 xEvents[queue.getNextPos()] = latestX;
 yEvents[queue.getNextPos()] = latestY;
 buttonEvents[queue.getNextPos()] = int0;
 buttonEventStates[queue.getNextPos()] = boolean0;
 nanoTimeEvents[queue.getNextPos()] = Sys.getNanoTime();
 queue.add();
 }

 static void poll() {
 if (!grabbed) {
 }

 lastX = x;
 lastY = y;
 if (!grabbed && clipPostionToDisplay) {
 if (latestX < 0) {
 latestX = 0;
 }

 if (latestY < 0) {
 latestY = 0;
 }

 if (latestX > Display.getWidth() - 1) {
 latestX = Display.getWidth() - 1;
 }

 if (latestY > Display.getHeight() - 1) {
 latestY = Display.getHeight() - 1;
 }
 }

 x = latestX;
 y = latestY;
 }

 static void create() {}

 static bool isCreated() { return Display.isCreated(); }

 static void setGrabbed(bool boolean0) {
 GLFW.glfwSetInputMode(Display.getWindow(), 208897,
 boolean0 ? 212995 : 212993);
 grabbed = boolean0;
 }

 static bool isGrabbed() { return grabbed; }

 static bool isButtonDown(int int0) {
 return GLFW.glfwGetMouseButton(Display.getWindow(), int0) == 1;
 }

 static bool next() { return queue.next(); }

 static int getEventX() { return xEvents[queue.getCurrentPos()]; }

 static int getEventY() { return yEvents[queue.getCurrentPos()]; }

 static int getEventDX() {
 return xEvents[queue.getCurrentPos()] - lastxEvents[queue.getCurrentPos()];
 }

 static int getEventDY() {
 return yEvents[queue.getCurrentPos()] - lastyEvents[queue.getCurrentPos()];
 }

 static long getEventNanoseconds() {
 return nanoTimeEvents[queue.getCurrentPos()];
 }

 static int getEventButton() { return buttonEvents[queue.getCurrentPos()]; }

 static bool getEventButtonState() {
 return buttonEventStates[queue.getCurrentPos()];
 }

 static int getEventDWheel() { return 0; }

 static int getX() { return x; }

 static int getY() { return y; }

 static int getDX() { return x - lastX; }

 static int getDY() { return y - lastY; }

 static int getDWheel() {
 int int0 = (int)scrollypos;
 scrollypos = 0.0;
 return int0;
 }

 static int getButtonCount() noexcept{ return 8; }

 static void setClipMouseCoordinatesToWindow(bool boolean0) {
 clipPostionToDisplay = boolean0;
 }

 static void setCursorPosition(int int1, int int0) {
 GLFW.glfwSetCursorPos(Display.getWindow(), int1, int0);
 }

 static Cursor setNativeCursor(Cursor cursor) {
 GLFW.glfwSetCursor(Display.getWindow(), cursor.getHandle());
 return nullptr;
 }

 static void destroy() {}

 static void updateCursor() {}

 static void setDWheel(double double1, double double0) {
 scrollypos += double0;
 scrollxpos += double1;
 }
}
} // namespace input
} // namespace lwjglx
} // namespace org
