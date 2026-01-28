#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "GraphicsWrapper/GraphicsExceptions.h"
#include "org/lwjglx/input/Controllers.h"
#include "org/lwjglx/opengl/Display.h"
#include "org/lwjglx/opengl/OpenGLException.h"
#include "org/lwjglx/opengl/Util.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Clipboard.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/opengl/RenderThread/s_performance.h"
#include "zombie/core/sprite/SpriteRenderState.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/Mouse.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/MPStatisticClient.h"
#include "zombie/ui/FPSGraph.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/lambda/Invokers/Params1/ICallback.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace opengl {


class RenderThread {
public:
    static Thread MainThread;
    static Thread RenderThread;
    static Thread ContextThread = nullptr;
    static bool m_isDisplayCreated = false;
    static int m_contextLockReentrantDepth = 0;
    static const void* m_contextLock = "RenderThread borrowContext Lock";
   private static const std::vector<RenderContextQueueItem> invokeOnRenderQueue = std::make_unique<std::vector<>>();
   private static const std::vector<RenderContextQueueItem> invokeOnRenderQueue_Invoking = std::make_unique<std::vector<>>();
    static bool m_isInitialized = false;
    static const void* m_initLock = "RenderThread Initialization Lock";
   private static volatile boolean m_isCloseRequested = false;
   private static volatile int m_displayWidth;
   private static volatile int m_displayHeight;
   private static volatile boolean m_renderingEnabled = true;
   private static volatile boolean m_waitForRenderState = false;
   private static volatile boolean m_hasContext = false;
    static bool m_cursorVisible = true;

    static void init() {
      /* synchronized - TODO: add std::mutex */ (m_initLock) {
         if (!m_isInitialized) {
            MainThread = Thread.currentThread();
            RenderThread = Thread.currentThread();
            m_displayWidth = Display.getWidth();
            m_displayHeight = Display.getHeight();
            m_isInitialized = true;
         }
      }
   }

    static void initServerGUI() {
      /* synchronized - TODO: add std::mutex */ (m_initLock) {
         if (m_isInitialized) {
            return;
         }

         MainThread = Thread.currentThread();
         RenderThread = std::make_shared<Thread>(ThreadGroups.Main, RenderThread::renderLoop, "RenderThread Main Loop");
         RenderThread.setName("Render Thread");
         RenderThread.setUncaughtExceptionHandler(RenderThread::uncaughtException);
         m_displayWidth = Display.getWidth();
         m_displayHeight = Display.getHeight();
         m_isInitialized = true;
      }

      RenderThread.start();
   }

    static void renderLoop() {
      if (!GameServer.bServer) {
         /* synchronized - TODO: add std::mutex */ (m_initLock) {
            try {
               m_isInitialized = false;
               GameWindow.InitDisplay();
               Controllers.create();
               Clipboard.initMainThread();
            } catch (Exception var12) {
               throw RuntimeException(var12);
            } finally {
               m_isInitialized = true;
            }
         }
      }

      acquireContextReentrant();

      for (boolean var16 = true; var16; Thread.yield()) {
         /* synchronized - TODO: add std::mutex */ (m_contextLock) {
            if (!m_hasContext) {
               acquireContextReentrant();
            }

            m_displayWidth = Display.getWidth();
            m_displayHeight = Display.getHeight();
            if (m_renderingEnabled) {
               s_performance.renderStep.invokeAndMeasure(RenderThread::renderStep);
            } else if (m_isDisplayCreated && m_hasContext) {
               Display.processMessages();
            }

            flushInvokeQueue();
            if (!m_renderingEnabled) {
               m_isCloseRequested = false;
            } else {
               GameWindow.GameInput.poll();
               Mouse.poll();
               GameKeyboard.poll();
               m_isCloseRequested = m_isCloseRequested || Display.isCloseRequested();
            }

            if (!GameServer.bServer) {
               Clipboard.updateMainThread();
            }

            DebugOptions.testThreadCrash(0);
            var16 = !GameWindow.bGameThreadExited;
         }
      }

      releaseContextReentrant();
      /* synchronized - TODO: add std::mutex */ (m_initLock) {
         RenderThread = nullptr;
         m_isInitialized = false;
      }

      shutdown();
      System.exit(0);
   }

