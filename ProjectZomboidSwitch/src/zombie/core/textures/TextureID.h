#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include <GL/glew.h>
#include "zombie/core/utils/BufferUtils.h"
#include "zombie/IndieGL.h"
#include "zombie/SystemDisabler.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/Asset/State.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/textures/Texture/PZFileformat.h"
#include "zombie/core/textures/TextureID/TextureIDAssetParams.h"
#include "zombie/core/utils/BooleanGrid.h"
#include "zombie/core/utils/DirectBufferAllocator.h"
#include "zombie/core/utils/WrappedBuffer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/interfaces/IDestroyable.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace textures {


class TextureID : public Asset {
public:
    static const long serialVersionUID = 4409253583065563738L;
    static long totalGraphicMemory = 0L;
    static bool UseFiltering = false;
    static bool bUseCompression = true;
    static bool bUseCompressionOption = true;
    static float totalMemUsed = 0.0F;
    static bool FREE_MEMORY = true;
   private static const std::unordered_map<int, std::string> TextureIDMap = std::make_unique<std::unordered_map<>>();
    std::string pathFileName;
    bool solid;
    int width;
    int widthHW;
    int height;
    int heightHW;
   protected transient ImageData data;
   protected transient int id = -1;
    int m_glMagFilter = -1;
    int m_glMinFilter = -1;
   std::vector<AlphaColorIndex> alphaList;
    int referenceCount = 0;
    BooleanGrid mask;
    int flags = 0;
    TextureIDAssetParams assetParams;
   static const IntBuffer deleteTextureIDS = BufferUtils::createIntBuffer(20);
    static const AssetType ASSET_TYPE = std::make_shared<AssetType>("TextureID");

    public TextureID(AssetPath var1, AssetManager var2, TextureIDAssetParams var3) {
      super(var1, var2);
      this.assetParams = var3;
      this.flags = var3 == nullptr ? 0 : this.assetParams.flags;
   }

    protected TextureID() {
      super(nullptr, TextureIDAssetManager.instance);
      this.assetParams = nullptr;
      this.onCreated(State.READY);
   }

    public TextureID(int var1, int var2, int var3) {
      super(nullptr, TextureIDAssetManager.instance);
      this.assetParams = std::make_unique<TextureIDAssetParams>();
      this.assetParams.flags = var3;
      if ((var3 & 16) != 0) {
         if ((var3 & 4) != 0) {
            DebugLog.General.warn("FBO incompatible with COMPRESS");
            this.assetParams.flags &= -5;
         }

         this.data = std::make_shared<ImageData>(var1, var2, nullptr);
      } else {
         this.data = std::make_shared<ImageData>(var1, var2);
      }

      this.width = this.data.getWidth();
      this.height = this.data.getHeight();
      this.widthHW = this.data.getWidthHW();
      this.heightHW = this.data.getHeightHW();
      this.solid = this.data.isSolid();
      RenderThread.queueInvokeOnRenderContext(() -> this.createTexture(false));
      this.onCreated(State.READY);
   }

    public TextureID(ImageData var1) {
      super(nullptr, TextureIDAssetManager.instance);
      this.assetParams = nullptr;
      this.data = var1;
      RenderThread.invokeOnRenderContext(this::createTexture);
      this.onCreated(State.READY);
   }

    public TextureID(const std::string& var1, const std::string& var2) {
      super(nullptr, TextureIDAssetManager.instance);
      this.assetParams = nullptr;
      this.data = std::make_shared<ImageData>(var1, var2);
      this.pathFileName = var1;
      RenderThread.invokeOnRenderContext(this::createTexture);
      this.onCreated(State.READY);
   }

    public TextureID(const std::string& var1, int[] var2) {
      super(nullptr, TextureIDAssetManager.instance);
      this.assetParams = nullptr;
      this.data = std::make_shared<ImageData>(var1, var2);
      this.pathFileName = var1;
      RenderThread.invokeOnRenderContext(this::createTexture);
      this.onCreated(State.READY);
   }

    public TextureID(const std::string& var1, int var2, int var3, int var4) {
      super(nullptr, TextureIDAssetManager.instance);
      this.assetParams = nullptr;
      if (var1.startsWith("/")) {
         var1 = var1.substr(1);
      }

    int var5;
      while ((var5 = var1.indexOf("\\")) != -1) {
         var1 = var1.substr(0, var5) + "/" + var1.substr(var5 + 1);
      }

      (this.data = std::make_shared<ImageData>(var1)).makeTransp((byte)var2, (byte)var3, (byte)var4);
      if (this.alphaList == nullptr) {
         this.alphaList = std::make_unique<std::vector<>>();
      }

      this.alphaList.push_back(std::make_shared<AlphaColorIndex>(var2, var3, var4, 0));
      this.pathFileName = var1;
      RenderThread.invokeOnRenderContext(this::createTexture);
      this.onCreated(State.READY);
   }

