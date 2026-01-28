#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/BufferUtils.h"
#include <GL/glew.h>
#include "zombie/SandboxOptions.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/core/utils/ImageUtils.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SliceY.h"
#include "zombie/iso/Vector2.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RGBAf.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace worldMap {


class WorldMapVisited {
public:
    static WorldMapVisited instance;
    int m_minX;
    int m_minY;
    int m_maxX;
    int m_maxY;
   byte[] m_visited;
    bool m_changed = false;
    int m_changeX1 = 0;
    int m_changeY1 = 0;
    int m_changeX2 = 0;
    int m_changeY2 = 0;
   private const int[] m_updateMinX = new int[4];
   private const int[] m_updateMinY = new int[4];
   private const int[] m_updateMaxX = new int[4];
   private const int[] m_updateMaxY = new int[4];
    static const int TEXTURE_BPP = 4;
    TextureID m_textureID;
    int m_textureW = 0;
    int m_textureH = 0;
    ByteBuffer m_textureBuffer;
    bool m_textureChanged = false;
    const RGBAf m_color = std::make_shared<RGBAf>().init(0.85882354F, 0.84313726F, 0.7529412F, 1.0F);
    const RGBAf m_gridColor = std::make_shared<RGBAf>().init(this.m_color.r * 0.85F, this.m_color.g * 0.85F, this.m_color.b * 0.85F, 1.0F);
    bool m_mainMenu = false;
    static ShaderProgram m_shaderProgram;
    static ShaderProgram m_gridShaderProgram;
    static const int UNITS_PER_CELL = 10;
    static const int SQUARES_PER_CELL = 300;
    static const int SQUARES_PER_UNIT = 30;
    static const int TEXTURE_PAD = 1;
    static const int BIT_VISITED = 1;
    static const int BIT_KNOWN = 2;
    Vector2 m_vector2 = std::make_shared<Vector2>();

    public WorldMapVisited() {
      Arrays.fill(this.m_updateMinX, -1);
      Arrays.fill(this.m_updateMinY, -1);
      Arrays.fill(this.m_updateMaxX, -1);
      Arrays.fill(this.m_updateMaxY, -1);
   }

    void setBounds(int var1, int var2, int var3, int var4) {
      if (var1 > var3 || var2 > var4) {
         var4 = 0;
         var2 = 0;
         var3 = 0;
         var1 = 0;
         this.m_mainMenu = true;
      }

      this.m_minX = var1;
      this.m_minY = var2;
      this.m_maxX = var3;
      this.m_maxY = var4;
      this.m_changed = true;
      this.m_changeX1 = 0;
      this.m_changeY1 = 0;
      this.m_changeX2 = this.getWidthInCells() * 10 - 1;
      this.m_changeY2 = this.getHeightInCells() * 10 - 1;
      this.m_visited = new byte[this.getWidthInCells() * 10 * this.getHeightInCells() * 10];
      this.m_textureW = this.calcTextureWidth();
      this.m_textureH = this.calcTextureHeight();
      this.m_textureBuffer = BufferUtils.createByteBuffer(this.m_textureW * this.m_textureH * 4);
      this.m_textureBuffer.limit(this.m_textureBuffer.capacity());
    int var5 = SandboxOptions.getInstance().Map.MapAllKnown.getValue() ? 0 : -1;
    uint8_t var6 = -1;
    uint8_t var7 = -1;
    uint8_t var8 = -1;

      for (byte var9 = 0; var9 < this.m_textureBuffer.limit(); var9 += 4) {
         this.m_textureBuffer.put(var9, (byte)var5);
         this.m_textureBuffer.put(var9 + 1, var6);
         this.m_textureBuffer.put(var9 + 2, var7);
         this.m_textureBuffer.put(var9 + 3, var8);
      }

      this.m_textureID = std::make_shared<TextureID>(this.m_textureW, this.m_textureH, 0);
   }

    int getMinX() {
      return this.m_minX;
   }

    int getMinY() {
      return this.m_minY;
   }

    int getWidthInCells() {
      return this.m_maxX - this.m_minX + 1;
   }

