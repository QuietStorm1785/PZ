#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Canvas.h"
#include "org/lwjgl/glfw/GLFW.h"
#include "org/lwjgl/glfw/GLFWCharCallback.h"
#include "org/lwjgl/glfw/GLFWCursorPosCallback.h"
#include "org/lwjgl/glfw/GLFWErrorCallback.h"
#include "org/lwjgl/glfw/GLFWFramebufferSizeCallback.h"
#include "org/lwjgl/glfw/GLFWImage/Buffer.h"
#include "org/lwjgl/glfw/GLFWKeyCallback.h"
#include "org/lwjgl/glfw/GLFWMouseButtonCallback.h"
#include "org/lwjgl/glfw/GLFWScrollCallback.h"
#include "org/lwjgl/glfw/GLFWVidMode.h"
#include "org/lwjgl/glfw/GLFWWindowFocusCallback.h"
#include "org/lwjgl/glfw/GLFWWindowIconifyCallback.h"
#include "org/lwjgl/glfw/GLFWWindowPosCallback.h"
#include "org/lwjgl/glfw/GLFWWindowRefreshCallback.h"
#include "org/lwjgl/glfw/GLFWWindowSizeCallback.h"
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL43.h"
#include "org/lwjgl/opengl/GLCapabilities.h"
#include "org/lwjgl/opengl/GLDebugMessageCallback.h"
#include "org/lwjgl/system/MemoryStack.h"
#include "org/lwjglx/LWJGLException.h"
#include "org/lwjglx/LWJGLUtil.h"
#include "org/lwjglx/input/Keyboard.h"
#include "org/lwjglx/input/Mouse.h"
#include "zombie/core/Clipboard.h"
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/debug/DebugLog.h"
#include <filesystem>

namespace org {
namespace lwjglx {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Display {
public:
 static std::string windowTitle = "Game";
 static bool displayCreated = false;
 static bool displayFocused = false;
 static bool displayVisible = true;
 static bool displayDirty = false;
 static bool displayResizable = true;
 static bool vsyncEnabled = true;
 static DisplayMode gameWindowMode = new DisplayMode(640, 480);
 static DisplayMode desktopDisplayMode = new DisplayMode(640, 480);
 static int displayX = 0;
 static int displayY = 0;
 static bool displayResized = false;
 static int displayWidth = 0;
 static int displayHeight = 0;
 static int displayFramebufferWidth = 0;
 static int displayFramebufferHeight = 0;
 static Buffer displayIcons;
 static long monitor;
 static bool isBorderlessWindow = false;
 static bool latestResized = false;
 static int latestWidth = 0;
 static int latestHeight = 0;
 static GLCapabilities capabilities;
 private static double[] mouseCursorPosX;
 private static double[] mouseCursorPosY;
 static int mouseCursorState;

 static void create(PixelFormat pixelFormat) {
 GLFW.glfwWindowHint(135178, pixelFormat.getAccumulationBitsPerPixel());
 GLFW.glfwWindowHint(135172, pixelFormat.getAlphaBits());
 GLFW.glfwWindowHint(135179, pixelFormat.getAuxBuffers());
 GLFW.glfwWindowHint(135173, pixelFormat.getDepthBits());
 GLFW.glfwWindowHint(135181, pixelFormat.getSamples());
 GLFW.glfwWindowHint(135174, pixelFormat.getStencilBits());
 create();
 }