    public TextureID(const std::string& var1) {
      super(nullptr, TextureIDAssetManager.instance);
      this.assetParams = nullptr;
      if (var1.toLowerCase().contains(".pcx")) {
         this.data = std::make_shared<ImageData>(var1, var1);
      } else {
         this.data = std::make_shared<ImageData>(var1);
      }

      if (this.data.getHeight() != -1) {
         this.pathFileName = var1;
         RenderThread.invokeOnRenderContext(this::createTexture);
         this.onCreated(State.READY);
      }
   }

    public TextureID(BufferedInputStream var1, const std::string& var2, bool var3, PZFileformat var4) {
      super(nullptr, TextureIDAssetManager.instance);
      this.assetParams = nullptr;
      this.data = std::make_shared<ImageData>(var1, var3, var4);
      if (this.data.id != -1) {
         this.id = this.data.id;
         this.width = this.data.getWidth();
         this.height = this.data.getHeight();
         this.widthHW = this.data.getWidthHW();
         this.heightHW = this.data.getHeightHW();
         this.solid = this.data.isSolid();
      } else {
         if (var3) {
            this.mask = this.data.mask;
            this.data.mask = nullptr;
         }

         this.createTexture();
      }

      this.pathFileName = var2;
      this.onCreated(State.READY);
   }

    public TextureID(BufferedInputStream var1, const std::string& var2, bool var3) {
      super(nullptr, TextureIDAssetManager.instance);
      this.assetParams = nullptr;
      this.data = std::make_shared<ImageData>(var1, var3);
      if (var3) {
         this.mask = this.data.mask;
         this.data.mask = nullptr;
      }

      this.pathFileName = var2;
      RenderThread.invokeOnRenderContext(this::createTexture);
      this.onCreated(State.READY);
   }

    static TextureID createSteamAvatar(long var0) {
    ImageData var2 = ImageData.createSteamAvatar(var0);
    return var2 = = nullptr ? nullptr : std::make_shared<TextureID>(var2);
   }

    int getID() {
      return this.id;
   }

    bool bind() {
      if (this.id == -1 && this.data == nullptr) {
         Texture.getErrorTexture().bind();
    return true;
      } else {
         this.debugBoundTexture();
         return this.id != -1 && this.id == Texture.lastTextureID ? false : this.bindalways();
      }
   }

    bool bindalways() {
      this.bindInternal();
    return true;
   }

    void bindInternal() {
      if (this.id == -1) {
         this.generateHwId(this.data != nullptr && this.data.data != nullptr);
      }

      this.assignFilteringFlags();
      Texture.lastlastTextureID = Texture.lastTextureID;
      Texture.lastTextureID = this.id;
      Texture.BindCount++;
   }

    void debugBoundTexture() {
      if (DebugOptions.instance.Checks.BoundTextures.getValue() && Texture.lastTextureID != -1) {
    int var1 = GL11.glGetInteger(34016);
         if (var1 == 33984) {
    int var2 = GL11.glGetInteger(32873);
            if (var2 != Texture.lastTextureID) {
    std::string var3 = nullptr;

               for (Asset var5 : TextureIDAssetManager.instance.getAssetTable().values()) {
    TextureID var6 = (TextureID)var5;
                  if (var6.id == Texture.lastTextureID) {
                     var3 = var6.getPath().getPath();
                     break;
                  }
               }

               DebugLog.General.error("Texture.lastTextureID %d != GL_TEXTURE_BINDING_2D %d name=%s", new Object[]{Texture.lastTextureID, var2, var3});
            }
         }
      }
   }

    void destroy() {
      assert Thread.currentThread() == RenderThread.RenderThread;

      if (this.id != -1) {
         if (deleteTextureIDS.position() == deleteTextureIDS.capacity()) {
            deleteTextureIDS.flip();
            GL11.glDeleteTextures(deleteTextureIDS);
            deleteTextureIDS.clear();
         }

         deleteTextureIDS.put(this.id);
         this.id = -1;
      }
   }

    void freeMemory() {
      this.data = nullptr;
   }

    WrappedBuffer getData() {
      this.bind();
    WrappedBuffer var1 = DirectBufferAllocator.allocate(this.heightHW * this.widthHW * 4);
      GL11.glGetTexImage(3553, 0, 6408, 5121, var1.getBuffer());
      Texture.lastTextureID = 0;
      GL11.glBindTexture(3553, 0);
    return var1;
   }

