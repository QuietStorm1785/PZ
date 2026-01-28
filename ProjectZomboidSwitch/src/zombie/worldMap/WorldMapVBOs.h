#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/BufferUtils.h"
#include <GL/glew.h>
#include <GL/glew.h>

#include "zombie/worldMap/WorldMapVBOs/WorldMapVBO.h"
#include <filesystem>

namespace zombie {
namespace worldMap {


class WorldMapVBOs {
public:
    static const int VERTEX_SIZE = 12;
    static const int COLOR_SIZE = 16;
    static const int ELEMENT_SIZE = 28;
    static const int COLOR_OFFSET = 12;
    static const int NUM_ELEMENTS = 2340;
    static const int INDEX_SIZE = 2;
    static const WorldMapVBOs instance = std::make_shared<WorldMapVBOs>();
   private const std::vector<WorldMapVBO> m_vbos = std::make_unique<std::vector<>>();
    ByteBuffer m_elements;
    ByteBuffer m_indices;

    static WorldMapVBOs getInstance() {
    return instance;
   }

    void create() {
      this.m_elements = BufferUtils.createByteBuffer(65520);
      this.m_indices = BufferUtils.createByteBuffer(4680);
   }

    void flush() {
      if (this.m_vbos.empty()) {
    WorldMapVBO var1 = std::make_shared<WorldMapVBO>();
         var1.create();
         this.m_vbos.push_back(var1);
      }

      this.m_elements.flip();
      this.m_indices.flip();
      this.m_vbos.get(this.m_vbos.size() - 1).flush(this.m_elements, this.m_indices);
      this.m_elements.position(this.m_elements.limit());
      this.m_elements.limit(this.m_elements.capacity());
      this.m_indices.position(this.m_indices.limit());
      this.m_indices.limit(this.m_indices.capacity());
   }

    void addVBO() {
    WorldMapVBO var1 = std::make_shared<WorldMapVBO>();
      var1.create();
      this.m_vbos.push_back(var1);
      this.m_elements.clear();
      this.m_indices.clear();
   }

    void reserveVertices(int var1, int[] var2) {
      if (this.m_indices == nullptr) {
         this.create();
      }

    int var3 = this.m_indices.position() / 2;
      if (var3 + var1 > 2340) {
         this.flush();
         this.addVBO();
      }

      var2[0] = this.m_vbos.empty() ? 0 : this.m_vbos.size() - 1;
      var2[1] = this.m_indices.position() / 2;
   }

    void addElement(float var1, float var2, float var3, float var4, float var5, float var6, float var7) {
      this.m_elements.putFloat(var1);
      this.m_elements.putFloat(var2);
      this.m_elements.putFloat(var3);
      this.m_elements.putFloat(var4);
      this.m_elements.putFloat(var5);
      this.m_elements.putFloat(var6);
      this.m_elements.putFloat(var7);
    short var8 = (short)(this.m_indices.position() / 2);
      this.m_indices.putShort(var8);
   }

    void drawElements(int var1, int var2, int var3, int var4) {
      if (var2 >= 0 && var2 < this.m_vbos.size()) {
    WorldMapVBO var5 = this.m_vbos.get(var2);
         if (var3 >= 0 && var3 + var4 <= var5.m_elementCount) {
            var5.m_vbo.bind();
            var5.m_ibo.bind();
            GL11.glEnableClientState(32884);
            GL11.glDisableClientState(32886);
            GL11.glVertexPointer(3, 5126, 28, 0L);

            for (int var6 = 7; var6 >= 0; var6--) {
               GL13.glActiveTexture(33984 + var6);
               GL11.glDisable(3553);
            }

            GL11.glDisable(2929);
            GL12.glDrawRangeElements(var1, var3, var3 + var4, var4, 5123, var3 * 2);
            var5.m_vbo.bindNone();
            var5.m_ibo.bindNone();
         }
      }
   }

    void reset() {
   }
}
} // namespace worldMap
} // namespace zombie
