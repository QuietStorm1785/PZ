#pragma once
#include "org/lwjglx/opengl/OpenGLException.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugLogStream.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include "zombie/ui/UITransition.h"
#include "zombie/util/Type.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace logger {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ExceptionLogger {
public:
 static int exceptionCount;
 static bool bIgnore;
 static bool bExceptionPopup = true;
 static long popupFrameMS = 0L;
 static UITransition transition = new UITransition();
 static bool bHide;

public
 static void logException(Throwable throwable) {
 logException(throwable, nullptr);
 }

public
 static void logException(Throwable throwable, String string) {
 logException(throwable, string, DebugLog.General, LogSeverity.Error);
 }

public
 static void logException(Throwable throwable0, String string,
 DebugLogStream debugLogStream,
 LogSeverity logSeverity) {
 OpenGLException openGLException =
 Type.tryCastTo(throwable0, OpenGLException.class);
 if (openGLException != nullptr) {
 RenderThread.logGLException(openGLException, false);
 }

 debugLogStream.printException(
 throwable0, string, DebugLogStream.generateCallerPrefix(), logSeverity);

 try {
 if (bIgnore) {
 return;
 }

 bIgnore = true;
 exceptionCount++;
 if (!GameServer.bServer) {
 if (bExceptionPopup) {
 showPopup();
 }

 return;
 }
 } catch (Throwable throwable1) {
 debugLogStream.printException(
 throwable1, "Exception thrown while trying to logException.",
 LogSeverity.Error);
 return;
 } finally {
 bIgnore = false;
 }
 }

 static void showPopup() {
 float float0 = popupFrameMS > 0L ? transition.getElapsed() : 0.0F;
 popupFrameMS = 3000L;
 transition.setIgnoreUpdateTime(true);
 transition.init(500.0F, false);
 transition.setElapsed(float0);
 bHide = false;
 }

 static void render() {
 if (!UIManager.useUIFBO || Core.getInstance().UIRenderThisFrame) {
 bool boolean0 = false;
 if (boolean0) {
 popupFrameMS = 3000L;
 }

 if (popupFrameMS > 0L) {
 popupFrameMS =
 (long)(popupFrameMS - UIManager.getMillisSinceLastRender());
 transition.update();
 int int0 = TextManager.instance.getFontHeight(UIFont.DebugConsole);
 uint8_t byte0 = 100;
 int int1 = int0 * 2 + 4;
 int int2 = Core.getInstance().getScreenWidth() - byte0;
 int int3 = Core.getInstance().getScreenHeight() -
 (int)(int1 * transition.fraction());
 if (boolean0) {
 int3 = Core.getInstance().getScreenHeight() - int1;
 }

 SpriteRenderer.instance.renderi(nullptr, int2, int3, byte0, int1, 0.8F,
 0.0F, 0.0F, 1.0F, nullptr);
 SpriteRenderer.instance.renderi(nullptr, int2 + 1, int3 + 1, byte0 - 2,
 int0 - 1, 0.0F, 0.0F, 0.0F, 1.0F,
 nullptr);
 TextManager.instance.DrawStringCentre(UIFont.DebugConsole,
 int2 + byte0 / 2, int3, "ERROR",
 1.0, 0.0, 0.0, 1.0);
 TextManager.instance.DrawStringCentre(
 UIFont.DebugConsole, int2 + byte0 / 2, int3 + int0,
 boolean0 ? "999" : Integer.toString(exceptionCount), 0.0, 0.0, 0.0,
 1.0);
 if (popupFrameMS <= 0L && !bHide) {
 popupFrameMS = 500L;
 transition.init(500.0F, true);
 bHide = true;
 }
 }
 }
 }
}
} // namespace logger
} // namespace core
} // namespace zombie
