#pragma once
#include "java/awt/image/BufferedImage.h"
#include "javax/imageio/ImageIO.h"
#include "org/lwjgl/BufferUtils.h"
#include "org/lwjglx/LWJGLException.h"
#include "org/lwjglx/input/Cursor.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Mouse {
public:
 static int x;
 static int y;
 static bool bLeftDown;
 static bool bLeftWasDown;
 static bool bRightDown;
 static bool bRightWasDown;
 static bool bMiddleDown;
 static bool bMiddleWasDown;
public
 static boolean[] m_buttonDownStates;
 static long lastActivity;
 static int wheelDelta;
 static const MouseStateCache s_mouseStateCache = new MouseStateCache();
public
 static boolean[] UICaptured = new boolean[10];
 static Cursor blankCursor;
 static Cursor defaultCursor;
 static bool isCursorVisible = true;
 static Texture mouseCursorTexture = nullptr;

 static int getWheelState() { return wheelDelta; }

public
 static int getXA() { return x; }

public
 static int getYA() { return y; }

public
 static int getX() {
 return (int)(x * Core.getInstance().getZoom(0);
 }

public
 static int getY() {
 return (int)(y * Core.getInstance().getZoom(0);
 }

 static bool isButtonDown(int number) {
 return m_buttonDownStates != nullptr ? m_buttonDownStates[number] : false;
 }

 static void UIBlockButtonDown(int number) { UICaptured[number] = true; }

 static bool isButtonDownUICheck(int number) {
 if (m_buttonDownStates != nullptr) {
 bool boolean0 = m_buttonDownStates[number];
 if (!boolean0) {
 UICaptured[number] = false;
 } else if (UICaptured[number]) {
 return false;
 }

 return boolean0;
 } else {
 return false;
 }
 }

 static bool isLeftDown() { return bLeftDown; }

 static bool isLeftPressed() { return !bLeftWasDown && bLeftDown; }

 static bool isLeftReleased() { return bLeftWasDown && !bLeftDown; }

 static bool isLeftUp() { return !bLeftDown; }

 static bool isMiddleDown() { return bMiddleDown; }

 static bool isMiddlePressed() { return !bMiddleWasDown && bMiddleDown; }

 static bool isMiddleReleased() { return bMiddleWasDown && !bMiddleDown; }

 static bool isMiddleUp() { return !bMiddleDown; }

 static bool isRightDown() { return bRightDown; }

 static bool isRightPressed() { return !bRightWasDown && bRightDown; }

 static bool isRightReleased() { return bRightWasDown && !bRightDown; }

 static bool isRightUp() { return !bRightDown; }

public
 static void update() {
 MouseState mouseState = s_mouseStateCache.getState();
 if (!mouseState.isCreated()) {
 s_mouseStateCache.swap();

 try {
 org.lwjglx.input.Mouse.create();
 } catch (LWJGLException lWJGLException) {
 lWJGLException.printStackTrace();
 }
 } else {
 bLeftWasDown = bLeftDown;
 bRightWasDown = bRightDown;
 bMiddleWasDown = bMiddleDown;
 int int0 = x;
 int int1 = y;
 x = mouseState.getX();
 y = Core.getInstance().getScreenHeight() - mouseState.getY() - 1;
 bLeftDown = mouseState.isButtonDown(0);
 bRightDown = mouseState.isButtonDown(1);
 bMiddleDown = mouseState.isButtonDown(2);
 wheelDelta = mouseState.getDWheel();
 mouseState.resetDWheel();
 if (m_buttonDownStates.empty()) {
 m_buttonDownStates = new boolean[mouseState.getButtonCount()];
 }

 for (int int2 = 0; int2 < m_buttonDownStates.length; int2++) {
 m_buttonDownStates[int2] = mouseState.isButtonDown(int2);
 }

 if (int0 != x || int1 != y || wheelDelta != 0 ||
 bLeftWasDown != bLeftDown || bRightWasDown != bRightDown ||
 bMiddleWasDown != bMiddleDown) {
 lastActivity = System.currentTimeMillis();
 }

 s_mouseStateCache.swap();
 }
 }

 static void poll() { s_mouseStateCache.poll(); }

public
 static void setXY(int _x, int _y) {
 s_mouseStateCache.getState().setCursorPosition(
 _x, Core.getInstance().getOffscreenHeight(0) - 1 - _y);
 }

 static Cursor loadCursor(const std::string &filename) {
 File file = ZomboidFileSystem.instance.getMediaFile("ui/" + filename);
 BufferedImage bufferedImage = nullptr;

 try {
 bufferedImage = ImageIO.read(file);
 int int0 = bufferedImage.getWidth();
 int int1 = bufferedImage.getHeight();
 int[] ints = new int[int0 * int1];

 for (int int2 = 0; int2 < ints.length; int2++) {
 int int3 = int2 % int0;
 int int4 = int1 - 1 - int2 / int0;
 ints[int2] = bufferedImage.getRGB(int3, int4);
 }

 IntBuffer intBuffer = BufferUtils.createIntBuffer(int0 * int1);
 intBuffer.put(ints);
 intBuffer.rewind();
 uint8_t byte0 = 1;
 uint8_t byte1 = 1;
 return new Cursor(int0, int1, byte0, byte1, 1, intBuffer, nullptr);
 } catch (Exception exception) {
 return nullptr;
 }
 }

 static void initCustomCursor() {
 if (blankCursor.empty()) {
 try {
 blankCursor = loadCursor("cursor_blank.png");
 defaultCursor = loadCursor("cursor_white.png");
 } catch (LWJGLException lWJGLException0) {
 lWJGLException0.printStackTrace();
 }
 }

 if (defaultCursor != nullptr) {
 try {
 org.lwjglx.input.Mouse.setNativeCursor(defaultCursor);
 } catch (LWJGLException lWJGLException1) {
 lWJGLException1.printStackTrace();
 }
 }
 }

 static void setCursorVisible(bool bVisible) { isCursorVisible = bVisible; }

 static bool isCursorVisible() { return isCursorVisible; }

 static void renderCursorTexture() {
 if (isCursorVisible()) {
 if (mouseCursorTexture.empty()) {
 mouseCursorTexture =
 Texture.getSharedTexture("media/ui/cursor_white.png");
 }

 if (mouseCursorTexture != nullptr && mouseCursorTexture.isReady()) {
 int int0 = getXA();
 int int1 = getYA();
 uint8_t byte0 = 1;
 uint8_t byte1 = 1;
 SpriteRenderer.instance.render(
 mouseCursorTexture, int0 - byte0, int1 - byte1,
 mouseCursorTexture.getWidth(), mouseCursorTexture.getHeight(), 1.0F,
 1.0F, 1.0F, 1.0F, nullptr);
 }
 }
 }
}
} // namespace input
} // namespace zombie