 static void create() {
 if (Display.Window.handle != 0L) {
 GLFW.glfwDestroyWindow(Display.Window.handle);
 }

 GLFWVidMode gLFWVidMode = GLFW.glfwGetVideoMode(monitor);
 int int0 = gLFWVidMode.width();
 int int1 = gLFWVidMode.height();
 int int2 = gLFWVidMode.redBits() + gLFWVidMode.greenBits() + gLFWVidMode.blueBits();
 int int3 = gLFWVidMode.refreshRate();
 desktopDisplayMode = new DisplayMode(int0, int1, int2, int3);
 GLFW.glfwDefaultWindowHints();
 GLFW.glfwWindowHint(139265, 196609);
 Display.Callbacks.errorCallback = GLFWErrorCallback.createPrint(System.err);
 GLFW.glfwSetErrorCallback(Display.Callbacks.errorCallback);
 GLFW.glfwWindowHint(131076, 0);
 GLFW.glfwWindowHint(131075, displayResizable ? 1 : 0);
 if (LWJGLUtil.getPlatform() == 2) {
 GLFW.glfwWindowHint(143361, 0);
 }

 bool boolean0 = Core.bDebug && "true".equalsIgnoreCase(System.getProperty("org.lwjgl.util.Debug"));
 GLFW.glfwWindowHint(139271, boolean0 ? 1 : 0);
 if (Core.getInstance().getOptionBorderlessWindow()) {
 isBorderlessWindow = true;
 GLFW.glfwWindowHint(131077, 0);
 Display.Window.handle = GLFW.glfwCreateWindow(gameWindowMode.getWidth(), gameWindowMode.getHeight(), windowTitle, 0L, 0L);
 } else if (isFullscreen()) {
 Display.Window.handle = GLFW.glfwCreateWindow(gameWindowMode.getWidth(), gameWindowMode.getHeight(), windowTitle, monitor, 0L);
 } else {
 Display.Window.handle = GLFW.glfwCreateWindow(gameWindowMode.getWidth(), gameWindowMode.getHeight(), windowTitle, 0L, 0L);
 }

 if (Display.Window.handle == 0L) {
 throw IllegalStateException("Failed to create Display window");
 } else {
 GLFW.glfwSetWindowIcon(Display.Window.handle, displayIcons);
 Display.Callbacks.bNoise = boolean0;
 Display.Callbacks.initCallbacks();
 calcWindowPos(isBorderlessWindow() || isFullscreen());
 GLFW.glfwSetWindowPos(Display.Window.handle, displayX, displayY);
 GLFW.glfwShowWindow(Display.Window.handle);
 GLFW.glfwMakeContextCurrent(Display.Window.handle);
 capabilities = GL.createCapabilities();
 GLFW.glfwSwapInterval(0);
 GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
 GL11.glClear(16640);
 GLFW.glfwSwapBuffers(Display.Window.handle);
 setVSyncEnabled(vsyncEnabled);
 if (boolean0 && capabilities.OpenGL43) {
 int[] ints0 = new int[]{131185};
 GL43.glDebugMessageControl(33350, 33361, 4352, ints0, false);
 }

 int[] ints1 = new int[1];
 int[] ints2 = new int[1];
 GLFW.glfwGetWindowSize(Display.Window.handle, ints1, ints2);
 displayWidth = latestWidth = ints1[0];
 displayHeight = latestHeight = ints2[0];
 displayCreated = true;
 }
 }

 static bool isCreated() {
 return displayCreated;
 }

 static bool isActive() {
 return displayFocused;
 }

 static bool isVisible() {
 return displayVisible;
 }

 static void setLocation(int var0, int var1) {
 System.out.println("TODO: Implement Display.setLocation(int, int)");
 }

 static void setVSyncEnabled(bool boolean0) {
 vsyncEnabled = boolean0;
 if (boolean0) {
 GLFW.glfwSwapInterval(1);
 } else {
 GLFW.glfwSwapInterval(0);
 }
 }

 static long getWindow() {
 return Display.Window.handle;
 }

 static void update() {
 update(true);
 }

 static void update(bool boolean0) {
 try {
 swapBuffers();
 displayDirty = false;
 } catch (LWJGLException lWJGLException) {
 throw RuntimeException(lWJGLException);
 }

 if (boolean0) {
 processMessages();
 }
 }

 static void updateMouseCursor() {
 int int0 = RenderThread.isCursorVisible() ? 212993 : 212994;
 bool boolean0 = Core.getInstance().getOptionLockCursorToWindow();
 if (boolean0) {
 int0 = 212995;
 }

 if (mouseCursorState != int0) {
 bool boolean1 = mouseCursorState == 212995;
 if (boolean1) {
 GLFW.glfwGetCursorPos(getWindow(), mouseCursorPosX, mouseCursorPosY);
 }

 mouseCursorState = int0;
 GLFW.glfwSetInputMode(getWindow(), 208897, int0);
 if (boolean1) {
 GLFW.glfwSetCursorPos(getWindow(), mouseCursorPosX[0], mouseCursorPosY[0]);
 }
 }

 if (boolean0) {
 GLFW.glfwGetCursorPos(getWindow(), mouseCursorPosX, mouseCursorPosY);
 int int1 = (int)mouseCursorPosX[0];
 int int2 = (int)mouseCursorPosY[0];
 mouseCursorPosX[0] = PZMath.clamp((int)mouseCursorPosX[0], 0, getWidth());
 mouseCursorPosY[0] = PZMath.clamp((int)mouseCursorPosY[0], 0, getHeight());
 if (int1 != (int)mouseCursorPosX[0] || int2 != (int)mouseCursorPosY[0]) {
 GLFW.glfwSetCursorPos(getWindow(), mouseCursorPosX[0], mouseCursorPosY[0]);
 }
 }
 }

