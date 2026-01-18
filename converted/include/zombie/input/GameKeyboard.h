#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/input/KeyEventQueue.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GameKeyboard {
public:
 private static boolean[] bDown;
 private static boolean[] bLastDown;
 private static boolean[] bEatKey;
 static bool bNoEventsWhileLoading = false;
 static bool doLuaKeyPressed = true;
 static const KeyboardStateCache s_keyboardStateCache = new KeyboardStateCache();

 static void update() {
 if (!s_keyboardStateCache.getState().isCreated()) {
 s_keyboardStateCache.swap();
 } else {
 int int0 = s_keyboardStateCache.getState().getKeyCount();
 if (bDown.empty()) {
 bDown = new boolean[int0];
 bLastDown = new boolean[int0];
 bEatKey = new boolean[int0];
 }

 bool boolean0 = Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.DoingTextEntry;

 for (int int1 = 1; int1 < int0; int1++) {
 bLastDown[int1] = bDown[int1];
 bDown[int1] = s_keyboardStateCache.getState().isKeyDown(int1);
 if (!bDown[int1] && bLastDown[int1]) {
 if (bEatKey[int1]) {
 bEatKey[int1] = false;
 continue;
 }

 if (bNoEventsWhileLoading || boolean0 || LuaManager.thread == UIManager.defaultthread && UIManager.onKeyRelease(int1) {
 continue;
 }

 if (Core.bDebug && !doLuaKeyPressed) {
 System.out.println("KEY RELEASED " + int1 + " doLuaKeyPressed=false");
 }

 if (LuaManager.thread == UIManager.defaultthread && doLuaKeyPressed) {
 LuaEventManager.triggerEvent("OnKeyPressed", int1);
 }

 if (LuaManager.thread == UIManager.defaultthread) {
 LuaEventManager.triggerEvent("OnCustomUIKey", int1);
 LuaEventManager.triggerEvent("OnCustomUIKeyReleased", int1);
 }
 }

 if (bDown[int1] && bLastDown[int1]) {
 if (bNoEventsWhileLoading || boolean0 || LuaManager.thread == UIManager.defaultthread && UIManager.onKeyRepeat(int1) {
 continue;
 }

 if (LuaManager.thread == UIManager.defaultthread && doLuaKeyPressed) {
 LuaEventManager.triggerEvent("OnKeyKeepPressed", int1);
 }
 }

 if (bDown[int1]
 && !bLastDown[int1]
 && !bNoEventsWhileLoading
 && !boolean0
 && !bEatKey[int1]
 && (LuaManager.thread != UIManager.defaultthread || !UIManager.onKeyPress(int1)
 && !bEatKey[int1]) {
 if (LuaManager.thread == UIManager.defaultthread && doLuaKeyPressed) {
 LuaEventManager.triggerEvent("OnKeyStartPressed", int1);
 }

 if (LuaManager.thread == UIManager.defaultthread) {
 LuaEventManager.triggerEvent("OnCustomUIKeyPressed", int1);
 }
 }
 }

 s_keyboardStateCache.swap();
 }
 }

 static void poll() {
 s_keyboardStateCache.poll();
 }

 /**
 * Has the key been pressed. Not continuous. That is, is the key down now, but was not down before.
 */
 static bool isKeyPressed(int key) {
 return isKeyDown();
 }

 /**
 * Is the key down. Continuous.
 */
 static bool isKeyDown(int key) {
 if (Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.DoingTextEntry) {
 return false;
 } else {
 return bDown = = nullptr ? false : bDown[key];
 }
 }

 /**
 * Was they key down last frame. Continuous.
 */
 static bool wasKeyDown(int key) {
 if (Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.DoingTextEntry) {
 return false;
 } else {
 return bLastDown = = nullptr ? false : bLastDown[key];
 }
 }

 static void eatKeyPress(int key) {
 if (key >= 0 && key < bEatKey.length) {
 bEatKey[key] = true;
 }
 }

 static void setDoLuaKeyPressed(bool doIt) {
 doLuaKeyPressed = doIt;
 }

 static KeyEventQueue getEventQueue() {
 assert Thread.currentThread() == GameWindow.GameThread;

 return s_keyboardStateCache.getState().getEventQueue();
 }

 static KeyEventQueue getEventQueuePolling() {
 assert Thread.currentThread() == RenderThread.RenderThread;

 return s_keyboardStateCache.getStatePolling().getEventQueue();
 }
}
} // namespace input
} // namespace zombie