    int getHeightInCells() {
      return this.m_maxY - this.m_minY + 1;
   }

    int calcTextureWidth() {
      return ImageUtils.getNextPowerOfTwo(this.getWidthInCells() * 10 + 2);
   }

    int calcTextureHeight() {
      return ImageUtils.getNextPowerOfTwo(this.getHeightInCells() * 10 + 2);
   }

    void setKnownInCells(int var1, int var2, int var3, int var4) {
      this.setFlags(var1 * 300, var2 * 300, (var3 + 1) * 300, (var4 + 1) * 300, 2);
   }

    void clearKnownInCells(int var1, int var2, int var3, int var4) {
      this.clearFlags(var1 * 300, var2 * 300, (var3 + 1) * 300, (var4 + 1) * 300, 2);
   }

    void setVisitedInCells(int var1, int var2, int var3, int var4) {
      this.setFlags(var1 * 300, var2 * 300, var3 * 300, var4 * 300, 1);
   }

    void clearVisitedInCells(int var1, int var2, int var3, int var4) {
      this.clearFlags(var1 * 300, var2 * 300, var3 * 300, var4 * 300, 1);
   }

    void setKnownInSquares(int var1, int var2, int var3, int var4) {
      this.setFlags(var1, var2, var3, var4, 2);
   }

    void clearKnownInSquares(int var1, int var2, int var3, int var4) {
      this.clearFlags(var1, var2, var3, var4, 2);
   }

    void setVisitedInSquares(int var1, int var2, int var3, int var4) {
      this.setFlags(var1, var2, var3, var4, 1);
   }

    void clearVisitedInSquares(int var1, int var2, int var3, int var4) {
      this.clearFlags(var1, var2, var3, var4, 1);
   }

    void updateVisitedTexture() {
      this.m_textureID.bind();
      GL11.glTexImage2D(3553, 0, 6408, this.m_textureW, this.m_textureH, 0, 6408, 5121, this.m_textureBuffer);
   }

    void renderMain() {
      this.m_textureChanged = this.m_textureChanged | this.updateTextureData(this.m_textureBuffer, this.m_textureW);
   }

    void initShader() {
      m_shaderProgram = ShaderProgram.createShaderProgram("worldMapVisited", false, true);
      if (m_shaderProgram.isCompiled()) {
      }
   }

    void render(float var1, float var2, int var3, int var4, int var5, int var6, float var7, bool var8) {
      if (!this.m_mainMenu) {
         GL13.glActiveTexture(33984);
         GL13.glClientActiveTexture(33984);
         GL11.glEnable(3553);
         if (this.m_textureChanged) {
            this.m_textureChanged = false;
            this.updateVisitedTexture();
         }

         this.m_textureID.bind();
    int var9 = var8 ? 9729 : 9728;
         GL11.glTexParameteri(3553, 10241, var9);
         GL11.glTexParameteri(3553, 10240, var9);
         GL11.glEnable(3042);
         GL11.glTexEnvi(8960, 8704, 8448);
         GL11.glColor4f(this.m_color.r, this.m_color.g, this.m_color.b, this.m_color.a);
         if (m_shaderProgram == nullptr) {
            this.initShader();
         }

         if (m_shaderProgram.isCompiled()) {
            m_shaderProgram.Start();
    float var10 = (float)(1 + (var3 - this.m_minX) * 10) / this.m_textureW;
    float var11 = (float)(1 + (var4 - this.m_minY) * 10) / this.m_textureH;
    float var12 = (float)(1 + (var5 + 1 - this.m_minX) * 10) / this.m_textureW;
    float var13 = (float)(1 + (var6 + 1 - this.m_minY) * 10) / this.m_textureH;
    float var14 = (var3 - this.m_minX) * 300 * var7;
    float var15 = (var4 - this.m_minY) * 300 * var7;
    float var16 = (var5 + 1 - this.m_minX) * 300 * var7;
    float var17 = (var6 + 1 - this.m_minY) * 300 * var7;
            GL11.glBegin(7);
            GL11.glTexCoord2f(var10, var11);
            GL11.glVertex2f(var1 + var14, var2 + var15);
            GL11.glTexCoord2f(var12, var11);
            GL11.glVertex2f(var1 + var16, var2 + var15);
            GL11.glTexCoord2f(var12, var13);
            GL11.glVertex2f(var1 + var16, var2 + var17);
            GL11.glTexCoord2f(var10, var13);
            GL11.glVertex2f(var1 + var14, var2 + var17);
            GL11.glEnd();
            m_shaderProgram.End();
         }
      }
   }

