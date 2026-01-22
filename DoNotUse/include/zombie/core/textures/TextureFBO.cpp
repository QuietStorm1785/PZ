#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/stack/array/TIntArrayStack.h"
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/interfaces/ITexture.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace textures {


class TextureFBO {
public:
    static IGLFramebufferObject funcs;
    static int lastID = 0;
    static const TIntArrayStack stack = std::make_shared<TIntArrayStack>();
    int id = 0;
    ITexture texture;
    int depth = 0;
    int width;
    int height;
    static bool checked = nullptr;

    void swapTexture(ITexture var1) {
    assert lastID = = this.id;

      if (var1 != nullptr && var1 != this.texture) {
         if (var1.getWidth() == this.width && var1.getHeight() == this.height) {
            if (var1.getID() == -1) {
               var1.bind();
            }

    IGLFramebufferObject var2 = getFuncs();
            var2.glFramebufferTexture2D(var2.GL_FRAMEBUFFER(), var2.GL_COLOR_ATTACHMENT0(), 3553, var1.getID(), 0);
            this.texture = var1;
         }
      }
   }

    public TextureFBO(ITexture var1) {
      this(var1, true);
   }

    public TextureFBO(ITexture var1, bool var2) {
      RenderThread.invokeOnRenderContext(var1, var2, this::init);
   }

    void init(ITexture var1, bool var2) {
    int var3 = lastID;

      try {
         this.initInternal(var1, var2);
      } finally {
    IGLFramebufferObject var6 = getFuncs();
    int var10001 = var6.GL_FRAMEBUFFER();
         lastID = var3;
         var6.glBindFramebuffer(var10001, var3);
      }
   }

    static IGLFramebufferObject getFuncs() {
      if (funcs == nullptr) {
         checkFBOSupport();
      }

    return funcs;
   }

    void initInternal(ITexture var1, bool var2) {
    IGLFramebufferObject var3 = getFuncs();

      try {
         PZGLUtil.checkGLErrorThrow("Enter.", new Object[0]);
         this.texture = var1;
         this.width = this.texture.getWidth();
         this.height = this.texture.getHeight();
         if (!checkFBOSupport()) {
            throw RuntimeException("Could not create FBO. FBO's not supported.");
         } else if (this.texture == nullptr) {
            throw NullPointerException("Could not create FBO. Texture is nullptr.");
         } else {
            this.texture.bind();
            PZGLUtil.checkGLErrorThrow("Binding texture. %s", new Object[]{this.texture});
            GL11.glTexImage2D(3553, 0, 6408, this.texture.getWidthHW(), this.texture.getHeightHW(), 0, 6408, 5121, (IntBuffer)nullptr);
            PZGLUtil.checkGLErrorThrow("glTexImage2D(width: %d, height: %d)", new Object[]{this.texture.getWidthHW(), this.texture.getHeightHW()});
            GL11.glTexParameteri(3553, 10242, 33071);
            GL11.glTexParameteri(3553, 10243, 33071);
            GL11.glTexParameteri(3553, 10240, 9729);
            GL11.glTexParameteri(3553, 10241, 9729);
            Texture.lastTextureID = 0;
            GL11.glBindTexture(3553, 0);
            this.id = var3.glGenFramebuffers();
            PZGLUtil.checkGLErrorThrow("glGenFrameBuffers", new Object[0]);
            var3.glBindFramebuffer(var3.GL_FRAMEBUFFER(), this.id);
            PZGLUtil.checkGLErrorThrow("glBindFramebuffer(%d)", new Object[]{this.id});
            var3.glFramebufferTexture2D(var3.GL_FRAMEBUFFER(), var3.GL_COLOR_ATTACHMENT0(), 3553, this.texture.getID(), 0);
            PZGLUtil.checkGLErrorThrow("glFramebufferTexture2D texture: %s", new Object[]{this.texture});
            this.depth = var3.glGenRenderbuffers();
            PZGLUtil.checkGLErrorThrow("glGenRenderbuffers", new Object[0]);
            var3.glBindRenderbuffer(var3.GL_RENDERBUFFER(), this.depth);
            PZGLUtil.checkGLErrorThrow("glBindRenderbuffer depth: %d", new Object[]{this.depth});
            if (var2) {
               var3.glRenderbufferStorage(var3.GL_RENDERBUFFER(), var3.GL_DEPTH24_STENCIL8(), this.texture.getWidthHW(), this.texture.getHeightHW());
               PZGLUtil.checkGLErrorThrow("glRenderbufferStorage(width: %d, height: %d)", new Object[]{this.texture.getWidthHW(), this.texture.getHeightHW()});
               var3.glBindRenderbuffer(var3.GL_RENDERBUFFER(), 0);
               var3.glFramebufferRenderbuffer(var3.GL_FRAMEBUFFER(), var3.GL_DEPTH_ATTACHMENT(), var3.GL_RENDERBUFFER(), this.depth);
               PZGLUtil.checkGLErrorThrow("glFramebufferRenderbuffer(depth: %d)", new Object[]{this.depth});
               var3.glFramebufferRenderbuffer(var3.GL_FRAMEBUFFER(), var3.GL_STENCIL_ATTACHMENT(), var3.GL_RENDERBUFFER(), this.depth);
               PZGLUtil.checkGLErrorThrow("glFramebufferRenderbuffer(stencil: %d)", new Object[]{this.depth});
            } else {
               var3.glRenderbufferStorage(var3.GL_RENDERBUFFER(), 6402, this.texture.getWidthHW(), this.texture.getHeightHW());
               PZGLUtil.checkGLErrorThrow("glRenderbufferStorage(width: %d, height: %d)", new Object[]{this.texture.getWidthHW(), this.texture.getHeightHW()});
               var3.glBindRenderbuffer(var3.GL_RENDERBUFFER(), 0);
               var3.glFramebufferRenderbuffer(var3.GL_FRAMEBUFFER(), var3.GL_DEPTH_ATTACHMENT(), var3.GL_RENDERBUFFER(), this.depth);
               PZGLUtil.checkGLErrorThrow("glFramebufferRenderbuffer(depth: %d)", new Object[]{this.depth});
            }

    int var4 = var3.glCheckFramebufferStatus(var3.GL_FRAMEBUFFER());
            if (var4 != var3.GL_FRAMEBUFFER_COMPLETE()) {
               if (var4 == var3.GL_FRAMEBUFFER_UNDEFINED()) {
                  DebugLog.General.error("glCheckFramebufferStatus = GL_FRAMEBUFFER_UNDEFINED");
               }

               if (var4 == var3.GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT()) {
                  DebugLog.General.error("glCheckFramebufferStatus = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
               }

               if (var4 == var3.GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT()) {
                  DebugLog.General.error("glCheckFramebufferStatus = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
               }

               if (var4 == var3.GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS()) {
                  DebugLog.General.error("glCheckFramebufferStatus = GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS");
               }

               if (var4 == var3.GL_FRAMEBUFFER_INCOMPLETE_FORMATS()) {
                  DebugLog.General.error("glCheckFramebufferStatus = GL_FRAMEBUFFER_INCOMPLETE_FORMATS");
               }

               if (var4 == var3.GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER()) {
                  DebugLog.General.error("glCheckFramebufferStatus = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
               }

               if (var4 == var3.GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER()) {
                  DebugLog.General.error("glCheckFramebufferStatus = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
               }

               if (var4 == var3.GL_FRAMEBUFFER_UNSUPPORTED()) {
                  DebugLog.General.error("glCheckFramebufferStatus = GL_FRAMEBUFFER_UNSUPPORTED");
               }

               if (var4 == var3.GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE()) {
                  DebugLog.General.error("glCheckFramebufferStatus = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
               }

               throw RuntimeException("Could not create FBO!");
            }
         }
      } catch (Exception var5) {
         var3.glDeleteFramebuffers(this.id);
         var3.glDeleteRenderbuffers(this.depth);
         this.id = 0;
         this.depth = 0;
         this.texture = nullptr;
    throw var5;
      }
   }

    static bool checkFBOSupport() {
      if (checked != nullptr) {
    return checked;
      } else if (GL.getCapabilities().OpenGL30) {
         DebugLog.General.debugln("OpenGL 3.0 framebuffer objects supported");
         funcs = std::make_unique<GLFramebufferObject30>();
    return checked = bool.TRUE;
      } else if (GL.getCapabilities().GL_ARB_framebuffer_object) {
         DebugLog.General.debugln("GL_ARB_framebuffer_object supported");
         funcs = std::make_unique<GLFramebufferObjectARB>();
    return checked = bool.TRUE;
      } else if (GL.getCapabilities().GL_EXT_framebuffer_object) {
         DebugLog.General.debugln("GL_EXT_framebuffer_object supported");
         if (!GL.getCapabilities().GL_EXT_packed_depth_stencil) {
            DebugLog.General.debugln("GL_EXT_packed_depth_stencil not supported");
         }

         funcs = std::make_unique<GLFramebufferObjectEXT>();
    return checked = bool.TRUE;
      } else {
         DebugLog.General.debugln("None of OpenGL 3.0, GL_ARB_framebuffer_object or GL_EXT_framebuffer_object are supported, zoom disabled");
    return checked = bool.TRUE;
      }
   }

    void destroy() {
      if (this.id != 0 && this.depth != 0) {
         if (lastID == this.id) {
            lastID = 0;
         }

         RenderThread.invokeOnRenderContext(() -> {
            if (this.texture != nullptr) {
               this.texture.destroy();
               this.texture = nullptr;
            }

    IGLFramebufferObject var1 = getFuncs();
            var1.glDeleteFramebuffers(this.id);
            var1.glDeleteRenderbuffers(this.depth);
            this.id = 0;
            this.depth = 0;
         });
      }
   }

    void destroyLeaveTexture() {
      if (this.id != 0 && this.depth != 0) {
         RenderThread.invokeOnRenderContext(() -> {
            this.texture = nullptr;
    IGLFramebufferObject var1 = getFuncs();
            var1.glDeleteFramebuffers(this.id);
            var1.glDeleteRenderbuffers(this.depth);
            this.id = 0;
            this.depth = 0;
         });
      }
   }

    void releaseTexture() {
    IGLFramebufferObject var1 = getFuncs();
      var1.glFramebufferTexture2D(var1.GL_FRAMEBUFFER(), var1.GL_COLOR_ATTACHMENT0(), 3553, 0, 0);
      this.texture = nullptr;
   }

    void endDrawing() {
      if (stack.size() != 0) {
         lastID = stack.pop();
      } else {
         lastID = 0;
      }

    IGLFramebufferObject var1 = getFuncs();
      var1.glBindFramebuffer(var1.GL_FRAMEBUFFER(), lastID);
   }

    ITexture getTexture() {
      return this.texture;
   }

    int getBufferId() {
      return this.id;
   }

    bool isDestroyed() {
      return this.texture == nullptr || this.id == 0 || this.depth == 0;
   }

    void startDrawing() {
      this.startDrawing(false, false);
   }

    void startDrawing(bool var1, bool var2) {
      stack.push(lastID);
      lastID = this.id;
    IGLFramebufferObject var3 = getFuncs();
      var3.glBindFramebuffer(var3.GL_FRAMEBUFFER(), this.id);
      if (this.texture != nullptr) {
         if (var1) {
            GL11.glClearColor(0.0F, 0.0F, 0.0F, var2 ? 0.0F : 1.0F);
            GL11.glClear(16640);
            if (var2) {
               GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
            }
         }
      }
   }

    void setTexture(Texture var1) {
    int var2 = lastID;
    IGLFramebufferObject var3 = getFuncs();
      var3.glBindFramebuffer(var3.GL_FRAMEBUFFER(), lastID = this.id);
      this.swapTexture(var1);
    int var10001 = var3.GL_FRAMEBUFFER();
      lastID = var2;
      var3.glBindFramebuffer(var10001, var2);
   }

    int getWidth() {
      return this.width;
   }

    int getHeight() {
      return this.height;
   }

    static int getCurrentID() {
    return lastID;
   }

    static void reset() {
      stack.clear();
      if (lastID != 0) {
    IGLFramebufferObject var0 = getFuncs();
    int var10001 = var0.GL_FRAMEBUFFER();
         lastID = 0;
         var0.glBindFramebuffer(var10001, 0);
      }
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