    static void uncaughtException(Thread var0, std::exception var1) {
      if (dynamic_cast<ThreadDeath*>(var1) != nullptr) {
         DebugLog.General.println("Render Thread exited: ", var0.getName());
      } else {
         try {
            GameWindow.uncaughtException(var0, var1);
         } finally {
            Runnable var7 = () -> {
    long var0x = 120000L;
    long var2 = 0L;
    long var4 = System.currentTimeMillis();
    long var6 = var4;
               if (!GameWindow.bGameThreadExited) {
                  try {
                     Thread.sleep(1000L);
                  } catch (InterruptedException var11) {
                  }

                  DebugLog.General.error("  Waiting for GameThread to exit...");

                  try {
                     Thread.sleep(2000L);
                  } catch (InterruptedException var10) {
                  }

                  while (!GameWindow.bGameThreadExited) {
                     Thread.yield();
                     var4 = System.currentTimeMillis();
    long var8x = var4 - var6;
                     var2 += var8x;
                     if (var2 >= 120000L) {
                        DebugLog.General.error("  GameThread failed to exit within time limit.");
                        break;
                     }

                     var6 = var4;
                  }
               }

               DebugLog.General.error("  Shutting down...");
               System.exit(1);
            };
    Thread var8 = std::make_shared<Thread>(var7, "ForceCloseThread");
            var8.start();
            DebugLog.General.error("Shutting down sequence starts.");
            m_isCloseRequested = true;
            DebugLog.General.error("  Notifying render state queue...");
            notifyRenderStateQueue();
            DebugLog.General.error("  Notifying InvokeOnRenderQueue...");
            /* synchronized - TODO: add std::mutex */ (invokeOnRenderQueue) {
               invokeOnRenderQueue_Invoking.addAll(invokeOnRenderQueue);
               invokeOnRenderQueue.clear();
            }

            PZArrayUtil.forEach(invokeOnRenderQueue_Invoking, RenderContextQueueItem::notifyWaitingListeners);
         }
      }
   }

    static bool renderStep() {
    bool var0 = false;

      try {
         var0 = lockStepRenderStep();
      } catch (OpenGLException var2) {
         logGLException(var2);
      } catch (Exception var3) {
         DebugLog.General.error("Thrown an " + var3.getClass().getTypeName() + ": " + var3.getMessage());
         var3.printStackTrace();
      }

    return var0;
   }

    static bool lockStepRenderStep() {
    SpriteRenderState var0 = SpriteRenderer.instance.acquireStateForRendering(RenderThread::waitForRenderStateCallback);
      if (var0 != nullptr) {
         m_cursorVisible = var0.bCursorVisible;
         s_performance.spriteRendererPostRender.invokeAndMeasure(() -> SpriteRenderer.instance.postRender());
         s_performance.displayUpdate.invokeAndMeasure(() -> {
            Display.update(true);
            checkControllers();
         });
         if (Core.bDebug && FPSGraph.instance != nullptr) {
            FPSGraph.instance.addRender(System.currentTimeMillis());
         }

         MPStatisticClient.getInstance().fpsProcess();
    return true;
      } else {
         notifyRenderStateQueue();
         if (!m_waitForRenderState || LuaManager.thread != nullptr && LuaManager.thread.bStep) {
            s_performance.displayUpdate.invokeAndMeasure(() -> Display.processMessages());
         }

    return true;
      }
   }

    static void checkControllers() {
   }

    static bool waitForRenderStateCallback() {
      flushInvokeQueue();
    return shouldContinueWaiting();
   }

    static bool shouldContinueWaiting() {
      return !m_isCloseRequested && !GameWindow.bGameThreadExited && (m_waitForRenderState || SpriteRenderer.instance.isWaitingForRenderState());
   }

    static bool isWaitForRenderState() {
    return m_waitForRenderState;
   }

    static void setWaitForRenderState(bool var0) {
      m_waitForRenderState = var0;
   }

