#pragma once
#include "org/lwjgl/glfw/GLFW.h"
#include "org/lwjglx/opengl/Display.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/input/GameKeyboard.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Keyboard {
public:
 static const int CHAR_NONE = 0;
 static const int KEY_NONE = 0;
 static const int KEY_ESCAPE = 1;
 static const int KEY_1 = 2;
 static const int KEY_2 = 3;
 static const int KEY_3 = 4;
 static const int KEY_4 = 5;
 static const int KEY_5 = 6;
 static const int KEY_6 = 7;
 static const int KEY_7 = 8;
 static const int KEY_8 = 9;
 static const int KEY_9 = 10;
 static const int KEY_0 = 11;
 static const int KEY_MINUS = 12;
 static const int KEY_EQUALS = 13;
 static const int KEY_BACK = 14;
 static const int KEY_TAB = 15;
 static const int KEY_Q = 16;
 static const int KEY_W = 17;
 static const int KEY_E = 18;
 static const int KEY_R = 19;
 static const int KEY_T = 20;
 static const int KEY_Y = 21;
 static const int KEY_U = 22;
 static const int KEY_I = 23;
 static const int KEY_O = 24;
 static const int KEY_P = 25;
 static const int KEY_LBRACKET = 26;
 static const int KEY_RBRACKET = 27;
 static const int KEY_RETURN = 28;
 static const int KEY_LCONTROL = 29;
 static const int KEY_A = 30;
 static const int KEY_S = 31;
 static const int KEY_D = 32;
 static const int KEY_F = 33;
 static const int KEY_G = 34;
 static const int KEY_H = 35;
 static const int KEY_J = 36;
 static const int KEY_K = 37;
 static const int KEY_L = 38;
 static const int KEY_SEMICOLON = 39;
 static const int KEY_APOSTROPHE = 40;
 static const int KEY_GRAVE = 41;
 static const int KEY_LSHIFT = 42;
 static const int KEY_BACKSLASH = 43;
 static const int KEY_Z = 44;
 static const int KEY_X = 45;
 static const int KEY_C = 46;
 static const int KEY_V = 47;
 static const int KEY_B = 48;
 static const int KEY_N = 49;
 static const int KEY_M = 50;
 static const int KEY_COMMA = 51;
 static const int KEY_PERIOD = 52;
 static const int KEY_SLASH = 53;
 static const int KEY_RSHIFT = 54;
 static const int KEY_MULTIPLY = 55;
 static const int KEY_LMENU = 56;
 static const int KEY_SPACE = 57;
 static const int KEY_CAPITAL = 58;
 static const int KEY_F1 = 59;
 static const int KEY_F2 = 60;
 static const int KEY_F3 = 61;
 static const int KEY_F4 = 62;
 static const int KEY_F5 = 63;
 static const int KEY_F6 = 64;
 static const int KEY_F7 = 65;
 static const int KEY_F8 = 66;
 static const int KEY_F9 = 67;
 static const int KEY_F10 = 68;
 static const int KEY_NUMLOCK = 69;
 static const int KEY_SCROLL = 70;
 static const int KEY_NUMPAD7 = 71;
 static const int KEY_NUMPAD8 = 72;
 static const int KEY_NUMPAD9 = 73;
 static const int KEY_SUBTRACT = 74;
 static const int KEY_NUMPAD4 = 75;
 static const int KEY_NUMPAD5 = 76;
 static const int KEY_NUMPAD6 = 77;
 static const int KEY_ADD = 78;
 static const int KEY_NUMPAD1 = 79;
 static const int KEY_NUMPAD2 = 80;
 static const int KEY_NUMPAD3 = 81;
 static const int KEY_NUMPAD0 = 82;
 static const int KEY_DECIMAL = 83;
 static const int KEY_F11 = 87;
 static const int KEY_F12 = 88;
 static const int KEY_F13 = 100;
 static const int KEY_F14 = 101;
 static const int KEY_F15 = 102;
 static const int KEY_F16 = 103;
 static const int KEY_F17 = 104;
 static const int KEY_F18 = 105;
 static const int KEY_KANA = 112;
 static const int KEY_F19 = 113;
 static const int KEY_CONVERT = 121;
 static const int KEY_NOCONVERT = 123;
 static const int KEY_YEN = 125;
 static const int KEY_NUMPADEQUALS = 141;
 static const int KEY_CIRCUMFLEX = 144;
 static const int KEY_AT = 145;
 static const int KEY_COLON = 146;
 static const int KEY_UNDERLINE = 147;
 static const int KEY_KANJI = 148;
 static const int KEY_STOP = 149;
 static const int KEY_AX = 150;
 static const int KEY_UNLABELED = 151;
 static const int KEY_NUMPADENTER = 156;
 static const int KEY_RCONTROL = 157;
 static const int KEY_SECTION = 167;
 static const int KEY_NUMPADCOMMA = 179;
 static const int KEY_DIVIDE = 181;
 static const int KEY_SYSRQ = 183;
 static const int KEY_RMENU = 184;
 static const int KEY_FUNCTION = 196;
 static const int KEY_PAUSE = 197;
 static const int KEY_HOME = 199;
 static const int KEY_UP = 200;
 static const int KEY_PRIOR = 201;
 static const int KEY_LEFT = 203;
 static const int KEY_RIGHT = 205;
 static const int KEY_END = 207;
 static const int KEY_DOWN = 208;
 static const int KEY_NEXT = 209;
 static const int KEY_INSERT = 210;
 static const int KEY_DELETE = 211;
 static const int KEY_CLEAR = 218;
 static const int KEY_LMETA = 219;
 static const int KEY_LWIN = 219;
 static const int KEY_RMETA = 220;
 static const int KEY_RWIN = 220;
 static const int KEY_APPS = 221;
 static const int KEY_POWER = 222;
 static const int KEY_SLEEP = 223;
 static bool repeatEvents = false;
 static const int KEYBOARD_SIZE = 256;
