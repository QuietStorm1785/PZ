#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/BufferUtils.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL12.h"
#include "org/lwjgl/opengl/GL13.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/VBO/GLVertexBufferObject.h"
#include "zombie/core/VBO/IGLBufferObject.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/worldMap/VBOLinesUV/Run.h"
#include <filesystem>

namespace zombie {
namespace worldMap {


class VBOLinesUV {
public:
    const int VERTEX_SIZE = 12;
    const int COLOR_SIZE = 16;
    const int UV_SIZE = 8;
    const int ELEMENT_SIZE = 36;
    const int COLOR_OFFSET = 12;
    const int UV_OFFSET = 28;
    const int NUM_ELEMENTS = 128;
    const int INDEX_SIZE = 2;
    GLVertexBufferObject m_vbo;
    GLVertexBufferObject m_ibo;
    ByteBuffer m_elements;
    ByteBuffer m_indices;
    float m_lineWidth = 1.0F;
    float m_dx = 0.0F;
    float m_dy = 0.0F;
    float m_dz = 0.0F;
    int m_mode = 1;
   private const ObjectPool<Run> m_runPool = std::make_shared<ObjectPool>(Run::new);
   private const std::vector<Run> m_runs = std::make_unique<std::vector<>>();

    Run currentRun() {
      return this.m_runs.empty() ? nullptr : this.m_runs.get(this.m_runs.size() - 1);
   }

    void create() {
      this.m_elements = BufferUtils.createByteBuffer(4608);
      this.m_indices = BufferUtils.createByteBuffer(256);
    IGLBufferObject var1 = GLVertexBufferObject.funcs;
      this.m_vbo = std::make_shared<GLVertexBufferObject>(4608L, var1.GL_ARRAY_BUFFER(), var1.GL_STREAM_DRAW());
      this.m_vbo.create();
      this.m_ibo = std::make_shared<GLVertexBufferObject>(256L, var1.GL_ELEMENT_ARRAY_BUFFER(), var1.GL_STREAM_DRAW());
      this.m_ibo.create();
   }

    void setOffset(float var1, float var2, float var3) {
      this.m_dx = var1;
      this.m_dy = var2;
      this.m_dz = var3;
   }

    void addElement(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9) {
      if (this.isFull()) {
    TextureID var10 = this.currentRun().textureID;
         this.flush();
         this.startRun(var10);
      }

      if (this.m_elements == nullptr) {
         this.create();
      }

      this.m_elements.putFloat(this.m_dx + var1);
      this.m_elements.putFloat(this.m_dy + var2);
      this.m_elements.putFloat(this.m_dz + var3);
      this.m_elements.putFloat(var6);
      this.m_elements.putFloat(var7);
      this.m_elements.putFloat(var8);
      this.m_elements.putFloat(var9);
      this.m_elements.putFloat(var4);
      this.m_elements.putFloat(var5);
    short var11 = (short)(this.m_indices.position() / 2);
      this.m_indices.putShort(var11);
      this.currentRun().count++;
   }

    void addElement(float var1, float var2, float var3, float var4, float var5, float var6, float var7) {
      this.addElement(var1, var2, var3, 0.0F, 0.0F, var4, var5, var6, var7);
   }

    void addLine(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10) {
      this.addElement(var1, var2, var3, var7, var8, var9, var10);
      this.addElement(var4, var5, var6, var7, var8, var9, var10);
   }

   public void addLine(
      float var1,
      float var2,
      float var3,
      float var4,
      float var5,
      float var6,
      float var7,
      float var8,
      float var9,
      float var10,
      float var11,
      float var12,
      float var13,
      float var14
   ) {
      this.addElement(var1, var2, var3, var7, var8, var9, var10);
      this.addElement(var4, var5, var6, var11, var12, var13, var14);
   }

   public void addTriangle(
      float var1,
      float var2,
      float var3,
      float var4,
      float var5,
      float var6,
      float var7,
      float var8,
      float var9,
      float var10,
      float var11,
      float var12,
      float var13,
      float var14,
      float var15,
      float var16,
      float var17,
      float var18,
      float var19
   ) {
      this.reserve(3);
      this.addElement(var1, var2, var3, var4, var5, var16, var17, var18, var19);
      this.addElement(var6, var7, var8, var9, var10, var16, var17, var18, var19);
      this.addElement(var11, var12, var13, var14, var15, var16, var17, var18, var19);
   }

   public void addQuad(
      float var1,
      float var2,
      float var3,
      float var4,
      float var5,
      float var6,
      float var7,
      float var8,
      float var9,
      float var10,
      float var11,
      float var12,
      float var13
   ) {
      this.reserve(4);
      this.addElement(var1, var2, var9, var3, var4, var10, var11, var12, var13);
      this.addElement(var5, var2, var9, var7, var4, var10, var11, var12, var13);
      this.addElement(var5, var6, var9, var7, var8, var10, var11, var12, var13);
      this.addElement(var1, var6, var9, var3, var8, var10, var11, var12, var13);
   }

