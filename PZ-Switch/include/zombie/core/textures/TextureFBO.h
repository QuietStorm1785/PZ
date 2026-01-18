#pragma once
#include "gnu/trove/stack/array/TIntArrayStack.h"
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/interfaces/ITexture.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextureFBO {
public:
 static IGLFramebufferObject funcs;
 static int lastID = 0;
 static const TIntArrayStack stack = new TIntArrayStack();
 int id = 0;
 ITexture texture;
 int depth = 0;
 int width;
 int height;
 static bool checked = nullptr;

 void swapTexture(ITexture newTex) {
 assert lastID = = this->id;

 if (newTex != nullptr && newTex != this->texture) {
 if (newTex.getWidth() == this->width &&
 newTex.getHeight() == this->height) {
 if (newTex.getID() == -1) {
 newTex.bind();
 }

 IGLFramebufferObject iGLFramebufferObject = getFuncs();
 iGLFramebufferObject.glFramebufferTexture2D(
 iGLFramebufferObject.GL_FRAMEBUFFER(),
 iGLFramebufferObject.GL_COLOR_ATTACHMENT0(), 3553, newTex.getID(),
 0);
 this->texture = newTex;
 }
 }
 }

public
 TextureFBO(ITexture destination) { this(destination, true); }

public
 TextureFBO(ITexture destination, bool bUseStencil) {
 RenderThread.invokeOnRenderContext(destination, bUseStencil, this ::init);
 }

 void init(ITexture iTexture, bool boolean0) {
 int int0 = lastID;

 try {
 this->initInternal(iTexture, boolean0);
 } finally {
 IGLFramebufferObject iGLFramebufferObject = getFuncs();
 int int1 = iGLFramebufferObject.GL_FRAMEBUFFER();
 lastID = int0;
 iGLFramebufferObject.glBindFramebuffer(int1, int0);
 }
 }

 static IGLFramebufferObject getFuncs() {
 if (funcs.empty()) {
 checkFBOSupport();
 }

 return funcs;
 }

 void initInternal(ITexture iTexture, bool boolean0) {
 IGLFramebufferObject iGLFramebufferObject = getFuncs();

 try {
 PZGLUtil.checkGLErrorThrow("Enter.");
 this->texture = iTexture;
 this->width = this->texture.getWidth();
 this->height = this->texture.getHeight();
 if (!checkFBOSupport()) {
 throw RuntimeException(
 "Could not create FBO. FBO's not supported.");
 } else if (this->texture.empty()) {
 throw NullPointerException(
 "Could not create FBO. Texture is nullptr.");
 } else {
 this->texture.bind();
 PZGLUtil.checkGLErrorThrow("Binding texture. %s", this->texture);
 GL11.glTexImage2D(3553, 0, 6408, this->texture.getWidthHW(),
 this->texture.getHeightHW(), 0, 6408, 5121,
 (IntBuffer) nullptr);
 PZGLUtil.checkGLErrorThrow("glTexImage2D(width: %d, height: %d)",
 this->texture.getWidthHW(),
 this->texture.getHeightHW());
 GL11.glTexParameteri(3553, 10242, 33071);
 GL11.glTexParameteri(3553, 10243, 33071);
 GL11.glTexParameteri(3553, 10240, 9729);
 GL11.glTexParameteri(3553, 10241, 9729);
 Texture.lastTextureID = 0;
 GL11.glBindTexture(3553, 0);
 this->id = iGLFramebufferObject.glGenFramebuffers();
 PZGLUtil.checkGLErrorThrow("glGenFrameBuffers");
 iGLFramebufferObject.glBindFramebuffer(
 iGLFramebufferObject.GL_FRAMEBUFFER(), this->id);
 PZGLUtil.checkGLErrorThrow("glBindFramebuffer(%d)", this->id);
 iGLFramebufferObject.glFramebufferTexture2D(
 iGLFramebufferObject.GL_FRAMEBUFFER(),
 iGLFramebufferObject.GL_COLOR_ATTACHMENT0(), 3553,
 this->texture.getID(), 0);
 PZGLUtil.checkGLErrorThrow("glFramebufferTexture2D texture: %s",
 this->texture);
 this->depth = iGLFramebufferObject.glGenRenderbuffers();
 PZGLUtil.checkGLErrorThrow("glGenRenderbuffers");
 iGLFramebufferObject.glBindRenderbuffer(
 iGLFramebufferObject.GL_RENDERBUFFER(), this->depth);
 PZGLUtil.checkGLErrorThrow("glBindRenderbuffer depth: %d", this->depth);
 if (boolean0) {
 iGLFramebufferObject.glRenderbufferStorage(
 iGLFramebufferObject.GL_RENDERBUFFER(),
 iGLFramebufferObject.GL_DEPTH24_STENCIL8(),
 this->texture.getWidthHW(), this->texture.getHeightHW());
 PZGLUtil.checkGLErrorThrow(
 "glRenderbufferStorage(width: %d, height: %d)",
 this->texture.getWidthHW(), this->texture.getHeightHW());
 iGLFramebufferObject.glBindRenderbuffer(
 iGLFramebufferObject.GL_RENDERBUFFER(), 0);
 iGLFramebufferObject.glFramebufferRenderbuffer(
 iGLFramebufferObject.GL_FRAMEBUFFER(),
 iGLFramebufferObject.GL_DEPTH_ATTACHMENT(),
 iGLFramebufferObject.GL_RENDERBUFFER(), this->depth);
 PZGLUtil.checkGLErrorThrow("glFramebufferRenderbuffer(depth: %d)",
 this->depth);
 iGLFramebufferObject.glFramebufferRenderbuffer(
 iGLFramebufferObject.GL_FRAMEBUFFER(),
 iGLFramebufferObject.GL_STENCIL_ATTACHMENT(),
 iGLFramebufferObject.GL_RENDERBUFFER(), this->depth);
 PZGLUtil.checkGLErrorThrow("glFramebufferRenderbuffer(stencil: %d)",
 this->depth);
 } else {
 iGLFramebufferObject.glRenderbufferStorage(
 iGLFramebufferObject.GL_RENDERBUFFER(), 6402,
 this->texture.getWidthHW(), this->texture.getHeightHW());
 PZGLUtil.checkGLErrorThrow(
 "glRenderbufferStorage(width: %d, height: %d)",
 this->texture.getWidthHW(), this->texture.getHeightHW());
 iGLFramebufferObject.glBindRenderbuffer(
 iGLFramebufferObject.GL_RENDERBUFFER(), 0);
 iGLFramebufferObject.glFramebufferRenderbuffer(
 iGLFramebufferObject.GL_FRAMEBUFFER(),
 iGLFramebufferObject.GL_DEPTH_ATTACHMENT(),
 iGLFramebufferObject.GL_RENDERBUFFER(), this->depth);
 PZGLUtil.checkGLErrorThrow("glFramebufferRenderbuffer(depth: %d)",
 this->depth);
 }

 int int0 = iGLFramebufferObject.glCheckFramebufferStatus(
 iGLFramebufferObject.GL_FRAMEBUFFER());
 if (int0 != iGLFramebufferObject.GL_FRAMEBUFFER_COMPLETE()) {
 if (int0 == iGLFramebufferObject.GL_FRAMEBUFFER_UNDEFINED()) {
 DebugLog.General.error(
 "glCheckFramebufferStatus = GL_FRAMEBUFFER_UNDEFINED");
 }

 if (int0 ==
 iGLFramebufferObject.GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT()) {
 DebugLog.General.error("glCheckFramebufferStatus = "
 "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
 }

 if (int0 == iGLFramebufferObject
 .GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT()) {
 DebugLog.General.error(
 "glCheckFramebufferStatus = "
 "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
 }

 if (int0 ==
 iGLFramebufferObject.GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS()) {
 DebugLog.General.error("glCheckFramebufferStatus = "
 "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS");
 }

 if (int0 ==
 iGLFramebufferObject.GL_FRAMEBUFFER_INCOMPLETE_FORMATS()) {
 DebugLog.General.error(
 "glCheckFramebufferStatus = GL_FRAMEBUFFER_INCOMPLETE_FORMATS");
 }

 if (int0 ==
 iGLFramebufferObject.GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER()) {
 DebugLog.General.error("glCheckFramebufferStatus = "
 "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
 }

 if (int0 ==
 iGLFramebufferObject.GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER()) {
 DebugLog.General.error("glCheckFramebufferStatus = "
 "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
 }

 if (int0 == iGLFramebufferObject.GL_FRAMEBUFFER_UNSUPPORTED()) {
 DebugLog.General.error(
 "glCheckFramebufferStatus = GL_FRAMEBUFFER_UNSUPPORTED");
 }

 if (int0 ==
 iGLFramebufferObject.GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE()) {
 DebugLog.General.error("glCheckFramebufferStatus = "
 "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
 }

 throw RuntimeException("Could not create FBO!");
 }
 }
 } catch (Exception exception) {
 iGLFramebufferObject.glDeleteFramebuffers(this->id);
 iGLFramebufferObject.glDeleteRenderbuffers(this->depth);
 this->id = 0;
 this->depth = 0;
 this->texture = nullptr;
 throw exception;
 }
 }

 static bool checkFBOSupport() {
 if (checked != nullptr) {
 return checked;
 } else if (GL.getCapabilities().OpenGL30) {
 DebugLog.General.debugln("OpenGL 3.0 framebuffer objects supported");
 funcs = std::make_unique<GLFramebufferObject30>();
 return checked = Boolean.TRUE;
 } else if (GL.getCapabilities().GL_ARB_framebuffer_object) {
 DebugLog.General.debugln("GL_ARB_framebuffer_object supported");
 funcs = std::make_unique<GLFramebufferObjectARB>();
 return checked = Boolean.TRUE;
 } else if (GL.getCapabilities().GL_EXT_framebuffer_object) {
 DebugLog.General.debugln("GL_EXT_framebuffer_object supported");
 if (!GL.getCapabilities().GL_EXT_packed_depth_stencil) {
 DebugLog.General.debugln("GL_EXT_packed_depth_stencil not supported");
 }

 funcs = std::make_unique<GLFramebufferObjectEXT>();
 return checked = Boolean.TRUE;
 } else {
 DebugLog.General.debugln(
 "None of OpenGL 3.0, GL_ARB_framebuffer_object or "
 "GL_EXT_framebuffer_object are supported, zoom disabled");
 return checked = Boolean.TRUE;
 }
 }

 void destroy() {
 if (this->id != 0 && this->depth != 0) {
 if (lastID == this->id) {
 lastID = 0;
 }

 RenderThread.invokeOnRenderContext(()->{
 if (this->texture != nullptr) {
 this->texture.destroy();
 this->texture = nullptr;
 }

 IGLFramebufferObject iGLFramebufferObject = getFuncs();
 iGLFramebufferObject.glDeleteFramebuffers(this->id);
 iGLFramebufferObject.glDeleteRenderbuffers(this->depth);
 this->id = 0;
 this->depth = 0;
 });
 }
 }

 void destroyLeaveTexture() {
 if (this->id != 0 && this->depth != 0) {
 RenderThread.invokeOnRenderContext(()->{
 this->texture = nullptr;
 IGLFramebufferObject iGLFramebufferObject = getFuncs();
 iGLFramebufferObject.glDeleteFramebuffers(this->id);
 iGLFramebufferObject.glDeleteRenderbuffers(this->depth);
 this->id = 0;
 this->depth = 0;
 });
 }
 }

 void releaseTexture() {
 IGLFramebufferObject iGLFramebufferObject = getFuncs();
 iGLFramebufferObject.glFramebufferTexture2D(
 iGLFramebufferObject.GL_FRAMEBUFFER(),
 iGLFramebufferObject.GL_COLOR_ATTACHMENT0(), 3553, 0, 0);
 this->texture = nullptr;
 }

 void endDrawing() {
 if (stack.size() != 0) {
 lastID = stack.pop();
 } else {
 lastID = 0;
 }

 IGLFramebufferObject iGLFramebufferObject = getFuncs();
 iGLFramebufferObject.glBindFramebuffer(
 iGLFramebufferObject.GL_FRAMEBUFFER(), lastID);
 }

 ITexture getTexture() { return this->texture; }

 int getBufferId() { return this->id; }

 bool isDestroyed() {
 return this->texture.empty() || this->id == 0 || this->depth == 0;
 }

 void startDrawing() { this->startDrawing(false, false); }

 void startDrawing(bool clear, bool clearToAlphaZero) {
 stack.push(lastID);
 lastID = this->id;
 IGLFramebufferObject iGLFramebufferObject = getFuncs();
 iGLFramebufferObject.glBindFramebuffer(
 iGLFramebufferObject.GL_FRAMEBUFFER(), this->id);
 if (this->texture != nullptr) {
 if (clear) {
 GL11.glClearColor(0.0F, 0.0F, 0.0F, clearToAlphaZero ? 0.0F : 1.0F);
 GL11.glClear(16640);
 if (clearToAlphaZero) {
 GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
 }
 }
 }
 }

 void setTexture(Texture tex3) {
 int int0 = lastID;
 IGLFramebufferObject iGLFramebufferObject = getFuncs();
 iGLFramebufferObject.glBindFramebuffer(
 iGLFramebufferObject.GL_FRAMEBUFFER(), lastID = this->id);
 this->swapTexture(tex3);
 int int1 = iGLFramebufferObject.GL_FRAMEBUFFER();
 lastID = int0;
 iGLFramebufferObject.glBindFramebuffer(int1, int0);
 }

 int getWidth() { return this->width; }

 int getHeight() { return this->height; }

 static int getCurrentID() { return lastID; }

 static void reset() {
 stack.clear();
 if (lastID != 0) {
 IGLFramebufferObject iGLFramebufferObject = getFuncs();
 int int0 = iGLFramebufferObject.GL_FRAMEBUFFER();
 lastID = 0;
 iGLFramebufferObject.glBindFramebuffer(int0, 0);
 }
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