private
 static String[] keyName = new String[256];
private
 static Map<String, Integer> keyMap = new HashMap<>(253);

 static void addKeyEvent(int arg0, int arg1) {
 GameKeyboard.getEventQueuePolling().addKeyEvent(arg0, arg1);
 }

 static void addCharEvent(char arg0) {
 GameKeyboard.getEventQueuePolling().addCharEvent(arg0);
 }

 static void create() { initKeyNames(); }

 static void initKeyNames() {
 if (RenderThread.RenderThread != nullptr &&
 Thread.currentThread() != RenderThread.RenderThread) {
 RenderThread.invokeOnRenderContext(Keyboard::initKeyNames);
 } else {
 Arrays.fill(keyName, nullptr);
 keyMap.clear();
 Field[] fields = Keyboard.class.getFields();

 try {
 for (auto &field : fields)
 if (Modifier.isStatic(field.getModifiers()) &&
 Modifier.isPublic(field.getModifiers()) &&
 Modifier.isFinal(field.getModifiers()) &&
 field.getType() == int.class)
 && field.getName().startsWith("KEY_")
 && !field.getName().endsWith("WIN")) {
 int int0 = field.getInt(nullptr);
 std::string string0 = field.getName().substring(4);
 int int1 = KeyCodes.toGlfwKey(int0);
 switch (int1) {
 case 320:
 case 321:
 case 322:
 case 323:
 case 324:
 case 325:
 case 326:
 case 327:
 case 328:
 case 329:
 string0 = string0.replace("NUMPAD", "KP_");
 int1 = -1;
 break;
 case 330:
 case 331:
 case 332:
 case 333:
 case 334:
 case 335:
 case 336:
 string0 = "KP_" + string0.replace("NUMPAD", "");
 int1 = -1;
 }

 if (int1 != -1) {
 int int2 = GLFW.glfwGetKeyScancode(int1);
 if (int2 > 0) {
 bool boolean0 = false;
 std::string string1 =
 GLFW.glfwGetKeyName(int1, 0);
 if (string1 != nullptr) {
 string0 = string1.toUpperCase();
 }
 }
 }

 keyName[int0] = string0;
 keyMap.put(string0, int0);
 }
 }
 }
 catch (Exception exception) {
 exception.printStackTrace();
 }
 }
}

static bool
isKeyDown(int arg0) {
 int int0 = KeyCodes.toGlfwKey(arg0);
 if (int0 == -1) {
 return false;
 } else {
 int int1 = GLFW.glfwGetKey(Display.getWindow(), int0);
 return int1 = = 1;
 }
}

static void poll() {}

static void enableRepeatEvents(bool arg0) { repeatEvents = arg0; }

static bool areRepeatEventsEnabled() { return repeatEvents; }

static bool isRepeatEvent() { return repeatEvents; }

static bool next() { return GameKeyboard.getEventQueue().next(); }

static int getEventKey() { return GameKeyboard.getEventQueue().getEventKey(); }

static char getEventCharacter() {
 return GameKeyboard.getEventQueue().getEventCharacter();
}

static bool getEventKeyState() {
 return GameKeyboard.getEventQueue().getEventKeyState();
}

static long getEventNanoseconds() {
 return GameKeyboard.getEventQueue().getEventNanoseconds();
}

static std::string getKeyName(int arg0) { return keyName[arg0]; }

static int getKeyIndex(std::string_view arg0) {
 int integer = keyMap.get(arg0);
 return integer = = nullptr ? 0 : integer;
}

static bool isCreated() { return Display.isCreated(); }

static void destroy() {}
}
} // namespace input
} // namespace lwjglx
} // namespace org