    void renderGrid(float var1, float var2, int var3, int var4, int var5, int var6, float var7, float var8) {
      if (!(var8 < 11.0F)) {
         if (m_gridShaderProgram == nullptr) {
            m_gridShaderProgram = ShaderProgram.createShaderProgram("worldMapGrid", false, true);
         }

         if (m_gridShaderProgram.isCompiled()) {
            m_gridShaderProgram.Start();
    float var9 = var1 + (var3 * 300 - this.m_minX * 300) * var7;
    float var10 = var2 + (var4 * 300 - this.m_minY * 300) * var7;
    float var11 = var9 + (var5 - var3 + 1) * 300 * var7;
    float var12 = var10 + (var6 - var4 + 1) * 300 * var7;
    VBOLinesUV var13 = WorldMapRenderer.m_vboLinesUV;
            var13.setMode(1);
            var13.setLineWidth(0.5F);
            var13.startRun(this.m_textureID);
    float var14 = this.m_gridColor.r;
    float var15 = this.m_gridColor.g;
    float var16 = this.m_gridColor.b;
    float var17 = this.m_gridColor.a;
    uint8_t var18 = 1;
            if (var8 < 13.0F) {
               var18 = 8;
            } else if (var8 < 14.0F) {
               var18 = 4;
            } else if (var8 < 15.0F) {
               var18 = 2;
            }

            m_gridShaderProgram.setValue("UVOffset", this.m_vector2.set(0.5F / this.m_textureW, 0.0F));

            for (int var19 = var3 * 10; var19 <= (var5 + 1) * 10; var19 += var18) {
               var13.reserve(2);
               var13.addElement(
                  var1 + (var19 * 30 - this.m_minX * 300) * var7,
                  var10,
                  0.0F,
                  (float)(1 + var19 - this.m_minX * 10) / this.m_textureW,
                  1.0F / this.m_textureH,
                  var14,
                  var15,
                  var16,
                  var17
               );
               var13.addElement(
                  var1 + (var19 * 30 - this.m_minX * 300) * var7,
                  var12,
                  0.0F,
                  (float)(1 + var19 - this.m_minX * 10) / this.m_textureW,
                  (float)(1 + this.getHeightInCells() * 10) / this.m_textureH,
                  var14,
                  var15,
                  var16,
                  var17
               );
            }

            m_gridShaderProgram.setValue("UVOffset", this.m_vector2.set(0.0F, 0.5F / this.m_textureH));

            for (int var20 = var4 * 10; var20 <= (var6 + 1) * 10; var20 += var18) {
               var13.reserve(2);
               var13.addElement(
                  var9,
                  var2 + (var20 * 30 - this.m_minY * 300) * var7,
                  0.0F,
                  1.0F / this.m_textureW,
                  (float)(1 + var20 - this.m_minY * 10) / this.m_textureH,
                  var14,
                  var15,
                  var16,
                  var17
               );
               var13.addElement(
                  var11,
                  var2 + (var20 * 30 - this.m_minY * 300) * var7,
                  0.0F,
                  (float)(1 + this.getWidthInCells() * 10) / this.m_textureW,
                  (float)(1 + var20 - this.m_minY * 10) / this.m_textureH,
                  var14,
                  var15,
                  var16,
                  var17
               );
            }

            var13.flush();
            m_gridShaderProgram.End();
         }
      }
   }

    void destroy() {
      if (this.m_textureID != nullptr) {
         RenderThread.invokeOnRenderContext(this.m_textureID::destroy);
      }

      this.m_textureBuffer = nullptr;
      this.m_visited = nullptr;
   }