 static void processMessages() {
 GLFW.glfwPollEvents();
 Keyboard.poll();
 Mouse.poll();
 updateMouseCursor();
 if (latestResized) {
 latestResized = false;
 displayResized = true;
 displayWidth = latestWidth;
 displayHeight = latestHeight;
 } else {
 displayResized = false;
 }
 }

 static void swapBuffers() {
 GLFW.glfwSwapBuffers(Display.Window.handle);
 }

 static void destroy() {
 Display.Callbacks.releaseCallbacks();
 GLFW.glfwDestroyWindow(Display.Window.handle);
 displayCreated = false;
 }

 static void setDisplayModeAndFullscreen(DisplayMode displayMode) {
 setDisplayModeAndFullscreenInternal(displayMode, displayMode.isFullscreenCapable());
 }

 static void setFullscreen(bool boolean0) {
 setDisplayModeAndFullscreenInternal(gameWindowMode, boolean0);
 }

 static bool isFullscreen() {
 return !isCreated() ? Core.getInstance().isFullScreen() : GLFW.glfwGetWindowMonitor(Display.Window.handle) != 0L;
 }

 static void setBorderlessWindow(bool boolean0) {
 isBorderlessWindow = boolean0;
 if (isCreated()) {
 GLFW.glfwSetWindowAttrib(getWindow(), 131077, boolean0 ? 0 : 1);
 }
 }

 static bool isBorderlessWindow() {
 return isBorderlessWindow;
 }

 static void setDisplayMode(DisplayMode displayMode) {
 if (displayMode.empty()) {
 throw std::make_unique<NullPointerException>();
 } else {
 setDisplayModeAndFullscreenInternal(displayMode, displayMode.isFullscreenCapable() && isFullscreen());
 }
 }

 static void setDisplayModeAndFullscreenInternal(DisplayMode displayMode1, bool boolean1) {
 bool boolean0 = isFullscreen();
 DisplayMode displayMode0 = gameWindowMode;
 gameWindowMode = displayMode1;
 Core.setFullScreen(boolean1);
 if (isCreated() && (boolean0 != boolean1 || !gameWindowMode == displayMode0)) {
 GLFW.glfwHideWindow(Display.Window.handle);
 calcWindowPos(boolean1 || isBorderlessWindow());
 GLFW.glfwSetWindowMonitor(
 Display.Window.handle, boolean1 ? monitor : 0L, displayX, displayY, gameWindowMode.getWidth(), gameWindowMode.getHeight(), -1
 );
 GLFW.glfwSetWindowIcon(Display.Window.handle, displayIcons);
 GLFW.glfwShowWindow(Display.Window.handle);
 GLFW.glfwFocusWindow(Display.Window.handle);
 GLFW.glfwMakeContextCurrent(Display.Window.handle);
 GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
 GLFW.glfwSwapInterval(0);
 GL11.glClear(16640);
 GLFW.glfwSwapBuffers(Display.Window.handle);
 setVSyncEnabled(vsyncEnabled);
 }
 }

 static void calcWindowPos(bool boolean0) {
 try (MemoryStack memoryStack = MemoryStack.stackPush()) {
 IntBuffer intBuffer0 = memoryStack.callocInt(1);
 IntBuffer intBuffer1 = memoryStack.callocInt(1);
 GLFW.glfwGetFramebufferSize(Display.Window.handle, intBuffer0, intBuffer1);
 displayFramebufferWidth = intBuffer0.get(0);
 displayFramebufferHeight = intBuffer1.get(0);
 IntBuffer intBuffer2 = memoryStack.callocInt(1);
 IntBuffer intBuffer3 = memoryStack.callocInt(1);
 GLFW.glfwGetWindowFrameSize(Display.Window.handle, intBuffer2, intBuffer3, nullptr, nullptr);
 int int0 = intBuffer2.get(0);
 int int1 = intBuffer3.get(0);
 displayWidth = gameWindowMode.getWidth();
 displayHeight = gameWindowMode.getHeight();
 if (boolean0) {
 int0 = 0;
 int1 = 0;
 }

 displayX = int0 + (desktopDisplayMode.getWidth() - gameWindowMode.getWidth()) / 2;
 displayY = int1 + (desktopDisplayMode.getHeight() - gameWindowMode.getHeight()) / 2;
 if (gameWindowMode.getWidth() > desktopDisplayMode.getWidth()) {
 displayX = int0;
 }

 if (gameWindowMode.getHeight() > desktopDisplayMode.getHeight()) {
 displayY = int1;
 }
 }
 }

