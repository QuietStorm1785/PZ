#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/imageio/ImageIO.h"
#include <GL/glew.h>
#include "org/lwjgl/system/MemoryUtil.h"
#include "zombie/GameWindow.h"
#include "zombie/IndieGL.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/Asset/State.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/bucket/BucketManager.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/textures/Texture/PZFileformat.h"
#include "zombie/core/textures/Texture/TextureAssetParams.h"
#include "zombie/core/textures/TextureID/TextureIDAssetParams.h"
#include "zombie/core/utils/BooleanGrid.h"
#include "zombie/core/utils/ImageUtils.h"
#include "zombie/core/utils/WrappedBuffer.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileSystem/SubTexture.h"
#include "zombie/interfaces/IDestroyable.h"
#include "zombie/interfaces/ITexture.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/ObjectRenderEffects.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace textures {


class Texture : public Asset {
public:
   public static const std::unordered_set<std::string> nullTextures = std::make_unique<std::unordered_set<>>();
    static const long serialVersionUID = 7472363451408935314L;
    static const ObjectRenderEffects objRen = ObjectRenderEffects.alloc();
    static int BindCount = 0;
    static bool bDoingQuad = false;
    static float lr;
    static float lg;
    static float lb;
    static float la;
    static int lastlastTextureID = -2;
    static int totalTextureID = 0;
    static Texture white = nullptr;
    static Texture errorTexture = nullptr;
    static Texture mipmap = nullptr;
    static int lastTextureID = -1;
    static bool WarnFailFindTexture = true;
   private static const std::unordered_map<std::string, Texture> textures = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, Texture> s_sharedTextureTable = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<int64_t, Texture> steamAvatarMap = std::make_unique<std::unordered_map<>>();
    bool flip = false;
    float offsetX = 0.0F;
    float offsetY = 0.0F;
    bool bindAlways = false;
    float xEnd = 1.0F;
    float yEnd = 1.0F;
    float xStart = 0.0F;
    float yStart = 0.0F;
    TextureID dataid;
    Mask mask;
    std::string name;
    bool solid;
    int width;
    int height;
    int heightOrig;
    int widthOrig;
    int realWidth = 0;
    int realHeight = 0;
    bool destroyed = false;
    Texture splitIconTex;
    int splitX = -1;
    int splitY;
    int splitW;
    int splitH;
    SubTexture subTexture;
    TextureAssetParams assetParams;
   private static const ThreadLocal<PNGSize> pngSize = ThreadLocal.withInitial(PNGSize::new);
    static const AssetType ASSET_TYPE = std::make_shared<AssetType>("Texture");

    public Texture(AssetPath var1, AssetManager var2, TextureAssetParams var3) {
      super(var1, var2);
      this.assetParams = var3;
      this.name = var1 == nullptr ? nullptr : var1.getPath();
      if (var3 != nullptr && var3.subTexture != nullptr) {
    SubTexture var4 = var3.subTexture;
         this.splitX = var4.m_info.x;
         this.splitY = var4.m_info.y;
         this.splitW = var4.m_info.w;
         this.splitH = var4.m_info.h;
         this.width = this.splitW;
         this.height = this.splitH;
         this.offsetX = var4.m_info.ox;
         this.offsetY = var4.m_info.oy;
         this.widthOrig = var4.m_info.fx;
         this.heightOrig = var4.m_info.fy;
         this.name = var4.m_info.name;
         this.subTexture = var4;
      }

    TextureIDAssetParams var9 = std::make_shared<TextureIDAssetParams>();
      if (this.assetParams != nullptr && this.assetParams.subTexture != nullptr) {
         var9.subTexture = this.assetParams.subTexture;
    std::string var5 = var9.subTexture.m_pack_name;
    std::string var6 = var9.subTexture.m_page_name;
    FileSystem var7 = this.getAssetManager().getOwner().getFileSystem();
         var9.flags = var7.getTexturePackFlags(var5);
         var9.flags = var9.flags | (var7.getTexturePackAlpha(var5, var6) ? 8 : 0);
    AssetPath var8 = std::make_shared<AssetPath>("@pack@/" + var5 + "/" + var6);
         this.dataid = (TextureID)TextureIDAssetManager.instance.load(var8, var9);
      } else {
         if (this.assetParams == nullptr) {
            var9.flags = var9.flags | (TextureID.bUseCompressionOption ? 4 : 0);
         } else {
            var9.flags = this.assetParams.flags;
         }

         this.dataid = (TextureID)this.getAssetManager().getOwner().get(TextureID.ASSET_TYPE).load(this.getPath(), var9);
      }

      this.onCreated(State.EMPTY);
      if (this.dataid != nullptr) {
         this.addDependency(this.dataid);
      }
   }

    public Texture(TextureID var1, const std::string& var2) {
      super(nullptr, TextureAssetManager.instance);
      this.dataid = var1;
      this.dataid.referenceCount++;
      if (var1.isReady()) {
         this.solid = this.dataid.solid;
         this.width = var1.width;
         this.height = var1.height;
         this.xEnd = (float)this.width / var1.widthHW;
         this.yEnd = (float)this.height / var1.heightHW;
      } else {
    assert false;
      }

      this.name = var2;
      this.assetParams = nullptr;
      this.onCreated(var1.getState());
      this.addDependency(var1);
   }

    public Texture(const std::string& var1) {
      this(std::make_shared<TextureID>(var1), var1);
      this.setUseAlphaChannel(true);
   }

    public Texture(const std::string& var1, BufferedInputStream var2, bool var3, PZFileformat var4) {
      this(std::make_shared<TextureID>(var2, var1, var3, var4), var1);
      if (var3 && this.dataid.mask != nullptr) {
         this.createMask(this.dataid.mask);
         this.dataid.mask = nullptr;
         this.dataid.data = nullptr;
      }
   }

    public Texture(const std::string& var1, BufferedInputStream var2, bool var3) {
      this(std::make_shared<TextureID>(var2, var1, var3), var1);
      if (var3) {
         this.createMask(this.dataid.mask);
         this.dataid.mask = nullptr;
         this.dataid.data = nullptr;
      }
   }