    static void flushInvokeQueue() {
      /* synchronized - TODO: add std::mutex */ (invokeOnRenderQueue) {
         invokeOnRenderQueue_Invoking.addAll(invokeOnRenderQueue);
         invokeOnRenderQueue.clear();
      }

      try {
         if (!invokeOnRenderQueue_Invoking.empty()) {
    long var11 = System.nanoTime();

            while (!invokeOnRenderQueue_Invoking.empty()) {
    RenderContextQueueItem var2 = invokeOnRenderQueue_Invoking.remove(0);
    long var3 = System.nanoTime();
               var2.invoke();
    long var5 = System.nanoTime();
               if (var5 - var3 > 1.0E7) {
    bool var7 = true;
               }

               if (var5 - var11 > 1.0E7) {
                  break;
               }
            }

            for (int var12 = invokeOnRenderQueue_Invoking.size() - 1; var12 >= 0; var12--) {
    RenderContextQueueItem var13 = invokeOnRenderQueue_Invoking.get(var12);
               if (var13.isWaiting()) {
                  while (var12 >= 0) {
    RenderContextQueueItem var4 = invokeOnRenderQueue_Invoking.remove(0);
                     var4.invoke();
                     var12--;
                  }
                  break;
               }
            }
         }

         if (TextureID.deleteTextureIDS.position() > 0) {
            TextureID.deleteTextureIDS.flip();
            GL11.glDeleteTextures(TextureID.deleteTextureIDS);
            TextureID.deleteTextureIDS.clear();
         }
      } catch (OpenGLException var9) {
         logGLException(var9);
      } catch (Exception var10) {
         DebugLog.General.error("Thrown an " + var10.getClass().getTypeName() + ": " + var10.getMessage());
         var10.printStackTrace();
      }
   }

    static void logGLException(OpenGLException var0) {
      logGLException(var0, true);
   }

    static void logGLException(OpenGLException var0, bool var1) {
      DebugLog.General.error("OpenGLException thrown: " + var0.getMessage());

      for (int var2 = GL11.glGetError(); var2 != 0; var2 = GL11.glGetError()) {
    std::string var3 = Util.translateGLErrorString(var2);
         DebugLog.General.error("  Also detected error: " + var3 + " ( code:" + var2 + ")");
      }

      if (var1) {
         DebugLog.General.error("std::stack trace:");
         var0.printStackTrace();
      }
   }

    static void Ready() {
      SpriteRenderer.instance.pushFrameDown();
      if (!m_isInitialized) {
         invokeOnRenderContext(RenderThread::renderStep);
      }
   }

    static void acquireContextReentrant() {
      /* synchronized - TODO: add std::mutex */ (m_contextLock) {
         acquireContextReentrantInternal();
      }
   }

    static void releaseContextReentrant() {
      /* synchronized - TODO: add std::mutex */ (m_contextLock) {
         releaseContextReentrantInternal();
      }
   }

    static void acquireContextReentrantInternal() {
    Thread var0 = Thread.currentThread();
      if (ContextThread != nullptr && ContextThread != var0) {
         throw RuntimeException("Context thread mismatch: " + ContextThread + ", " + var0);
      } else {
         m_contextLockReentrantDepth++;
         if (m_contextLockReentrantDepth <= 1) {
            ContextThread = var0;
            m_isDisplayCreated = Display.isCreated();
            if (m_isDisplayCreated) {
               try {
                  m_hasContext = true;
                  Display.makeCurrent();
                  Display.setVSyncEnabled(Core.OptionVSync);
               } catch (LWJGLException var2) {
                  DebugLog.General.error("Exception thrown trying to gain GL context.");
                  var2.printStackTrace();
               }
            }
         }
      }
   }

    static void releaseContextReentrantInternal() {
    Thread var0 = Thread.currentThread();
      if (ContextThread != var0) {
         throw RuntimeException("Context thread mismatch: " + ContextThread + ", " + var0);
      } else if (m_contextLockReentrantDepth == 0) {
         throw RuntimeException("Context thread release overflow: 0: " + ContextThread + ", " + var0);
      } else {
         m_contextLockReentrantDepth--;
         if (m_contextLockReentrantDepth <= 0) {
            if (m_isDisplayCreated && m_hasContext) {
               try {
                  m_hasContext = false;
                  Display.releaseContext();
               } catch (LWJGLException var2) {
                  DebugLog.General.error("Exception thrown trying to release GL context.");
                  var2.printStackTrace();
               }
            }

            ContextThread = nullptr;
         }
      }
   }