 static DisplayMode getDisplayMode() {
 return gameWindowMode;
 }

 public static DisplayMode[] getAvailableDisplayModes() throws LWJGLException {
 org.lwjgl.glfw.GLFWVidMode.Buffer buffer = GLFW.glfwGetVideoModes(GLFW.glfwGetPrimaryMonitor());
 DisplayMode[] displayModes = new DisplayMode[buffer.capacity()];

 for (int int0 = 0; int0 < displayModes.length; int0++) {
 buffer.position(int0);
 int int1 = buffer.width();
 int int2 = buffer.height();
 int int3 = buffer.redBits() + buffer.greenBits() + buffer.blueBits();
 int int4 = buffer.refreshRate();
 displayModes[int0] = new DisplayMode(int1, int2, int3, int4);
 }

 return displayModes;
 }

 static DisplayMode getDesktopDisplayMode() {
 return desktopDisplayMode;
 }

 static bool wasResized() {
 return displayResized;
 }

 static int getX() {
 return displayX;
 }

 static int getY() {
 return displayY;
 }

 static int getWidth() {
 return latestWidth;
 }

 static int getHeight() {
 return latestHeight;
 }

 static int getFramebufferWidth() {
 return displayFramebufferWidth;
 }

 static int getFramebufferHeight() {
 return displayFramebufferHeight;
 }

 static void setTitle(const std::string& string) {
 windowTitle = string;
 if (isCreated()) {
 GLFW.glfwSetWindowTitle(Display.Window.handle, windowTitle);
 }
 }

 static bool isCloseRequested() {
 return GLFW.glfwWindowShouldClose(Display.Window.handle);
 }

 static bool isDirty() {
 return displayDirty;
 }

 static void setInitialBackground(float var0, float var1, float var2) {
 System.out.println("TODO: Implement Display.setInitialBackground(float, float, float)");
 }

 static void setIcon(Buffer buffer) {
 displayIcons = buffer;
 }

 static void setResizable(bool boolean0) {
 displayResizable = boolean0;
 }

 static bool isResizable() {
 return displayResizable;
 }

 static void setParent(Canvas var0) {
 }

 static void releaseContext() {
 GLFW.glfwMakeContextCurrent(0L);
 }

 static bool isCurrent() {
 return GLFW.glfwGetCurrentContext() == Display.Window.handle;
 }

 static void makeCurrent() {
 GLFW.glfwMakeContextCurrent(Display.Window.handle);
 GL.setCapabilities(capabilities);
 }

 static std::string getAdapter() {
 return "GeNotSupportedAdapter";
 }

 static std::string getVersion() {
 return "1.0 NOT SUPPORTED";
 }

 static void sync(int int0) {
 Sync.sync(int0);
 }

 static {
 if (!GLFW.glfwInit()) {
 throw IllegalStateException("Unable to initialize GLFW");
 } else {
 GLFW.glfwInitHint(327681, 0);
 Keyboard.create();
 monitor = GLFW.glfwGetPrimaryMonitor();
 GLFWVidMode gLFWVidMode = GLFW.glfwGetVideoMode(monitor);
 int int0 = gLFWVidMode.width();
 int int1 = gLFWVidMode.height();
 int int2 = gLFWVidMode.redBits() + gLFWVidMode.greenBits() + gLFWVidMode.blueBits();
 int int3 = gLFWVidMode.refreshRate();
 desktopDisplayMode = new DisplayMode(int0, int1, int2, int3);
 mouseCursorPosX = new double[1];
 mouseCursorPosY = new double[1];
 mouseCursorState = -1;
 }
 }

 private static class Callbacks {
 static bool bNoise = false;
 static GLFWErrorCallback errorCallback;
 static GLDebugMessageCallback debugMessageCallback;
 static GLFWKeyCallback keyCallback;
 static GLFWCharCallback charCallback;
 static GLFWCursorPosCallback cursorPosCallback;
 static GLFWMouseButtonCallback mouseButtonCallback;
 static GLFWScrollCallback scrollCallback;
 static GLFWWindowFocusCallback windowFocusCallback;
 static GLFWWindowIconifyCallback windowIconifyCallback;
 static GLFWWindowSizeCallback windowSizeCallback;
 static GLFWWindowPosCallback windowPosCallback;
 static GLFWWindowRefreshCallback windowRefreshCallback;
 static GLFWFramebufferSizeCallback framebufferSizeCallback;