    void save(ByteBuffer var1) {
      var1.putInt(this.m_minX);
      var1.putInt(this.m_minY);
      var1.putInt(this.m_maxX);
      var1.putInt(this.m_maxY);
      var1.putInt(10);
      var1.put(this.m_visited);
   }

    void load(ByteBuffer var1, int var2) {
    int var3 = var1.getInt();
    int var4 = var1.getInt();
    int var5 = var1.getInt();
    int var6 = var1.getInt();
    int var7 = var1.getInt();
      if (var3 == this.m_minX && var4 == this.m_minY && var5 == this.m_maxX && var6 == this.m_maxY && var7 == 10) {
         var1.get(this.m_visited);
      } else {
         byte[] var8 = new byte[(var5 - var3 + 1) * var7 * (var6 - var4 + 1) * var7];
         var1.get(var8);
    int var9 = 300 / var7;
    int var10 = (var5 - var3 + 1) * var7;

         for (int var11 = var4 * var7; var11 <= var6 * var7; var11++) {
    int var12 = var11 - var4 * var7;

            for (int var13 = var3 * var7; var13 <= var5 * var7; var13++) {
    int var14 = var13 - var3 * var7;
               this.setFlags(var13 * var9, var11 * var9, var13 * var9 + var9 - 1, var11 * var9 + var9 - 1, var8[var14 + var12 * var10]);
            }
         }
      }
   }

    void save() {
    ByteBuffer var1 = SliceY.SliceBuffer;
      var1.clear();
      var1.putInt(195);
      this.save(var1);
    File var2 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("map_visited.bin"));