    void setData(ByteBuffer var1) {
      if (var1 == nullptr) {
         this.freeMemory();
      } else {
         this.bind();
         GL11.glTexSubImage2D(3553, 0, 0, 0, this.widthHW, this.heightHW, 6408, 5121, var1);
         if (this.data != nullptr) {
    MipMapLevel var2 = this.data.getData();
    ByteBuffer var3 = var2.getBuffer();
            var1.flip();
            var3.clear();
            var3.put(var1);
            var3.flip();
         }
      }
   }

    ImageData getImageData() {
      return this.data;
   }

    void setImageData(ImageData var1) {
      var1 = this.limitMaxSize(var1);
      this.data = var1;
      this.width = var1.getWidth();
      this.height = var1.getHeight();
      this.widthHW = var1.getWidthHW();
      this.heightHW = var1.getHeightHW();
      if (var1.mask != nullptr) {
         this.mask = var1.mask;
         var1.mask = nullptr;
      }

      RenderThread.queueInvokeOnRenderContext(this::createTexture);
   }

    ImageData limitMaxSize(ImageData var1) {
      if (this.assetParams == nullptr) {
    return var1;
      } else {
    int var2 = this.assetParams.flags;
    short var3 = 384;
         if ((var2 & var3) == 0) {
    return var1;
         } else {
    int var4 = Core.getInstance().getMaxTextureSizeFromFlags(var2);
            if (var1.getWidth() <= var4 && var1.getHeight() <= var4) {
    return var1;
            } else {
               var1.bPreserveTransparentColor = true;
    MipMapLevel var5 = var1.getData();
    int var6 = 0;

               while (var5.width > var4 || var5.height > var4) {
                  var5 = var1.getMipMapData(++var6);
               }

    WrappedBuffer var7 = DirectBufferAllocator.allocate(var5.getBuffer().capacity());
               var5.getBuffer().rewind();
               var7.getBuffer().put(var5.getBuffer());
               var7.getBuffer().rewind();
    ImageData var8 = std::make_shared<ImageData>(var1.getWidth() >> var6, var1.getHeight() >> var6, var7);
               var8.alphaPaddingDone = true;
               if (FREE_MEMORY) {
                  var1.dispose();
               }

    return var8;
            }
         }
      }
   }

    std::string getPathFileName() {
      return this.pathFileName;
   }

    bool isDestroyed() {
      return this.id == -1;
   }

    bool isSolid() {
      return this.solid;
   }

    void createTexture() {
      if (this.data != nullptr) {
         this.createTexture(true);
      }
   }

    void createTexture(bool var1) {
      if (this.id == -1) {
         this.width = this.data.getWidth();
         this.height = this.data.getHeight();
         this.widthHW = this.data.getWidthHW();
         this.heightHW = this.data.getHeightHW();
         this.solid = this.data.isSolid();
         this.generateHwId(var1);
      }
   }