    static void invokeOnRenderContext(Runnable var0) {
    RenderContextQueueItem var1 = RenderContextQueueItem.alloc(var0);
      var1.setWaiting();
      queueInvokeOnRenderContext(var1);

      try {
         var1.waitUntilFinished(() -> {
            notifyRenderStateQueue();
            return !m_isCloseRequested && !GameWindow.bGameThreadExited;
         });
      } catch (InterruptedException var3) {
         DebugLog.General.error("Thread Interrupted while waiting for queued item to finish:" + var1);
         notifyRenderStateQueue();
      }

    std::exception var2 = var1.getThrown();
      if (var2 != nullptr) {
         throw RenderContextQueueException(var2);
      }
   }

   public static <T1> void invokeOnRenderContext(T1 var0, ICallback<T1> var1) {
      Lambda.capture(var0, var1, (var0x, var1x, var2) -> invokeOnRenderContext(var0x.invoker(var1x, var2)));
   }

   public static <T1, T2> void invokeOnRenderContext(T1 var0, T2 var1, zombie.util.lambda.Invokers.Params2.ICallback<T1, T2> var2) {
      Lambda.capture(var0, var1, var2, (var0x, var1x, var2x, var3) -> invokeOnRenderContext(var0x.invoker(var1x, var2x, var3)));
   }

   public static <T1, T2, T3> void invokeOnRenderContext(T1 var0, T2 var1, T3 var2, zombie.util.lambda.Invokers.Params3.ICallback<T1, T2, T3> var3) {
      Lambda.capture(var0, var1, var2, var3, (var0x, var1x, var2x, var3x, var4) -> invokeOnRenderContext(var0x.invoker(var1x, var2x, var3x, var4)));
   }

   public static <T1, T2, T3, T4> void invokeOnRenderContext(
      T1 var0, T2 var1, T3 var2, T4 var3, zombie.util.lambda.Invokers.Params4.ICallback<T1, T2, T3, T4> var4
   ) {
      Lambda.capture(
         var0, var1, var2, var3, var4, (var0x, var1x, var2x, var3x, var4x, var5) -> invokeOnRenderContext(var0x.invoker(var1x, var2x, var3x, var4x, var5))
      );
   }

    static void notifyRenderStateQueue() {
      if (SpriteRenderer.instance != nullptr) {
         SpriteRenderer.instance.notifyRenderStateQueue();
      }
   }

    static void queueInvokeOnRenderContext(Runnable var0) {
      queueInvokeOnRenderContext(RenderContextQueueItem.alloc(var0));
   }

    static void queueInvokeOnRenderContext(RenderContextQueueItem var0) {
      if (!m_isInitialized) {
         /* synchronized - TODO: add std::mutex */ (m_initLock) {
            if (!m_isInitialized) {
               try {
                  acquireContextReentrant();
                  var0.invoke();
               } finally {
                  releaseContextReentrant();
               }

               return;
            }
         }
      }

      if (ContextThread == Thread.currentThread()) {
         var0.invoke();
      } else {
         /* synchronized - TODO: add std::mutex */ (invokeOnRenderQueue) {
            invokeOnRenderQueue.push_back(var0);
         }
      }
   }

    static void shutdown() {
      GameWindow.GameInput.quit();
      if (m_isInitialized) {
         queueInvokeOnRenderContext(Display::destroy);
      } else {
         Display.destroy();
      }
   }

    static bool isCloseRequested() {
      if (m_isCloseRequested) {
         DebugLog.log("EXITDEBUG: RenderThread.isCloseRequested 1");
    return m_isCloseRequested;
      } else {
         if (!m_isInitialized) {
            /* synchronized - TODO: add std::mutex */ (m_initLock) {
               if (!m_isInitialized) {
                  m_isCloseRequested = Display.isCloseRequested();
                  if (m_isCloseRequested) {
                     DebugLog.log("EXITDEBUG: RenderThread.isCloseRequested 2");
                  }
               }
            }
         }

    return m_isCloseRequested;
      }
   }

    static int getDisplayWidth() {
      return !m_isInitialized ? Display.getWidth() : m_displayWidth;
   }

    static int getDisplayHeight() {
      return !m_isInitialized ? Display.getHeight() : m_displayHeight;
   }

    static bool isRunning() {
    return m_isInitialized;
   }

    static void startRendering() {
      m_renderingEnabled = true;
   }

    static void onGameThreadExited() {
      DebugLog.General.println("GameThread exited.");
      if (RenderThread != nullptr) {
         RenderThread.interrupt();
      }
   }

    static bool isCursorVisible() {
    return m_cursorVisible;
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