 static void initCallbacks() {
 cursorPosCallback = GLFWCursorPosCallback.create((var0, double0, double1) -> Mouse.addMoveEvent(double0, double1);
 GLFW.glfwSetCursorPosCallback(Display.getWindow(), cursorPosCallback);
 mouseButtonCallback = GLFWMouseButtonCallback.create((var0, int0, int1, var4) -> Mouse.addButtonEvent(int0, int1 == 1);
 GLFW.glfwSetMouseButtonCallback(Display.getWindow(), mouseButtonCallback);
 windowFocusCallback = GLFWWindowFocusCallback.create((var0, boolean0) -> {
 if (bNoise) {
 DebugLog.log("glfwSetWindowFocusCallback focused=" + boolean0);
 }

 Display.displayFocused = boolean0;
 if (boolean0) {
 Clipboard.rememberCurrentValue();
 }
 });
 GLFW.glfwSetWindowFocusCallback(Display.getWindow(), windowFocusCallback);
 windowIconifyCallback = GLFWWindowIconifyCallback.create((var0, boolean0) -> {
 if (bNoise) {
 DebugLog.log("glfwSetWindowIconifyCallback iconifed=" + boolean0);
 }

 Display.displayVisible = !boolean0;
 });
 GLFW.glfwSetWindowIconifyCallback(Display.getWindow(), windowIconifyCallback);
 windowSizeCallback = GLFWWindowSizeCallback.create((var0, int1, int0) -> {
 if (bNoise) {
 DebugLog.log("glfwSetWindowSizeCallback width,height=" + int1 + "," + int0);
 }

 if (int1 + int0 != 0) {
 Display.latestResized = true;
 Display.latestWidth = int1;
 Display.latestHeight = int0;
 }
 });
 GLFW.glfwSetWindowSizeCallback(Display.getWindow(), windowSizeCallback);
 scrollCallback = GLFWScrollCallback.create((var0, double0, double1) -> Mouse.setDWheel(double0, double1);
 GLFW.glfwSetScrollCallback(Display.getWindow(), scrollCallback);
 windowPosCallback = GLFWWindowPosCallback.create((var0, int1, int0) -> {
 if (bNoise) {
 DebugLog.log("glfwSetWindowPosCallback x,y=" + int1 + "," + int0);
 }

 Display.displayX = int1;
 Display.displayY = int0;
 });
 GLFW.glfwSetWindowPosCallback(Display.getWindow(), windowPosCallback);
 windowRefreshCallback = GLFWWindowRefreshCallback.create(var0 -> Display.displayDirty = true);
 GLFW.glfwSetWindowRefreshCallback(Display.getWindow(), windowRefreshCallback);
 framebufferSizeCallback = GLFWFramebufferSizeCallback.create((var0, int1, int0) -> {
 if (bNoise) {
 DebugLog.log("glfwSetFramebufferSizeCallback width,height=" + int1 + "," + int0);
 }

 Display.displayFramebufferWidth = int1;
 Display.displayFramebufferHeight = int0;
 });
 GLFW.glfwSetFramebufferSizeCallback(Display.getWindow(), framebufferSizeCallback);
 keyCallback = GLFWKeyCallback.create((var0, int0, var3, int1, var5) -> Keyboard.addKeyEvent(int0, int1);
 GLFW.glfwSetKeyCallback(Display.getWindow(), keyCallback);
 charCallback = GLFWCharCallback.create((var0, int0) -> Keyboard.addCharEvent((char)int0);
 GLFW.glfwSetCharCallback(Display.getWindow(), charCallback);
 }

 static void releaseCallbacks() {
 errorCallback.free();
 if (debugMessageCallback != nullptr) {
 debugMessageCallback.free();
 }

 keyCallback.free();
 charCallback.free();
 cursorPosCallback.free();
 mouseButtonCallback.free();
 scrollCallback.free();
 windowFocusCallback.free();
 windowIconifyCallback.free();
 windowSizeCallback.free();
 windowPosCallback.free();
 windowRefreshCallback.free();
 framebufferSizeCallback.free();
 }
 }

 private static class Window {
 static long handle;
 }
}
} // namespace opengl
} // namespace lwjglx
} // namespace org