    void generateHwId(bool var1) {
      this.id = GL11.glGenTextures();
      Texture.totalTextureID++;
      GL11.glBindTexture(3553, Texture.lastTextureID = this.id);
      SpriteRenderer.ringBuffer.restoreBoundTextures = true;
    int var2;
      if (this.assetParams == nullptr) {
         var2 = bUseCompressionOption ? 4 : 0;
      } else {
         var2 = this.assetParams.flags;
      }

    bool var3 = (var2 & 1) != 0;
    bool var4 = (var2 & 2) != 0;
    bool var5 = (var2 & 16) != 0;
    bool var6 = (var2 & 64) != 0 && !var5 && var1;
    bool var7 = (var2 & 4) != 0;
    char var8;
      if (var7 && GL.getCapabilities().GL_ARB_texture_compression) {
         var8 = '蓮';
      } else {
         var8 = 6408;
      }

      this.m_glMagFilter = var4 ? 9728 : 9729;
      this.m_glMinFilter = var6 ? 9987 : (var3 ? 9728 : 9729);
      GL11.glTexParameteri(3553, 10241, this.m_glMinFilter);
      GL11.glTexParameteri(3553, 10240, this.m_glMagFilter);
      if ((var2 & 32) != 0) {
         GL11.glTexParameteri(3553, 10242, 33071);
         GL11.glTexParameteri(3553, 10243, 33071);
      } else {
         GL11.glTexParameteri(3553, 10242, 10497);
         GL11.glTexParameteri(3553, 10243, 10497);
      }

      if (var1) {
         if (var6) {
            PZGLUtil.checkGLErrorThrow("TextureID.mipMaps.start", new Object[0]);
    int var9 = this.data.getMipMapCount();
    int var10 = PZMath.min(0, var9 - 1);
    int var11 = var9;

            for (int var12 = var10; var12 < var11; var12++) {
    MipMapLevel var13 = this.data.getMipMapData(var12);
    int var14 = var13.width;
    int var15 = var13.height;
               totalMemUsed = totalMemUsed + var13.getDataSize();
               GL11.glTexImage2D(3553, var12 - var10, var8, var14, var15, 0, 6408, 5121, var13.getBuffer());
               PZGLUtil.checkGLErrorThrow("TextureID.mipMaps[%d].end", new Object[]{var12});
            }

            PZGLUtil.checkGLErrorThrow("TextureID.mipMaps.end", new Object[0]);
         } else {
            PZGLUtil.checkGLErrorThrow("TextureID.noMips.start", new Object[0]);
            totalMemUsed = totalMemUsed + this.widthHW * this.heightHW * 4;
            GL11.glTexImage2D(3553, 0, var8, this.widthHW, this.heightHW, 0, 6408, 5121, this.data.getData().getBuffer());
            PZGLUtil.checkGLErrorThrow("TextureID.noMips.end", new Object[0]);
         }
      } else {
         GL11.glTexImage2D(3553, 0, var8, this.widthHW, this.heightHW, 0, 6408, 5121, (ByteBuffer)nullptr);
         totalMemUsed = totalMemUsed + this.widthHW * this.heightHW * 4;
      }

      if (FREE_MEMORY) {
         if (this.data != nullptr) {
            this.data.dispose();
         }

         this.data = nullptr;
         if (this.assetParams != nullptr) {
            this.assetParams.subTexture = nullptr;
            this.assetParams = nullptr;
         }
      }

      TextureIDMap.put(this.id, this.pathFileName);
      if (SystemDisabler.doEnableDetectOpenGLErrorsInTexture) {
         PZGLUtil.checkGLErrorThrow("generateHwId id:%d pathFileName:%s", new Object[]{this.id, this.pathFileName});
      }
   }

    void assignFilteringFlags() {
      GL11.glBindTexture(3553, this.id);
      if (this.width == 1 && this.height == 1) {
         GL11.glTexParameteri(3553, 10241, 9728);
         GL11.glTexParameteri(3553, 10240, 9728);
      } else {
         GL11.glTexParameteri(3553, 10241, this.m_glMinFilter);
         GL11.glTexParameteri(3553, 10240, this.m_glMagFilter);
         if ((this.flags & 64) != 0
            && DebugOptions.instance.IsoSprite.NearestMagFilterAtMinZoom.getValue()
            && this.isMinZoomLevel()
            && this.m_glMagFilter != 9728) {
            GL11.glTexParameteri(3553, 10240, 9728);
         }

         if (DebugOptions.instance.IsoSprite.ForceLinearMagFilter.getValue() && this.m_glMagFilter != 9729) {
            GL11.glTexParameteri(3553, 10240, 9729);
         }

         if (DebugOptions.instance.IsoSprite.ForceNearestMagFilter.getValue() && this.m_glMagFilter != 9728) {
            GL11.glTexParameteri(3553, 10240, 9728);
         }

         if (DebugOptions.instance.IsoSprite.ForceNearestMipMapping.getValue() && this.m_glMinFilter == 9987) {
            GL11.glTexParameteri(3553, 10241, 9986);
         }

         if (DebugOptions.instance.IsoSprite.TextureWrapClampToEdge.getValue()) {
            GL11.glTexParameteri(3553, 10242, 33071);
            GL11.glTexParameteri(3553, 10243, 33071);
         }

         if (DebugOptions.instance.IsoSprite.TextureWrapRepeat.getValue()) {
            GL11.glTexParameteri(3553, 10242, 10497);
            GL11.glTexParameteri(3553, 10243, 10497);
         }

         if (SystemDisabler.doEnableDetectOpenGLErrorsInTexture) {
            PZGLUtil.checkGLErrorThrow("assignFilteringFlags id:%d pathFileName:%s", new Object[]{this.id, this.pathFileName});
         }
      }
   }

    void setMagFilter(int var1) {
      this.m_glMagFilter = var1;
   }

    void setMinFilter(int var1) {
      this.m_glMinFilter = var1;
   }

    bool hasMipMaps() {
      return this.m_glMinFilter == 9987;
   }

    bool isMaxZoomLevel() {
      return IndieGL.isMaxZoomLevel();
   }

    bool isMinZoomLevel() {
      return IndieGL.isMinZoomLevel();
   }

    void setAssetParams(AssetParams var1) {
      this.assetParams = (TextureIDAssetParams)var1;
      this.flags = this.assetParams == nullptr ? 0 : this.assetParams.flags;
   }

    AssetType getType() {
    return ASSET_TYPE;
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