    public Texture(const std::string& var1, bool var2, bool var3) {
      this(std::make_shared<TextureID>(var1), var1);
      this.setUseAlphaChannel(var3);
      if (var2) {
         this.dataid.data = nullptr;
      }
   }

    public Texture(const std::string& var1, const std::string& var2) {
      this(std::make_shared<TextureID>(var1, var2), var1);
      this.setUseAlphaChannel(true);
   }

    public Texture(const std::string& var1, int[] var2) {
      this(std::make_shared<TextureID>(var1, var2), var1);
      if (var1.contains("drag")) {
    bool var3 = false;
      }

      this.setUseAlphaChannel(true);
   }

    public Texture(const std::string& var1, bool var2) {
      this(std::make_shared<TextureID>(var1), var1);
      this.setUseAlphaChannel(var2);
   }

    public Texture(int var1, int var2, const std::string& var3, int var4) {
      this(std::make_shared<TextureID>(var1, var2, var4), var3);
   }

    public Texture(int var1, int var2, int var3) {
      this(std::make_shared<TextureID>(var1, var2, var3), nullptr);
   }

    public Texture(const std::string& var1, int var2, int var3, int var4) {
      this(std::make_shared<TextureID>(var1, var2, var3, var4), var1);
   }

    public Texture(Texture var1) {
      this(var1.dataid, var1.name + "(copy)");
      this.width = var1.width;
      this.height = var1.height;
      this.name = var1.name;
      this.xStart = var1.xStart;
      this.yStart = var1.yStart;
      this.xEnd = var1.xEnd;
      this.yEnd = var1.yEnd;
      this.solid = var1.solid;
   }

    public Texture() {
      super(nullptr, TextureAssetManager.instance);
      this.assetParams = nullptr;
      this.onCreated(State.EMPTY);
   }

    static std::string processFilePath(const std::string& var0) {
      return var0.replaceAll("\\\\", "/");
   }

    static void bindNone() {
      IndieGL.glDisable(3553);
      lastTextureID = -1;
      BindCount--;
   }

    static Texture getWhite() {
      if (white == nullptr) {
         white = std::make_shared<Texture>(32, 32, "white", 0);
         RenderThread.invokeOnRenderContext(() -> {
            GL11.glBindTexture(3553, lastTextureID = white.getID());
            GL11.glTexParameteri(3553, 10241, 9728);
            GL11.glTexParameteri(3553, 10240, 9728);
    ByteBuffer var0 = MemoryUtil.memAlloc(white.width * white.height * 4);

            for (int var1 = 0; var1 < white.width * white.height * 4; var1++) {
               var0.put((byte)-1);
            }

            var0.flip();
            GL11.glTexImage2D(3553, 0, 6408, white.width, white.height, 0, 6408, 5121, var0);
            MemoryUtil.memFree(var0);
         });
         s_sharedTextureTable.put("white.png", white);
         s_sharedTextureTable.put("media/white.png", white);
         s_sharedTextureTable.put("media/ui/white.png", white);
      }

    return white;
   }

    static Texture getErrorTexture() {
      if (errorTexture == nullptr) {
         errorTexture = std::make_shared<Texture>(32, 32, "EngineErrorTexture", 0);
         RenderThread.invokeOnRenderContext(() -> {
            GL11.glBindTexture(3553, lastTextureID = errorTexture.getID());
            GL11.glTexParameteri(3553, 10241, 9728);
            GL11.glTexParameteri(3553, 10240, 9728);
    uint8_t var0 = 4;
    ByteBuffer var1 = MemoryUtil.memAlloc(errorTexture.width * errorTexture.height * var0);
            var1.position(errorTexture.width * errorTexture.height * var0);
    int var2 = errorTexture.width * var0;
    bool var3 = true;
    bool var4 = var3;
    uint8_t var5 = 8;
    int var6 = errorTexture.width / var5;

            for (int var7 = 0; var7 < var5 * var5; var7++) {
    int var8 = var7 / var5;
    int var9 = var7 % var5;
               if (var8 > 0 && var9 == 0) {
                  var3 = !var3;
                  var4 = var3;
               }

    int var10 = var4 ? -16776961 : -1;
               var4 = !var4;

               for (int var11 = 0; var11 < var6; var11++) {
                  for (int var12 = 0; var12 < var6; var12++) {
                     var1.putInt((var8 * var6 + var11) * var2 + (var9 * var6 + var12) * var0, var10);
                  }
               }
            }

            var1.flip();
            GL11.glTexImage2D(3553, 0, 6408, errorTexture.width, errorTexture.height, 0, 6408, 5121, var1);
            MemoryUtil.memFree(var1);
         });
         s_sharedTextureTable.put("EngineErrorTexture.png", errorTexture);
      }

    return errorTexture;
   }

    static void initEngineMipmapTextureLevel(int var0, int var1, int var2, int var3, int var4, int var5, int var6) {
    ByteBuffer var7 = MemoryUtil.memAlloc(var1 * var2 * 4);
      MemoryUtil.memSet(var7, 255);

      for (int var8 = 0; var8 < var1 * var2; var8++) {
         var7.put((byte)(var3 & 0xFF));
         var7.put((byte)(var4 & 0xFF));
         var7.put((byte)(var5 & 0xFF));
         var7.put((byte)(var6 & 0xFF));
      }

      var7.flip();
      GL11.glTexImage2D(3553, var0, 6408, var1, var2, 0, 6408, 5121, var7);
      MemoryUtil.memFree(var7);
   }

    static Texture getEngineMipmapTexture() {
      if (mipmap == nullptr) {
         mipmap = std::make_shared<Texture>(256, 256, "EngineMipmapTexture", 0);
         mipmap.dataid.setMinFilter(9984);
         RenderThread.invokeOnRenderContext(() -> {
            GL11.glBindTexture(3553, lastTextureID = mipmap.getID());
            GL11.glTexParameteri(3553, 10241, 9984);
            GL11.glTexParameteri(3553, 10240, 9728);
            GL11.glTexParameteri(3553, 33085, 6);
            initEngineMipmapTextureLevel(0, mipmap.width, mipmap.height, 255, 0, 0, 255);
            initEngineMipmapTextureLevel(1, mipmap.width / 2, mipmap.height / 2, 0, 255, 0, 255);
            initEngineMipmapTextureLevel(2, mipmap.width / 4, mipmap.height / 4, 0, 0, 255, 255);
            initEngineMipmapTextureLevel(3, mipmap.width / 8, mipmap.height / 8, 255, 255, 0, 255);
            initEngineMipmapTextureLevel(4, mipmap.width / 16, mipmap.height / 16, 255, 0, 255, 255);
            initEngineMipmapTextureLevel(5, mipmap.width / 32, mipmap.height / 32, 0, 0, 0, 255);
            initEngineMipmapTextureLevel(6, mipmap.width / 64, mipmap.height / 64, 255, 255, 255, 255);
         });
      }

    return mipmap;
   }