   public void addQuad(
      float var1,
      float var2,
      float var3,
      float var4,
      float var5,
      float var6,
      float var7,
      float var8,
      float var9,
      float var10,
      float var11,
      float var12,
      float var13,
      float var14,
      float var15,
      float var16,
      float var17,
      float var18,
      float var19,
      float var20,
      float var21
   ) {
      this.reserve(4);
      this.addElement(var1, var2, var17, var3, var4, var18, var19, var20, var21);
      this.addElement(var5, var6, var17, var7, var8, var18, var19, var20, var21);
      this.addElement(var9, var10, var17, var11, var12, var18, var19, var20, var21);
      this.addElement(var13, var14, var17, var15, var16, var18, var19, var20, var21);
   }

    bool isFull() {
      if (this.m_elements == nullptr) {
    return false;
      } else {
         return this.m_mode == 4 && this.m_elements.position() % 108 == 0 && this.m_elements.position() + 108 > 4608
            ? true
            : this.m_elements.position() == 4608;
      }
   }

    void reserve(int var1) {
      if (!this.hasRoomFor(var1)) {
    TextureID var2 = this.currentRun() == nullptr ? nullptr : this.currentRun().textureID;
         this.flush();
         if (var2 != nullptr) {
            this.startRun(var2);
         }
      }
   }

    bool hasRoomFor(int var1) {
      return this.m_elements == nullptr || this.m_elements.position() / 36 + var1 <= 128;
   }

    void flush() {
      if (this.m_elements != nullptr && this.m_elements.position() != 0) {
         this.m_elements.flip();
         this.m_indices.flip();
         GL13.glClientActiveTexture(33984);
         GL11.glEnableClientState(32888);
         this.m_vbo.bind();
         this.m_vbo.bufferData(this.m_elements);
         this.m_ibo.bind();
         this.m_ibo.bufferData(this.m_indices);
         GL11.glEnableClientState(32884);
         GL11.glEnableClientState(32886);
         GL11.glVertexPointer(3, 5126, 36, 0L);
         GL11.glColorPointer(4, 5126, 36, 12L);
         GL11.glTexCoordPointer(2, 5126, 36, 28L);
         GL11.glEnable(3553);
         GL11.glDisable(2929);
         GL11.glEnable(2848);
         GL11.glLineWidth(this.m_lineWidth);

         for (int var1 = 0; var1 < this.m_runs.size(); var1++) {
    Run var2 = this.m_runs.get(var1);
    int var3 = var2.start;
    int var4 = var2.count;
    int var5 = var2.start;
    int var6 = var5 + var2.count;
            if (var2.textureID.getID() == -1) {
               var2.textureID.bind();
            } else {
               GL11.glBindTexture(3553, Texture.lastTextureID = var2.textureID.getID());
               GL11.glTexParameteri(3553, 10241, 9729);
               GL11.glTexParameteri(3553, 10240, 9728);
            }

            GL12.glDrawRangeElements(this.m_mode, var3, var3 + var4, var6 - var5, 5123, var5 * 2L);
         }

         this.m_vbo.bindNone();
         this.m_ibo.bindNone();
         this.m_elements.clear();
         this.m_indices.clear();
         this.m_runPool.releaseAll(this.m_runs);
         this.m_runs.clear();
         GL11.glEnable(2929);
         GL11.glDisable(2848);
         GL13.glClientActiveTexture(33984);
         SpriteRenderer.ringBuffer.restoreVBOs = true;
         SpriteRenderer.ringBuffer.restoreBoundTextures = true;
      }
   }

    void setLineWidth(float var1) {
      if (!PZMath.equal(this.m_lineWidth, var1, 0.01F)) {
    TextureID var2 = this.currentRun() == nullptr ? nullptr : this.currentRun().textureID;
         this.flush();
         if (var2 != nullptr) {
            this.startRun(var2);
         }

         this.m_lineWidth = var1;
      }
   }

    void setMode(int var1) {
    assert var1 = = 1 || var1 == 4 || var1 == 7;

      if (var1 != this.m_mode) {
    TextureID var2 = this.currentRun() == nullptr ? nullptr : this.currentRun().textureID;
         this.flush();
         if (var2 != nullptr) {
            this.startRun(var2);
         }

         this.m_mode = var1;
      }
   }

    void startRun(TextureID var1) {
    Run var2 = (Run)this.m_runPool.alloc();
      var2.start = this.m_elements == nullptr ? 0 : this.m_elements.position() / 36;
      var2.count = 0;
      var2.textureID = var1;
      this.m_runs.push_back(var2);
   }
}
} // namespace worldMap
} // namespace zombie