      try (
    FileOutputStream var3 = std::make_shared<FileOutputStream>(var2);
    BufferedOutputStream var4 = std::make_shared<BufferedOutputStream>(var3);
      ) {
         var4.write(var1.array(), 0, var1.position());
      }
   }

    void load() {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("map_visited.bin"));

      try (
    FileInputStream var2 = std::make_shared<FileInputStream>(var1);
    BufferedInputStream var3 = std::make_shared<BufferedInputStream>(var2);
      ) {
    ByteBuffer var4 = SliceY.SliceBuffer;
         var4.clear();
    int var5 = var3.read(var4.array());
         var4.limit(var5);
    int var6 = var4.getInt();
         this.load(var4, var6);
      } catch (FileNotFoundException var11) {
      }
   }

    void setFlags(int var1, int var2, int var3, int var4, int var5) {
      var1 -= this.m_minX * 300;
      var2 -= this.m_minY * 300;
      var3 -= this.m_minX * 300;
      var4 -= this.m_minY * 300;
    int var6 = this.getWidthInCells();
    int var7 = this.getHeightInCells();
      var1 = PZMath.clamp(var1, 0, var6 * 300 - 1);
      var2 = PZMath.clamp(var2, 0, var7 * 300 - 1);
      var3 = PZMath.clamp(var3, 0, var6 * 300 - 1);
      var4 = PZMath.clamp(var4, 0, var7 * 300 - 1);
      if (var1 != var3 && var2 != var4) {
    int var8 = var1 / 30;
    int var9 = var3 / 30;
    int var10 = var2 / 30;
    int var11 = var4 / 30;
         if (var3 % 30 == 0) {
            var9--;
         }

         if (var4 % 30 == 0) {
            var11--;
         }

    bool var12 = false;
    int var13 = var6 * 10;

         for (int var14 = var10; var14 <= var11; var14++) {
            for (int var15 = var8; var15 <= var9; var15++) {
    uint8_t var16 = this.m_visited[var15 + var14 * var13];
               if ((var16 & var5) != var5) {
                  this.m_visited[var15 + var14 * var13] = (byte)(var16 | var5);
                  var12 = true;
               }
            }
         }

         if (var12) {
            this.m_changed = true;
            this.m_changeX1 = PZMath.min(this.m_changeX1, var8);
            this.m_changeY1 = PZMath.min(this.m_changeY1, var10);
            this.m_changeX2 = PZMath.max(this.m_changeX2, var9);
            this.m_changeY2 = PZMath.max(this.m_changeY2, var11);
         }
      }
   }

    void clearFlags(int var1, int var2, int var3, int var4, int var5) {
      var1 -= this.m_minX * 300;
      var2 -= this.m_minY * 300;
      var3 -= this.m_minX * 300;
      var4 -= this.m_minY * 300;
    int var6 = this.getWidthInCells();
    int var7 = this.getHeightInCells();
      var1 = PZMath.clamp(var1, 0, var6 * 300 - 1);
      var2 = PZMath.clamp(var2, 0, var7 * 300 - 1);
      var3 = PZMath.clamp(var3, 0, var6 * 300 - 1);
      var4 = PZMath.clamp(var4, 0, var7 * 300 - 1);
      if (var1 != var3 && var2 != var4) {
    int var8 = var1 / 30;
    int var9 = var3 / 30;
    int var10 = var2 / 30;
    int var11 = var4 / 30;
         if (var3 % 30 == 0) {
            var9--;
         }

         if (var4 % 30 == 0) {
            var11--;
         }

    bool var12 = false;
    int var13 = var6 * 10;

         for (int var14 = var10; var14 <= var11; var14++) {
            for (int var15 = var8; var15 <= var9; var15++) {
    uint8_t var16 = this.m_visited[var15 + var14 * var13];
               if ((var16 & var5) != 0) {
                  this.m_visited[var15 + var14 * var13] = (byte)(var16 & ~var5);
                  var12 = true;
               }
            }
         }

         if (var12) {
            this.m_changed = true;
            this.m_changeX1 = PZMath.min(this.m_changeX1, var8);
            this.m_changeY1 = PZMath.min(this.m_changeY1, var10);
            this.m_changeX2 = PZMath.max(this.m_changeX2, var9);
            this.m_changeY2 = PZMath.max(this.m_changeY2, var11);
         }
      }
   }

    bool updateTextureData(ByteBuffer var1, int var2) {
      if (!this.m_changed) {
    return false;
      } else {
         this.m_changed = false;
    uint8_t var3 = 4;
    int var4 = this.getWidthInCells() * 10;

         for (int var5 = this.m_changeY1; var5 <= this.m_changeY2; var5++) {
            var1.position((1 + this.m_changeX1) * var3 + (1 + var5) * var2 * var3);

            for (int var6 = this.m_changeX1; var6 <= this.m_changeX2; var6++) {
    uint8_t var7 = this.m_visited[var6 + var5 * var4];
               var1.put((byte)((var7 & 2) != 0 ? 0 : -1));
               var1.put((byte)((var7 & 1) != 0 ? 0 : -1));
               var1.put((byte)-1);
               var1.put((byte)-1);
            }
         }

         var1.position(0);
         this.m_changeX1 = int.MAX_VALUE;
         this.m_changeY1 = int.MAX_VALUE;
         this.m_changeX2 = int.MIN_VALUE;
         this.m_changeY2 = int.MIN_VALUE;
    return true;
      }
   }

    void setUnvisitedRGBA(float var1, float var2, float var3, float var4) {
      this.m_color.init(var1, var2, var3, var4);
   }

    void setUnvisitedGridRGBA(float var1, float var2, float var3, float var4) {
      this.m_gridColor.init(var1, var2, var3, var4);
   }

    bool hasFlags(int var1, int var2, int var3, int var4, int var5, bool var6) {
      var1 -= this.m_minX * 300;
      var2 -= this.m_minY * 300;
      var3 -= this.m_minX * 300;
      var4 -= this.m_minY * 300;
    int var7 = this.getWidthInCells();
    int var8 = this.getHeightInCells();
      var1 = PZMath.clamp(var1, 0, var7 * 300 - 1);
      var2 = PZMath.clamp(var2, 0, var8 * 300 - 1);
      var3 = PZMath.clamp(var3, 0, var7 * 300 - 1);
      var4 = PZMath.clamp(var4, 0, var8 * 300 - 1);
      if (var1 != var3 && var2 != var4) {
    int var9 = var1 / 30;
    int var10 = var3 / 30;
    int var11 = var2 / 30;
    int var12 = var4 / 30;
         if (var3 % 30 == 0) {
            var10--;
         }

         if (var4 % 30 == 0) {
            var12--;
         }

    int var13 = var7 * 10;

         for (int var14 = var11; var14 <= var12; var14++) {
            for (int var15 = var9; var15 <= var10; var15++) {
    uint8_t var16 = this.m_visited[var15 + var14 * var13];
               if (var6) {
                  if ((var16 & var5) != 0) {
    return true;
                  }
               } else if ((var16 & var5) != var5) {
    return false;
               }
            }
         }

         return !var6;
      } else {
    return false;
      }
   }

    bool isCellVisible(int var1, int var2) {
      return this.hasFlags(var1 * 300, var2 * 300, (var1 + 1) * 300, (var2 + 1) * 300, 3, true);
   }

    static WorldMapVisited getInstance() {
    IsoMetaGrid var0 = IsoWorld.instance.getMetaGrid();
      if (var0 == nullptr) {
         throw NullPointerException("IsoWorld.instance.MetaGrid is nullptr");
      } else {
         if (instance == nullptr) {
            instance = std::make_unique<WorldMapVisited>();
            instance.setBounds(var0.getMinX(), var0.getMinY(), var0.getMaxX(), var0.getMaxY());

            try {
               instance.load();
               if (SandboxOptions.getInstance().Map.MapAllKnown.getValue()) {
                  instance.setKnownInCells(var0.getMinX(), var0.getMinY(), var0.getMaxX(), var0.getMaxY());
               }
            } catch (Throwable var2) {
               ExceptionLogger.logException(var2);
            }
         }

    return instance;
      }
   }

    static void update() {
      if (IsoWorld.instance != nullptr) {
    WorldMapVisited var0 = getInstance();
         if (var0 != nullptr) {
            for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
    IsoPlayer var2 = IsoPlayer.players[var1];
               if (var2 != nullptr && !var2.isDead()) {
    uint8_t var3 = 25;
    int var4 = ((int)var2.x - var3) / 30;
    int var5 = ((int)var2.y - var3) / 30;
    int var6 = ((int)var2.x + var3) / 30;
    int var7 = ((int)var2.y + var3) / 30;
                  if (((int)var2.x + var3) % 30 == 0) {
                     var6--;
                  }

                  if (((int)var2.y + var3) % 30 == 0) {
                     var7--;
                  }

                  if (var4 != var0.m_updateMinX[var1] || var5 != var0.m_updateMinY[var1] || var6 != var0.m_updateMaxX[var1] || var7 != var0.m_updateMaxY[var1]) {
                     var0.m_updateMinX[var1] = var4;
                     var0.m_updateMinY[var1] = var5;
                     var0.m_updateMaxX[var1] = var6;
                     var0.m_updateMaxY[var1] = var7;
                     var0.setFlags((int)var2.x - var3, (int)var2.y - var3, (int)var2.x + var3, (int)var2.y + var3, 3);
                  }
               }
            }
         }
      }
   }

    void forget() {
      this.clearKnownInCells(this.m_minX, this.m_minY, this.m_maxX, this.m_maxY);
      this.clearVisitedInCells(this.m_minX, this.m_minY, this.m_maxX, this.m_maxY);
      Arrays.fill(this.m_updateMinX, -1);
      Arrays.fill(this.m_updateMinY, -1);
      Arrays.fill(this.m_updateMaxX, -1);
      Arrays.fill(this.m_updateMaxY, -1);
   }

    static void SaveAll() {
    WorldMapVisited var0 = instance;
      if (var0 != nullptr) {
         try {
            var0.save();
         } catch (Exception var2) {
            ExceptionLogger.logException(var2);
         }
      }
   }

    static void Reset() {
    WorldMapVisited var0 = instance;
      if (var0 != nullptr) {
         var0.destroy();
         instance = nullptr;
      }
   }
}
} // namespace worldMap
} // namespace zombie