    static void clearTextures() {
      textures.clear();
   }

    static Texture getSharedTexture(const std::string& var0) {
    int var1 = 0;
      var1 |= TextureID.bUseCompression ? 4 : 0;
    return getSharedTexture();
   }

    static Texture getSharedTexture(const std::string& var0, int var1) {
      if (GameServer.bServer && !ServerGUI.isCreated()) {
    return nullptr;
      } else {
         try {
    return getSharedTextureInternal();
         } catch (Exception var3) {
    return nullptr;
         }
      }
   }

    static Texture trygetTexture(const std::string& var0) {
      if (GameServer.bServer && !ServerGUI.isCreated()) {
    return nullptr;
      } else {
    Texture var1 = getSharedTexture(var0);
         if (var1 == nullptr) {
    std::string var2 = "media/textures/" + var0;
            if (!var0.endsWith(".png")) {
               var2 = var2 + ".png";
            }

            var1 = s_sharedTextureTable.get(var2);
            if (var1 != nullptr) {
    return var1;
            }

    std::string var3 = ZomboidFileSystem.instance.getString(var2);
            if (!var3 == var2)) {
    int var4 = 0;
               var4 |= TextureID.bUseCompression ? 4 : 0;
    TextureAssetParams var5 = std::make_shared<TextureAssetParams>();
               var5.flags = var4;
               var1 = (Texture)TextureAssetManager.instance.load(std::make_shared<AssetPath>(var3), var5);
               BucketManager.Shared().AddTexture(var2, var1);
               setSharedTextureInternal(var2, var1);
            }
         }

    return var1;
      }
   }

    static void onTextureFileChanged(const std::string& var0) {
      DebugLog.General.println("Texture.onTextureFileChanged> " + var0);
   }

    static void onTexturePacksChanged() {
      nullTextures.clear();
      s_sharedTextureTable.clear();
   }

    static void setSharedTextureInternal(const std::string& var0, Texture var1) {
      s_sharedTextureTable.put(var0, var1);
   }

    static Texture getSharedTextureInternal(const std::string& var0, int var1) {
      if (GameServer.bServer && !ServerGUI.isCreated()) {
    return nullptr;
      } else if (nullTextures.contains(var0)) {
    return nullptr;
      } else {
    Texture var2 = s_sharedTextureTable.get(var0);
         if (var2 != nullptr) {
    return var2;
         } else {
            if (!var0.endsWith(".txt")) {
    std::string var3 = var0;
               if (var0.endsWith(".pcx") || var0.endsWith(".png")) {
                  var3 = var0.substr(0, var0.lastIndexOf("."));
               }

               var3 = var3.substr(var0.lastIndexOf("/") + 1);
    Texture var4 = TexturePackPage.getTexture(var3);
               if (var4 != nullptr) {
                  setSharedTextureInternal(var0, var4);
    return var4;
               }

    SubTexture var5 = (SubTexture)GameWindow.texturePackTextures.get(var3);
               if (var5 != nullptr) {
    TextureAssetParams var17 = std::make_shared<TextureAssetParams>();
                  var17.subTexture = var5;
    std::string var18 = "@pack/" + var5.m_pack_name + "/" + var5.m_page_name + "/" + var5.m_info.name;
    Texture var8 = (Texture)TextureAssetManager.instance.load(std::make_shared<AssetPath>(var18), var17);
                  if (var8 == nullptr) {
                     nullTextures.push_back(var0);
                  } else {
                     setSharedTextureInternal(var0, var8);
                  }

    return var8;
               }
            }

            if (TexturePackPage.subTextureMap.containsKey(var0)) {
               return (Texture)TexturePackPage.subTextureMap.get(var0);
            } else {
    SubTexture var10 = (SubTexture)GameWindow.texturePackTextures.get(var0);
               if (var10 != nullptr) {
    TextureAssetParams var13 = std::make_shared<TextureAssetParams>();
                  var13.subTexture = var10;
    std::string var15 = "@pack/" + var10.m_pack_name + "/" + var10.m_page_name + "/" + var10.m_info.name;
    Texture var16 = (Texture)TextureAssetManager.instance.load(std::make_shared<AssetPath>(var15), var13);
                  if (var16 == nullptr) {
                     nullTextures.push_back(var0);
                  } else {
                     setSharedTextureInternal(var0, var16);
                  }

    return var16;
               } else if (BucketManager.Shared().HasTexture(var0)) {
    Texture var12 = BucketManager.Shared().getTexture(var0);
                  setSharedTextureInternal(var0, var12);
    return var12;
               } else if (StringUtils.endsWithIgnoreCase(var0, ".pcx")) {
                  nullTextures.push_back(var0);
    return nullptr;
               } else if (var0.lastIndexOf(46) == -1) {
                  nullTextures.push_back(var0);
    return nullptr;
               } else {
    std::string var11 = ZomboidFileSystem.instance.getString(var0);
    bool var14 = var11 != var0;
                  if (!var14 && !std::make_shared<File>(var11).exists()) {
                     nullTextures.push_back(var0);
    return nullptr;
                  } else {
    TextureAssetParams var6 = std::make_shared<TextureAssetParams>();
                     var6.flags = var1;
    Texture var7 = (Texture)TextureAssetManager.instance.load(std::make_shared<AssetPath>(var11), var6);
                     BucketManager.Shared().AddTexture(var0, var7);
                     setSharedTextureInternal(var0, var7);
    return var7;
                  }
               }
            }
         }
      }
   }

    static Texture getSharedTexture(const std::string& var0, const std::string& var1) {
      if (BucketManager.Shared().HasTexture(var0 + var1)) {
         return BucketManager.Shared().getTexture(var0 + var1);
      } else {
    Texture var2 = std::make_shared<Texture>(var0, var1);
         BucketManager.Shared().AddTexture(var0 + var1, var2);
    return var2;
      }
   }

    static Texture getSharedTexture(const std::string& var0, int[] var1, const std::string& var2) {
      if (BucketManager.Shared().HasTexture(var0 + var2)) {
         return BucketManager.Shared().getTexture(var0 + var2);
      } else {
    Texture var3 = std::make_shared<Texture>(var0, var1);
         BucketManager.Shared().AddTexture(var0 + var2, var3);
    return var3;
      }
   }

    static Texture getTexture(const std::string& var0) {
      if (!var0.contains(".txt")) {
    std::string var1 = var0.replace(".png", "");
         var1 = var1.replace(".pcx", "");
         var1 = var1.substr(var0.lastIndexOf("/") + 1);
    Texture var2 = TexturePackPage.getTexture(var1);
         if (var2 != nullptr) {
    return var2;
         }
      }

      if (BucketManager.Active().HasTexture(var0)) {
         return BucketManager.Active().getTexture(var0);
      } else {
         try {
    Texture var6 = std::make_shared<Texture>(var0);
            BucketManager.Active().AddTexture(var0, var6);
    return var6;
         } catch (Exception var3) {
    return nullptr;
         }
      }
   }

    static Texture getSteamAvatar(long var0) {
      if (steamAvatarMap.containsKey(var0)) {
         return steamAvatarMap.get(var0);
      } else {
    TextureID var2 = TextureID.createSteamAvatar(var0);
         if (var2 == nullptr) {
    return nullptr;
         } else {
    Texture var3 = std::make_shared<Texture>(var2, "SteamAvatar" + SteamUtils.convertSteamIDToString(var0));
            steamAvatarMap.put(var0, var3);
    return var3;
         }
      }
   }

    static void steamAvatarChanged(long var0) {
    Texture var2 = steamAvatarMap.get(var0);
      if (var2 != nullptr) {
         steamAvatarMap.remove(var0);
      }
   }

    static void forgetTexture(const std::string& var0) {
      BucketManager.Shared().forgetTexture(var0);
      s_sharedTextureTable.remove(var0);
   }

    static void reload(const std::string& var0) {
      if (var0 != nullptr && !var0.empty()) {
    Texture var1 = s_sharedTextureTable.get(var0);
         if (var1 == nullptr) {
            var1 = (Texture)Type.tryCastTo((Asset)TextureAssetManager.instance.getAssetTable().get(var0), Texture.class);
            if (var1 == nullptr) {
               return;
            }
         }

         var1.reloadFromFile(var0);
      }
   }

   public static int[] flipPixels(int[] var0, int var1, int var2) {
      int[] var3 = nullptr;
      if (var0 != nullptr) {
         var3 = new int[var1 * var2];

         for (int var4 = 0; var4 < var2; var4++) {
            for (int var5 = 0; var5 < var1; var5++) {
               var3[(var2 - var4 - 1) * var1 + var5] = var0[var4 * var1 + var5];
            }
         }
      }

    return var3;
   }

    void reloadFromFile(const std::string& var1) {
      if (this.dataid != nullptr) {
    TextureIDAssetParams var5 = std::make_shared<TextureIDAssetParams>();
         var5.flags = this.dataid.flags;
         this.dataid.getAssetManager().reload(this.dataid, var5);
      } else if (var1 != nullptr && !var1.empty()) {
    File var2 = std::make_shared<File>(var1);
         if (var2.exists()) {
            try {
    ImageData var3 = std::make_shared<ImageData>(var2.getAbsolutePath());
               if (var3.getWidthHW() != this.getWidthHW() || var3.getHeightHW() != this.getHeightHW()) {
                  return;
               }

               RenderThread.invokeOnRenderContext(var3, var1x -> {
                  GL11.glBindTexture(3553, lastTextureID = this.dataid.id);
    short var2x = 6408;
                  GL11.glTexImage2D(3553, 0, var2x, this.getWidthHW(), this.getHeightHW(), 0, 6408, 5121, var1x.getData().getBuffer());
               });
            } catch (Throwable var4) {
               ExceptionLogger.logException(var4, var1);
            }
         }
      }
   }

    void bind() {
      this.bind(3553);
   }

    void bind(int var1) {
      if (!this.isDestroyed() && this.isValid() && this.isReady()) {
         if (this.bindAlways) {
            this.dataid.bindalways();
         } else {
            this.dataid.bind();
         }
      } else {
         getErrorTexture().bind(var1);
      }
   }

    void copyMaskRegion(Texture var1, int var2, int var3, int var4, int var5) {
      if (var1.getMask() != nullptr) {
    std::make_shared<Mask>();
      }
   }

    void createMask() {
    std::make_shared<Mask>();
   }

    void createMask(boolean[] var1) {
    std::make_shared<Mask>();
   }

    void createMask(BooleanGrid var1) {
    std::make_shared<Mask>();
   }

    void createMask(WrappedBuffer var1) {
    std::make_shared<Mask>();
   }

    void destroy() {
      if (!this.destroyed) {
         if (this.dataid != nullptr && --this.dataid.referenceCount == 0) {
            if (lastTextureID == this.dataid.id) {
               lastTextureID = -1;
            }

            this.dataid.destroy();
         }

         this.destroyed = true;
      }
   }

    bool equals(Texture var1) {
      return var1.xStart == this.xStart
         && var1.xEnd == this.xEnd
         && var1.yStart == this.yStart
         && var1.yEnd == this.yEnd
         && var1.width == this.width
         && var1.height == this.height
         && var1.solid == this.solid
         && (
            this.dataid == nullptr
               || var1.dataid == nullptr
               || var1.dataid.pathFileName == nullptr
               || this.dataid.pathFileName == nullptr
               || var1.dataid.pathFileName == this.dataid.pathFileName)
         );
   }

    WrappedBuffer getData() {
      return this.dataid.getData();
   }

    void setData(ByteBuffer var1) {
      this.dataid.setData(var1);
   }

    int getHeight() {
      if (!this.isReady() && this.height <= 0 && !(dynamic_cast<SmartTexture*>(this) != nullptr)) {
         this.syncReadSize();
      }

      return this.height;
   }

    void setHeight(int var1) {
      this.height = var1;
   }

    int getHeightHW() {
      if (!this.isReady() && this.height <= 0 && !(dynamic_cast<SmartTexture*>(this) != nullptr)) {
         this.syncReadSize();
      }

      return this.dataid.heightHW;
   }

    int getHeightOrig() {
      return this.heightOrig == 0 ? this.getHeight() : this.heightOrig;
   }

    int getID() {
      return this.dataid.id;
   }

    Mask getMask() {
      return this.mask;
   }

    void setMask(Mask var1) {
      this.mask = var1;
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      if (var1 != nullptr) {
         if (var1 == this.name)) {
            if (!textures.containsKey(var1)) {
               textures.put(var1, this);
            }
         } else {
            if (textures.containsKey(var1)) {
            }

            if (textures.containsKey(this.name)) {
               textures.remove(this.name);
            }

            this.name = var1;
            textures.put(var1, this);
         }
      }
   }

    TextureID getTextureId() {
      return this.dataid;
   }

    bool getUseAlphaChannel() {
      return !this.solid;
   }

    void setUseAlphaChannel(bool var1) {
      this.dataid.solid = this.solid = !var1;
   }

    int getWidth() {
      if (!this.isReady() && this.width <= 0 && !(dynamic_cast<SmartTexture*>(this) != nullptr)) {
         this.syncReadSize();
      }

      return this.width;
   }

    void setWidth(int var1) {
      this.width = var1;
   }

    int getWidthHW() {
      if (!this.isReady() && this.width <= 0 && !(dynamic_cast<SmartTexture*>(this) != nullptr)) {
         this.syncReadSize();
      }

      return this.dataid.widthHW;
   }

    int getWidthOrig() {
      return this.widthOrig == 0 ? this.getWidth() : this.widthOrig;
   }

    float getXEnd() {
      return this.xEnd;
   }

    float getXStart() {
      return this.xStart;
   }

    float getYEnd() {
      return this.yEnd;
   }

    float getYStart() {
      return this.yStart;
   }

    float getOffsetX() {
      return this.offsetX;
   }

    void setOffsetX(int var1) {
      this.offsetX = var1;
   }

    float getOffsetY() {
      return this.offsetY;
   }

    void setOffsetY(int var1) {
      this.offsetY = var1;
   }

    bool isCollisionable() {
      return this.mask != nullptr;
   }

    bool isDestroyed() {
      return this.destroyed;
   }

    bool isSolid() {
      return this.solid;
   }

    bool isValid() {
      return this.dataid != nullptr;
   }

    void makeTransp(int var1, int var2, int var3) {
      this.setAlphaForeach(var1, var2, var3, 0);
   }

    void render(float var1, float var2, float var3, float var4) {
      this.render(var1, var2, var3, var4, 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
   }

    void render(float var1, float var2) {
      this.render(var1, var2, this.width, this.height, 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
   }

    void render(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, Consumer<TextureDraw> var9) {
      var1 += this.offsetX;
      var2 += this.offsetY;
      SpriteRenderer.instance.render(this, var1, var2, var3, var4, var5, var6, var7, var8, var9);
   }

   public void render(
      ObjectRenderEffects var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, Consumer<TextureDraw> var10
   ) {
    float var11 = this.offsetX + var2;
    float var12 = this.offsetY + var3;
      objRen.x1 = var11 + var1.x1 * var4;
      objRen.y1 = var12 + var1.y1 * var5;
      objRen.x2 = var11 + var4 + var1.x2 * var4;
      objRen.y2 = var12 + var1.y2 * var5;
      objRen.x3 = var11 + var4 + var1.x3 * var4;
      objRen.y3 = var12 + var5 + var1.y3 * var5;
      objRen.x4 = var11 + var1.x4 * var4;
      objRen.y4 = var12 + var5 + var1.y4 * var5;
      SpriteRenderer.instance
         .render(this, objRen.x1, objRen.y1, objRen.x2, objRen.y2, objRen.x3, objRen.y3, objRen.x4, objRen.y4, var6, var7, var8, var9, var10);
   }

   public void rendershader2(
      float var1, float var2, float var3, float var4, int var5, int var6, int var7, int var8, float var9, float var10, float var11, float var12
   ) {
      if (var12 != 0.0F) {
    float var13 = (float)var5 / this.getWidthHW();
    float var14 = (float)var6 / this.getHeightHW();
    float var15 = (float)(var5 + var7) / this.getWidthHW();
    float var16 = (float)(var6 + var8) / this.getHeightHW();
         if (this.flip) {
    float var17 = var15;
            var15 = var13;
            var13 = var17;
            var1 += this.widthOrig - this.offsetX - this.width;
            var2 += this.offsetY;
         } else {
            var1 += this.offsetX;
            var2 += this.offsetY;
         }

         if (var9 > 1.0F) {
            var9 = 1.0F;
         }

         if (var10 > 1.0F) {
            var10 = 1.0F;
         }

         if (var11 > 1.0F) {
            var11 = 1.0F;
         }

         if (var12 > 1.0F) {
            var12 = 1.0F;
         }

         if (var9 < 0.0F) {
            var9 = 0.0F;
         }

         if (var10 < 0.0F) {
            var10 = 0.0F;
         }

         if (var11 < 0.0F) {
            var11 = 0.0F;
         }

         if (var12 < 0.0F) {
            var12 = 0.0F;
         }

         if (!(var1 + var3 <= 0.0F)) {
            if (!(var2 + var4 <= 0.0F)) {
               if (!(var1 >= Core.getInstance().getScreenWidth())) {
                  if (!(var2 >= Core.getInstance().getScreenHeight())) {
                     lr = var9;
                     lg = var10;
                     lb = var11;
                     la = var12;
                     SpriteRenderer.instance
                        .render(this, var1, var2, var3, var4, var9, var10, var11, var12, var13, var16, var15, var16, var15, var14, var13, var14);
                  }
               }
            }
         }
      }
   }

    void renderdiamond(float var1, float var2, float var3, float var4, int var5, int var6, int var7, int var8) {
      SpriteRenderer.instance
         .render(nullptr, var1, var2, var1 + var3 / 2.0F, var2 - var4 / 2.0F, var1 + var3, var2, var1 + var3 / 2.0F, var2 + var4 / 2.0F, var5, var6, var7, var8);
   }

    void renderwallnw(float var1, float var2, float var3, float var4, int var5, int var6, int var7, int var8, int var9, int var10) {
      lr = -1.0F;
      lg = -1.0F;
      lb = -1.0F;
      la = -1.0F;
      if (this.flip) {
         var1 += this.widthOrig - this.offsetX - this.width;
         var2 += this.offsetY;
      } else {
         var1 += this.offsetX;
         var2 += this.offsetY;
      }

    int var11 = Core.TileScale;
      if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.LightingOldDebug.getValue()) {
         var8 = -65536;
         var6 = -65536;
         var7 = -65536;
         var5 = -65536;
      }

    float var12 = var1 - var3 / 2.0F - 0.0F;
    float var13 = var2 - 96 * var11 + var4 / 2.0F - 1.0F - 0.0F;
    float var14 = var1 + 0.0F;
    float var15 = var2 - 96 * var11 - 2.0F - 0.0F;
    float var16 = var1 + 0.0F;
    float var17 = var2 + 4.0F + 0.0F;
    float var18 = var1 - var3 / 2.0F - 0.0F;
    float var19 = var2 + var4 / 2.0F + 4.0F + 0.0F;
      SpriteRenderer.instance.render(this, var12, var13, var14, var15, var16, var17, var18, var19, var8, var7, var5, var6);
      if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.LightingOldDebug.getValue()) {
         var10 = -256;
         var9 = -256;
         var7 = -256;
         var5 = -256;
      }

      var12 = var1 - 0.0F;
      var13 = var2 - 96 * var11 - 0.0F;
      var14 = var1 + var3 / 2.0F + 0.0F;
      var15 = var2 - 96 * var11 + var4 / 2.0F - 0.0F;
      var16 = var1 + var3 / 2.0F + 0.0F;
      var17 = var2 + var4 / 2.0F + 5.0F + 0.0F;
      var18 = var1 - 0.0F;
      var19 = var2 + 5.0F + 0.0F;
      SpriteRenderer.instance.render(this, var12, var13, var14, var15, var16, var17, var18, var19, var7, var10, var9, var5);
   }

    void renderwallw(float var1, float var2, float var3, float var4, int var5, int var6, int var7, int var8) {
      lr = -1.0F;
      lg = -1.0F;
      lb = -1.0F;
      la = -1.0F;
      if (this.flip) {
         var1 += this.widthOrig - this.offsetX - this.width;
         var2 += this.offsetY;
      } else {
         var1 += this.offsetX;
         var2 += this.offsetY;
      }

      if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.LightingOldDebug.getValue()) {
         var6 = -16711936;
         var5 = -16711936;
         var8 = -16728064;
         var7 = -16728064;
      }

    int var9 = Core.TileScale;
    float var10 = var1 - var3 / 2.0F - 0.0F;
    float var11 = var2 - 96 * var9 + var4 / 2.0F - 1.0F - 0.0F;
    float var12 = var1 + var9 + 0.0F;
    float var13 = var2 - 96 * var9 - 3.0F - 0.0F;
    float var14 = var1 + var9 + 0.0F;
    float var15 = var2 + 3.0F + 0.0F;
    float var16 = var1 - var3 / 2.0F - 0.0F;
    float var17 = var2 + var4 / 2.0F + 4.0F + 0.0F;
      SpriteRenderer.instance.render(this, var10, var11, var12, var13, var14, var15, var16, var17, var8, var7, var5, var6);
   }

    void renderwalln(float var1, float var2, float var3, float var4, int var5, int var6, int var7, int var8) {
      lr = -1.0F;
      lg = -1.0F;
      lb = -1.0F;
      la = -1.0F;
      if (this.flip) {
         var1 += this.widthOrig - this.offsetX - this.width;
         var2 += this.offsetY;
      } else {
         var1 += this.offsetX;
         var2 += this.offsetY;
      }

      if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.LightingOldDebug.getValue()) {
         var6 = -16776961;
         var5 = -16776961;
         var8 = -16777024;
         var7 = -16777024;
      }

    int var9 = Core.TileScale;
    float var10 = var1 - 6.0F - 0.0F;
    float var11 = var2 - 96 * var9 - 3.0F - 0.0F;
    float var12 = var1 + var3 / 2.0F + 0.0F;
    float var13 = var2 - 96 * var9 + var4 / 2.0F - 0.0F;
    float var14 = var1 + var3 / 2.0F + 0.0F;
    float var15 = var2 + var4 / 2.0F + 5.0F + 0.0F;
    float var16 = var1 - 6.0F - 0.0F;
    float var17 = var2 + 2.0F + 0.0F;
      SpriteRenderer.instance.render(this, var10, var11, var12, var13, var14, var15, var16, var17, var7, var8, var6, var5);
   }

    void renderstrip(int var1, int var2, int var3, int var4, float var5, float var6, float var7, float var8, Consumer<TextureDraw> var9) {
      try {
         if (var8 <= 0.0F) {
            return;
         }

         if (var5 > 1.0F) {
            var5 = 1.0F;
         }

         if (var6 > 1.0F) {
            var6 = 1.0F;
         }

         if (var7 > 1.0F) {
            var7 = 1.0F;
         }

         if (var8 > 1.0F) {
            var8 = 1.0F;
         }

         if (var5 < 0.0F) {
            var5 = 0.0F;
         }

         if (var6 < 0.0F) {
            var6 = 0.0F;
         }

         if (var7 < 0.0F) {
            var7 = 0.0F;
         }

         if (var8 < 0.0F) {
            var8 = 0.0F;
         }

    float var10 = this.getXStart();
    float var11 = this.getYStart();
    float var12 = this.getXEnd();
    float var13 = this.getYEnd();
         if (this.flip) {
            var1 = (int)(var1 + (this.widthOrig - this.offsetX - this.width));
            var2 = (int)(var2 + this.offsetY);
         } else {
            var1 = (int)(var1 + this.offsetX);
            var2 = (int)(var2 + this.offsetY);
         }

         SpriteRenderer.instance.renderi(this, var1, var2, var3, var4, var5, var6, var7, var8, var9);
      } catch (Exception var15) {
         bDoingQuad = false;
         Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, var15);
      }
   }

    void setAlphaForeach(int var1, int var2, int var3, int var4) {
    ImageData var5 = this.getTextureId().getImageData();
      if (var5 != nullptr) {
         var5.makeTransp((byte)var1, (byte)var2, (byte)var3, (byte)var4);
      } else {
    WrappedBuffer var6 = this.getData();
         this.setData(ImageUtils.makeTransp(var6.getBuffer(), var1, var2, var3, var4, this.getWidthHW(), this.getHeightHW()));
         var6.dispose();
      }

    AlphaColorIndex var7 = std::make_shared<AlphaColorIndex>(var1, var2, var3, var4);
      if (this.dataid.alphaList == nullptr) {
         this.dataid.alphaList = std::make_unique<std::vector>();
      }

      if (!this.dataid.alphaList.contains(var7)) {
         this.dataid.alphaList.push_back(var7);
      }
   }

    void setCustomizedTexture() {
      this.dataid.pathFileName = nullptr;
   }

    void setNameOnly(const std::string& var1) {
      this.name = var1;
   }

    void setRegion(int var1, int var2, int var3, int var4) {
      if (var1 >= 0 && var1 <= this.getWidthHW()) {
         if (var2 >= 0 && var2 <= this.getHeightHW()) {
            if (var3 > 0) {
               if (var4 > 0) {
                  if (var3 + var1 > this.getWidthHW()) {
                     var3 = this.getWidthHW() - var1;
                  }

                  if (var4 > this.getHeightHW()) {
                     var4 = this.getHeightHW() - var2;
                  }

                  this.xStart = (float)var1 / this.getWidthHW();
                  this.yStart = (float)var2 / this.getHeightHW();
                  this.xEnd = (float)(var1 + var3) / this.getWidthHW();
                  this.yEnd = (float)(var2 + var4) / this.getHeightHW();
                  this.width = var3;
                  this.height = var4;
               }
            }
         }
      }
   }

    Texture splitIcon() {
      if (this.splitIconTex == nullptr) {
         if (!this.dataid.isReady()) {
            this.splitIconTex = std::make_unique<Texture>();
            this.splitIconTex.name = this.name + "_Icon";
            this.splitIconTex.dataid = this.dataid;
            this.splitIconTex.dataid.referenceCount++;
            this.splitIconTex.splitX = this.splitX;
            this.splitIconTex.splitY = this.splitY;
            this.splitIconTex.splitW = this.splitW;
            this.splitIconTex.splitH = this.splitH;
            this.splitIconTex.width = this.width;
            this.splitIconTex.height = this.height;
            this.splitIconTex.offsetX = 0.0F;
            this.splitIconTex.offsetY = 0.0F;
            this.splitIconTex.widthOrig = 0;
            this.splitIconTex.heightOrig = 0;
            this.splitIconTex.addDependency(this.dataid);
            setSharedTextureInternal(this.splitIconTex.name, this.splitIconTex);
            return this.splitIconTex;
         }

         this.splitIconTex = std::make_shared<Texture>(this.getTextureId(), this.name + "_Icon");
    float var1 = this.xStart * this.getWidthHW();
    float var2 = this.yStart * this.getHeightHW();
    float var3 = this.xEnd * this.getWidthHW() - var1;
    float var4 = this.yEnd * this.getHeightHW() - var2;
         this.splitIconTex.setRegion((int)var1, (int)var2, (int)var3, (int)var4);
         this.splitIconTex.offsetX = 0.0F;
         this.splitIconTex.offsetY = 0.0F;
         setSharedTextureInternal(this.name + "_Icon", this.splitIconTex);
      }

      return this.splitIconTex;
   }

    Texture split(int var1, int var2, int var3, int var4) {
    Texture var5 = std::make_shared<Texture>(this.getTextureId(), this.name + "_" + var1 + "_" + var2);
      this.splitX = var1;
      this.splitY = var2;
      this.splitW = var3;
      this.splitH = var4;
      if (this.getTextureId().isReady()) {
         var5.setRegion(var1, var2, var3, var4);
      } else {
    assert false;
      }

    return var5;
   }

    Texture split(const std::string& var1, int var2, int var3, int var4, int var5) {
    Texture var6 = std::make_shared<Texture>(this.getTextureId(), var1);
      var6.setRegion(var2, var3, var4, var5);
    return var6;
   }

   public Texture[] split(int var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8) {
      Texture[] var9 = new Texture[var3 * var4];

      for (int var10 = 0; var10 < var3; var10++) {
         for (int var11 = 0; var11 < var4; var11++) {
            var9[var11 + var10 * var4] = std::make_shared<Texture>(this.getTextureId(), this.name + "_" + var3 + "_" + var4);
            var9[var11 + var10 * var4].setRegion(var1 + var11 * var5 + var7 * var11, var2 + var10 * var6 + var8 * var10, var5, var6);
            var9[var11 + var10 * var4].copyMaskRegion(this, var1 + var11 * var5 + var7 * var11, var2 + var10 * var6 + var8 * var10, var5, var6);
         }
      }

    return var9;
   }

   public Texture[][] split2D(int[] var1, int[] var2) {
      if (var1 != nullptr && var2 != nullptr) {
         Texture[][] var3 = new Texture[var1.length][var2.length];
    float var8 = 0.0F;
    float var6 = 0.0F;
    float var5 = 0.0F;

         for (int var9 = 0; var9 < var2.length; var9++) {
            var6 += var8;
            var8 = (float)var2[var9] / this.getHeightHW();
            var5 = 0.0F;

            for (int var10 = 0; var10 < var1.length; var10++) {
    float var7 = (float)var1[var10] / this.getWidthHW();
    Texture var4 = var3[var10][var9] = std::make_shared<Texture>(this);
               var4.width = var1[var10];
               var4.height = var2[var9];
               var4.xStart = var5;
               var4.xEnd = var5 += var7;
               var4.yStart = var6;
               var4.yEnd = var6 + var8;
            }
         }

    return var3;
      } else {
    return nullptr;
      }
   }

    std::string toString() {
      return this.getClass().getSimpleName() + "{ name:\"" + this.name + "\", w:" + this.getWidth() + ", h:" + this.getHeight() + " }";
   }

    void saveMask(const std::string& var1) {
      this.mask.save(var1);
   }

    void saveToZomboidDirectory(const std::string& var1) {
      if (!StringUtils.containsDoubleDot(var1)) {
    std::string var2 = ZomboidFileSystem.instance.getCacheDirSub(var1);
         RenderThread.invokeOnRenderContext(() -> this.saveOnRenderThread(var2));
      }
   }

    void saveToCurrentSavefileDirectory(const std::string& var1) {
      if (!StringUtils.containsDoubleDot(var1)) {
    std::string var2 = ZomboidFileSystem.instance.getFileNameInCurrentSave(var1);
         RenderThread.invokeOnRenderContext(() -> this.saveOnRenderThread(var2));
      }
   }

    void saveOnRenderThread(const std::string& var1) {
      if (this.getID() == -1) {
         throw IllegalStateException("texture hasn't been uploaded to the GPU");
      } else {
         GL11.glPixelStorei(3333, 1);
         GL13.glActiveTexture(33984);
         GL11.glEnable(3553);
         this.bind();
    int var2 = this.getWidth();
    int var3 = this.getHeight();
    int var4 = this.getWidthHW();
    int var5 = this.getHeightHW();
    uint8_t var6 = 4;
    ByteBuffer var7 = MemoryUtil.memAlloc(var4 * var5 * var6);
         GL21.glGetTexImage(3553, 0, 6408, 5121, var7);
         int[] var8 = new int[var2 * var3];
    int var9 = (int)PZMath.floor(this.getXStart() * var4);
    int var10 = (int)PZMath.floor(this.getYStart() * var5);

         for (int var11 = 0; var11 < var8.length; var11++) {
    int var12 = var9 + var11 % var2;
    int var13 = var10 + var11 / var2;
    int var14 = (var12 + var13 * var4) * var6;
            var8[var11] = (var7.get(var14 + 3) & 255) << 24
               | (var7.get(var14) & 255) << 16
               | (var7.get(var14 + 1) & 255) << 8
               | (var7.get(var14 + 2) & 255) << 0;
         }

         MemoryUtil.memFree(var7);
    BufferedImage var16 = std::make_shared<BufferedImage>(var2, var3, 2);
         var16.setRGB(0, 0, var2, var3, var8, 0, var2);

         try {
    File var17 = std::make_shared<File>(var1);
            var17.getParentFile().mkdirs();
            ImageIO.write(var16, "png", var17);
         } catch (IOException var15) {
            ExceptionLogger.logException(var15);
         }

         SpriteRenderer.ringBuffer.restoreBoundTextures = true;
      }
   }

    void loadMaskRegion(ByteBuffer var1) {
      if (var1 != nullptr) {
         this.mask = std::make_unique<Mask>();
         this.mask.mask = std::make_shared<BooleanGrid>(this.width, this.height);
         this.mask.mask.LoadFromByteBuffer(var1);
      }
   }

    void saveMaskRegion(ByteBuffer var1) {
      if (var1 != nullptr) {
         this.mask.mask.PutToByteBuffer(var1);
      }
   }

    int getRealWidth() {
      return this.realWidth;
   }

    void setRealWidth(int var1) {
      this.realWidth = var1;
   }

    int getRealHeight() {
      return this.realHeight;
   }

    void setRealHeight(int var1) {
      this.realHeight = var1;
   }

    Vector2 getUVScale(Vector2 var1) {
      var1.set(1.0F, 1.0F);
      if (this.dataid == nullptr) {
    return var1;
      } else {
         if (this.dataid.heightHW != this.dataid.height || this.dataid.widthHW != this.dataid.width) {
            var1.x = (float)this.dataid.width / this.dataid.widthHW;
            var1.y = (float)this.dataid.height / this.dataid.heightHW;
         }

    return var1;
      }
   }

    void syncReadSize() {
    PNGSize var1 = pngSize.get();
      var1.readSize(this.name);
      this.width = var1.width;
      this.height = var1.height;
   }

    AssetType getType() {
    return ASSET_TYPE;
   }

    void onBeforeReady() {
      if (this.assetParams != nullptr) {
         this.assetParams.subTexture = nullptr;
         this.assetParams = nullptr;
      }

      this.solid = this.dataid.solid;
      if (this.splitX == -1) {
         this.width = this.dataid.width;
         this.height = this.dataid.height;
         this.xEnd = (float)this.width / this.dataid.widthHW;
         this.yEnd = (float)this.height / this.dataid.heightHW;
         if (this.dataid.mask != nullptr) {
            this.createMask(this.dataid.mask);
         }
      } else {
         this.setRegion(this.splitX, this.splitY, this.splitW, this.splitH);
         if (this.dataid.mask != nullptr) {
            this.mask = std::make_shared<Mask>(this.dataid.mask, this.dataid.width, this.dataid.height, this.splitX, this.splitY, this.splitW, this.splitH);
         }
      }
   }

    static void collectAllIcons(std::string> var0, std::string> var1) {
      for (Entry var3 : s_sharedTextureTable.entrySet()) {
         if (((std::string)var3.getKey()).startsWith("media/ui/Container_") || ((std::string)var3.getKey()).startsWith("Item_")) {
    std::string var4 = "";
            if (((std::string)var3.getKey()).startsWith("Item_")) {
               var4 = ((std::string)var3.getKey()).replaceFirst("Item_", "");
            } else if (((std::string)var3.getKey()).startsWith("media/ui/Container_")) {
    std::string var5 = ((std::string)var3.getKey()).replaceFirst("media/ui/Container_", "");
               var4 = var5.replaceAll("\\.png", "");
               DebugLog.log("Adding " + var4.toLowerCase() + ", value = " + (std::string)var3.getKey());
            }

            var0.put(var4.toLowerCase(), var4);
            var1.put(var4.toLowerCase(), (std::string)var3.getKey());
         }
      }
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
