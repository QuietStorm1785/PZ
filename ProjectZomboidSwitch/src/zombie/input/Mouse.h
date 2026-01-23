#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/image/BufferedImage.h"
#include "javax/imageio/ImageIO.h"
#include "org/lwjgl/BufferUtils.h"
#include "GraphicsWrapper/GraphicsExceptions.h"
#include "org/lwjglx/input/Cursor.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace input {


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
   public static boolean[] m_buttonDownStates;
    static long lastActivity;
    static int wheelDelta;
    static const MouseStateCache s_mouseStateCache = std::make_shared<MouseStateCache>();
   public static boolean[] UICaptured = new boolean[10];
    static Cursor blankCursor;
    static Cursor defaultCursor;
    static bool isCursorVisible = true;
    static Texture mouseCursorTexture = nullptr;

    static int getWheelState() {
    return wheelDelta;
   }

   public static /* synchronized - TODO: add std::mutex */ int getXA() {
    return x;
   }

   public static /* synchronized - TODO: add std::mutex */ int getYA() {
    return y;
   }

   public static /* synchronized - TODO: add std::mutex */ int getX() {
      return (int)(x * Core.getInstance().getZoom(0));
   }

   public static /* synchronized - TODO: add std::mutex */ int getY() {
      return (int)(y * Core.getInstance().getZoom(0));
   }

    static bool isButtonDown(int var0) {
      return m_buttonDownStates != nullptr ? m_buttonDownStates[var0] : false;
   }

    static void UIBlockButtonDown(int var0) {
      UICaptured[var0] = true;
   }

    static bool isButtonDownUICheck(int var0) {
      if (m_buttonDownStates != nullptr) {
    bool var1 = m_buttonDownStates[var0];
         if (!var1) {
            UICaptured[var0] = false;
         } else if (UICaptured[var0]) {
    return false;
         }

    return var1;
      } else {
    return false;
      }
   }

    static bool isLeftDown() {
    return bLeftDown;
   }

    static bool isLeftPressed() {
      return !bLeftWasDown && bLeftDown;
   }

    static bool isLeftReleased() {
      return bLeftWasDown && !bLeftDown;
   }

    static bool isLeftUp() {
      return !bLeftDown;
   }

    static bool isMiddleDown() {
    return bMiddleDown;
   }

    static bool isMiddlePressed() {
      return !bMiddleWasDown && bMiddleDown;
   }

    static bool isMiddleReleased() {
      return bMiddleWasDown && !bMiddleDown;
   }

    static bool isMiddleUp() {
      return !bMiddleDown;
   }

    static bool isRightDown() {
    return bRightDown;
   }

    static bool isRightPressed() {
      return !bRightWasDown && bRightDown;
   }

    static bool isRightReleased() {
      return bRightWasDown && !bRightDown;
   }

    static bool isRightUp() {
      return !bRightDown;
   }

   public static /* synchronized - TODO: add std::mutex */ void update() {
    MouseState var0 = s_mouseStateCache.getState();
      if (!var0.isCreated()) {
         s_mouseStateCache.swap();

         try {
            org.lwjglx.input.Mouse.create();
         } catch (LWJGLException var4) {
            var4.printStackTrace();
         }
      } else {
         bLeftWasDown = bLeftDown;
         bRightWasDown = bRightDown;
         bMiddleWasDown = bMiddleDown;
    int var1 = x;
    int var2 = y;
         x = var0.getX();
         y = Core.getInstance().getScreenHeight() - var0.getY() - 1;
         bLeftDown = var0.isButtonDown(0);
         bRightDown = var0.isButtonDown(1);
         bMiddleDown = var0.isButtonDown(2);
         wheelDelta = var0.getDWheel();
         var0.resetDWheel();
         if (m_buttonDownStates == nullptr) {
            m_buttonDownStates = new boolean[var0.getButtonCount()];
         }

         for (int var3 = 0; var3 < m_buttonDownStates.length; var3++) {
            m_buttonDownStates[var3] = var0.isButtonDown(var3);
         }

         if (var1 != x || var2 != y || wheelDelta != 0 || bLeftWasDown != bLeftDown || bRightWasDown != bRightDown || bMiddleWasDown != bMiddleDown) {
            lastActivity = System.currentTimeMillis();
         }

         s_mouseStateCache.swap();
      }
   }

    static void poll() {
      s_mouseStateCache.poll();
   }

   public static /* synchronized - TODO: add std::mutex */ void setXY(int var0, int var1) {
      s_mouseStateCache.getState().setCursorPosition(var0, Core.getInstance().getOffscreenHeight(0) - 1 - var1);
   }

    static Cursor loadCursor(const std::string& var0) {
    File var1 = ZomboidFileSystem.instance.getMediaFile("ui/" + var0);
    BufferedImage var2 = nullptr;

      try {
         var2 = ImageIO.read(var1);
    int var3 = var2.getWidth();
    int var4 = var2.getHeight();
         int[] var5 = new int[var3 * var4];

         for (int var6 = 0; var6 < var5.length; var6++) {
    int var7 = var6 % var3;
    int var8 = var4 - 1 - var6 / var3;
            var5[var6] = var2.getRGB(var7, var8);
         }

    IntBuffer var12 = BufferUtils.createIntBuffer(var3 * var4);
         var12.put(var5);
         var12.rewind();
    uint8_t var13 = 1;
    uint8_t var14 = 1;
         return std::make_shared<Cursor>(var3, var4, var13, var14, 1, var12, nullptr);
      } catch (Exception var10) {
    return nullptr;
      }
   }

    static void initCustomCursor() {
      if (blankCursor == nullptr) {
         try {
            blankCursor = loadCursor("cursor_blank.png");
            defaultCursor = loadCursor("cursor_white.png");
         } catch (LWJGLException var2) {
            var2.printStackTrace();
         }
      }

      if (defaultCursor != nullptr) {
         try {
            org.lwjglx.input.Mouse.setNativeCursor(defaultCursor);
         } catch (LWJGLException var1) {
            var1.printStackTrace();
         }
      }
   }

    static void setCursorVisible(bool var0) {
      isCursorVisible = var0;
   }

    static bool isCursorVisible() {
    return isCursorVisible;
   }

    static void renderCursorTexture() {
      if (isCursorVisible()) {
         if (mouseCursorTexture == nullptr) {
            mouseCursorTexture = Texture.getSharedTexture("media/ui/cursor_white.png");
         }

         if (mouseCursorTexture != nullptr && mouseCursorTexture.isReady()) {
    int var0 = getXA();
    int var1 = getYA();
    uint8_t var2 = 1;
    uint8_t var3 = 1;
            SpriteRenderer.instance
               .render(
                  mouseCursorTexture, var0 - var2, var1 - var3, mouseCursorTexture.getWidth(), mouseCursorTexture.getHeight(), 1.0F, 1.0F, 1.0F, 1.0F, nullptr
               );
         }
      }
   }
}
} // namespace input
} // namespace zombie
