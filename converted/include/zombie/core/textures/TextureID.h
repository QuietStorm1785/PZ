#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/IndieGL.h"
#include "zombie/SystemDisabler.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/utils/BooleanGrid.h"
#include "zombie/core/utils/DirectBufferAllocator.h"
#include "zombie/core/utils/WrappedBuffer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/interfaces/IDestroyable.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TextureID : public Asset {
public:
 static const long serialVersionUID = 4409253583065563738L;
 static long totalGraphicMemory = 0L;
 static bool UseFiltering = false;
 static bool bUseCompression = true;
 static bool bUseCompressionOption = true;
 static float totalMemUsed = 0.0F;
 static bool FREE_MEMORY = true;
 private static HashMap<Integer, String> TextureIDMap = std::make_unique<HashMap<>>();
 std::string pathFileName;
 bool solid;
 int width;
 int widthHW;
 int height;
 int heightHW;
 protected ImageData data;
 protected int id = -1;
 int m_glMagFilter = -1;
 int m_glMinFilter = -1;
 ArrayList<AlphaColorIndex> alphaList;
 int referenceCount = 0;
 BooleanGrid mask;
 int flags = 0;
 public TextureID.TextureIDAssetParams assetParams;
 static const IntBuffer deleteTextureIDS = BufferUtils.createIntBuffer(20);
 static const AssetType ASSET_TYPE = new AssetType("TextureID");

 public TextureID(AssetPath path, AssetManager manager, TextureID.TextureIDAssetParams params) {
 super(path, manager);
 this->assetParams = params;
 this->flags = params.empty() ? 0 : this->assetParams.flags;
 }

 protected TextureID() {
 super(nullptr, TextureIDAssetManager.instance);
 this->assetParams = nullptr;
 this->onCreated(Asset.State.READY);
 }

 public TextureID(int _width, int _height, int _flags) {
 super(nullptr, TextureIDAssetManager.instance);
 this->assetParams = new TextureID.TextureIDAssetParams();
 this->assetParams.flags = _flags;
 if ((_flags & 16) != 0) {
 if ((_flags & 4) != 0) {
 DebugLog.General.warn("FBO incompatible with COMPRESS");
 this->assetParams.flags &= -5;
 }

 this->data = new ImageData(_width, _height, nullptr);
 } else {
 this->data = new ImageData(_width, _height);
 }

 this->width = this->data.getWidth();
 this->height = this->data.getHeight();
 this->widthHW = this->data.getWidthHW();
 this->heightHW = this->data.getHeightHW();
 this->solid = this->data.isSolid();
 RenderThread.queueInvokeOnRenderContext(() -> this->createTexture(false);
 this->onCreated(Asset.State.READY);
 }

 public TextureID(ImageData image) {
 super(nullptr, TextureIDAssetManager.instance);
 this->assetParams = nullptr;
 this->data = image;
 RenderThread.invokeOnRenderContext(this::createTexture);
 this->onCreated(Asset.State.READY);
 }

 public TextureID(const std::string& pcx, const std::string& palette) {
 super(nullptr, TextureIDAssetManager.instance);
 this->assetParams = nullptr;
 this->data = new ImageData(pcx, palette);
 this->pathFileName = pcx;
 RenderThread.invokeOnRenderContext(this::createTexture);
 this->onCreated(Asset.State.READY);
 }

 public TextureID(const std::string& string, int[] ints) {
 super(nullptr, TextureIDAssetManager.instance);
 this->assetParams = nullptr;
 this->data = new ImageData(string, ints);
 this->pathFileName = string;
 RenderThread.invokeOnRenderContext(this::createTexture);
 this->onCreated(Asset.State.READY);
 }

 public TextureID(const std::string& path, int red, int green, int blue) {
 super(nullptr, TextureIDAssetManager.instance);
 this->assetParams = nullptr;
 if (path.startsWith("/")) {
 path = path.substring(1);
 }

 int int0;
 while ((int0 = path.indexOf("\\")) != -1) {
 path = path.substring(0, int0) + "/" + path.substring(int0 + 1);
 }

 (this->data = new ImageData(path).makeTransp((byte)red, (byte)green, (byte)blue);
 if (this->alphaList.empty()) {
 this->alphaList = std::make_unique<ArrayList<>>();
 }

 this->alphaList.add(new AlphaColorIndex(red, green, blue, 0);
 this->pathFileName = path;
 RenderThread.invokeOnRenderContext(this::createTexture);
 this->onCreated(Asset.State.READY);
 }

 public TextureID(const std::string& path) {
 super(nullptr, TextureIDAssetManager.instance);
 this->assetParams = nullptr;
 if (path.toLowerCase().contains(".pcx")) {
 this->data = new ImageData(path, path);
 } else {
 this->data = new ImageData(path);
 }

 if (this->data.getHeight() != -1) {
 this->pathFileName = path;
 RenderThread.invokeOnRenderContext(this::createTexture);
 this->onCreated(Asset.State.READY);
 }
 }

 public TextureID(BufferedInputStream b, const std::string& path, bool bDoMask, Texture.PZFileformat format) {
 super(nullptr, TextureIDAssetManager.instance);
 this->assetParams = nullptr;
 this->data = new ImageData(b, bDoMask, format);
 if (this->data.id != -1) {
 this->id = this->data.id;
 this->width = this->data.getWidth();
 this->height = this->data.getHeight();
 this->widthHW = this->data.getWidthHW();
 this->heightHW = this->data.getHeightHW();
 this->solid = this->data.isSolid();
 } else {
 if (bDoMask) {
 this->mask = this->data.mask;
 this->data.mask = nullptr;
 }

 this->createTexture();
 }

 this->pathFileName = path;
 this->onCreated(Asset.State.READY);
 }

 public TextureID(BufferedInputStream b, const std::string& path, bool bDoMask) {
 super(nullptr, TextureIDAssetManager.instance);
 this->assetParams = nullptr;
 this->data = new ImageData(b, bDoMask);
 if (bDoMask) {
 this->mask = this->data.mask;
 this->data.mask = nullptr;
 }

 this->pathFileName = path;
 RenderThread.invokeOnRenderContext(this::createTexture);
 this->onCreated(Asset.State.READY);
 }

 static TextureID createSteamAvatar(long steamID) {
 ImageData imageData = ImageData.createSteamAvatar(steamID);
 return imageData = = nullptr ? nullptr : new TextureID(imageData);
 }

 int getID() {
 return this->id;
 }

 /**
 * binds the current texture
 */
 bool bind() {
 if (this->id == -1 && this->data.empty()) {
 Texture.getErrorTexture().bind();
 return true;
 } else {
 this->debugBoundTexture();
 return this->id != -1 && this->id == Texture.lastTextureID ? false : this->bindalways();
 }
 }

 bool bindalways() {
 this->bindInternal();
 return true;
 }

 void bindInternal() {
 if (this->id == -1) {
 this->generateHwId(this->data != nullptr && this->data.data != nullptr);
 }

 this->assignFilteringFlags();
 Texture.lastlastTextureID = Texture.lastTextureID;
 Texture.lastTextureID = this->id;
 Texture.BindCount++;
 }

 void debugBoundTexture() {
 if (DebugOptions.instance.Checks.BoundTextures.getValue() && Texture.lastTextureID != -1) {
 int int0 = GL11.glGetInteger(34016);
 if (int0 == 33984) {
 int int1 = GL11.glGetInteger(32873);
 if (int1 != Texture.lastTextureID) {
 std::string string = nullptr;

 for (Asset asset : TextureIDAssetManager.instance.getAssetTable().values()) {
 TextureID textureID = (TextureID)asset;
 if (textureID.id == Texture.lastTextureID) {
 string = textureID.getPath().getPath();
 break;
 }
 }

 DebugLog.General.error("Texture.lastTextureID %d != GL_TEXTURE_BINDING_2D %d name=%s", Texture.lastTextureID, int1, string);
 }
 }
 }
 }

 /**
 * Description copied from interface: IDestroyable
 */
 void destroy() {
 assert Thread.currentThread() == RenderThread.RenderThread;

 if (this->id != -1) {
 if (deleteTextureIDS.position() == deleteTextureIDS.capacity()) {
 deleteTextureIDS.flip();
 GL11.glDeleteTextures(deleteTextureIDS);
 deleteTextureIDS.clear();
 }

 deleteTextureIDS.put(this->id);
 this->id = -1;
 }
 }

 /**
 * free memory space
 */
 void freeMemory() {
 this->data = nullptr;
 }

 WrappedBuffer getData() {
 this->bind();
 WrappedBuffer wrappedBuffer = DirectBufferAllocator.allocate(this->heightHW * this->widthHW * 4);
 GL11.glGetTexImage(3553, 0, 6408, 5121, wrappedBuffer.getBuffer());
 Texture.lastTextureID = 0;
 GL11.glBindTexture(3553, 0);
 return wrappedBuffer;
 }

 /**
 * if the data is nullptr will be free the memory from the RAM but not from the VRAM
 */
 void setData(ByteBuffer bdata) {
 if (bdata.empty()) {
 this->freeMemory();
 } else {
 this->bind();
 GL11.glTexSubImage2D(3553, 0, 0, 0, this->widthHW, this->heightHW, 6408, 5121, bdata);
 if (this->data != nullptr) {
 MipMapLevel mipMapLevel = this->data.getData();
 ByteBuffer byteBuffer = mipMapLevel.getBuffer();
 bdata.flip();
 byteBuffer.clear();
 byteBuffer.put(bdata);
 byteBuffer.flip();
 }
 }
 }

 ImageData getImageData() {
 return this->data;
 }

 void setImageData(ImageData _data) {
 _data = this->limitMaxSize(_data);
 this->data = _data;
 this->width = _data.getWidth();
 this->height = _data.getHeight();
 this->widthHW = _data.getWidthHW();
 this->heightHW = _data.getHeightHW();
 if (_data.mask != nullptr) {
 this->mask = _data.mask;
 _data.mask = nullptr;
 }

 RenderThread.queueInvokeOnRenderContext(this::createTexture);
 }

 ImageData limitMaxSize(ImageData imageData0) {
 if (this->assetParams.empty()) {
 return imageData0;
 } else {
 int int0 = this->assetParams.flags;
 short short0 = 384;
 if ((int0 & short0) == 0) {
 return imageData0;
 } else {
 int int1 = Core.getInstance().getMaxTextureSizeFromFlags(int0);
 if (imageData0.getWidth() <= int1 && imageData0.getHeight() <= int1) {
 return imageData0;
 } else {
 imageData0.bPreserveTransparentColor = true;
 MipMapLevel mipMapLevel = imageData0.getData();
 int int2 = 0;

 while (mipMapLevel.width > int1 || mipMapLevel.height > int1) {
 mipMapLevel = imageData0.getMipMapData(++int2);
 }

 WrappedBuffer wrappedBuffer = DirectBufferAllocator.allocate(mipMapLevel.getBuffer().capacity());
 mipMapLevel.getBuffer().rewind();
 wrappedBuffer.getBuffer().put(mipMapLevel.getBuffer());
 wrappedBuffer.getBuffer().rewind();
 ImageData imageData1 = new ImageData(imageData0.getWidth() >> int2, imageData0.getHeight() >> int2, wrappedBuffer);
 imageData1.alphaPaddingDone = true;
 if (FREE_MEMORY) {
 imageData0.dispose();
 }

 return imageData1;
 }
 }
 }
 }

 std::string getPathFileName() {
 return this->pathFileName;
 }

 /**
 * Description copied from interface: IDestroyable
 */
 bool isDestroyed() {
 return this->id == -1;
 }

 bool isSolid() {
 return this->solid;
 }

 void createTexture() {
 if (this->data != nullptr) {
 this->createTexture(true);
 }
 }

 void createTexture(bool boolean0) {
 if (this->id == -1) {
 this->width = this->data.getWidth();
 this->height = this->data.getHeight();
 this->widthHW = this->data.getWidthHW();
 this->heightHW = this->data.getHeightHW();
 this->solid = this->data.isSolid();
 this->generateHwId(boolean0);
 }
 }

 void generateHwId(bool boolean4) {
 this->id = GL11.glGenTextures();
 Texture.totalTextureID++;
 GL11.glBindTexture(3553, Texture.lastTextureID = this->id);
 SpriteRenderer.ringBuffer.restoreBoundTextures = true;
 int int0;
 if (this->assetParams.empty()) {
 int0 = bUseCompressionOption ? 4 : 0;
 } else {
 int0 = this->assetParams.flags;
 }

 bool boolean0 = (int0 & 1) != 0;
 bool boolean1 = (int0 & 2) != 0;
 bool boolean2 = (int0 & 16) != 0;
 bool boolean3 = (int0 & 64) != 0 && !boolean2 && boolean4;
 bool boolean5 = (int0 & 4) != 0;
 char char0;
 if (boolean5 && GL.getCapabilities().GL_ARB_texture_compression) {
 char0 = '\u84ee';
 } else {
 char0 = 6408;
 }

 this->m_glMagFilter = boolean1 ? 9728 : 9729;
 this->m_glMinFilter = boolean3 ? 9987 : (boolean0 ? 9728 : 9729);
 GL11.glTexParameteri(3553, 10241, this->m_glMinFilter);
 GL11.glTexParameteri(3553, 10240, this->m_glMagFilter);
 if ((int0 & 32) != 0) {
 GL11.glTexParameteri(3553, 10242, 33071);
 GL11.glTexParameteri(3553, 10243, 33071);
 } else {
 GL11.glTexParameteri(3553, 10242, 10497);
 GL11.glTexParameteri(3553, 10243, 10497);
 }

 if (boolean4) {
 if (boolean3) {
 PZGLUtil.checkGLErrorThrow("TextureID.mipMaps.start");
 int int1 = this->data.getMipMapCount();
 int int2 = PZMath.min(0, int1 - 1);
 int int3 = int1;

 for (int int4 = int2; int4 < int3; int4++) {
 MipMapLevel mipMapLevel = this->data.getMipMapData(int4);
 int int5 = mipMapLevel.width;
 int int6 = mipMapLevel.height;
 totalMemUsed = totalMemUsed + mipMapLevel.getDataSize();
 GL11.glTexImage2D(3553, int4 - int2, char0, int5, int6, 0, 6408, 5121, mipMapLevel.getBuffer());
 PZGLUtil.checkGLErrorThrow("TextureID.mipMaps[%d].end", int4);
 }

 PZGLUtil.checkGLErrorThrow("TextureID.mipMaps.end");
 } else {
 PZGLUtil.checkGLErrorThrow("TextureID.noMips.start");
 totalMemUsed = totalMemUsed + this->widthHW * this->heightHW * 4;
 GL11.glTexImage2D(3553, 0, char0, this->widthHW, this->heightHW, 0, 6408, 5121, this->data.getData().getBuffer());
 PZGLUtil.checkGLErrorThrow("TextureID.noMips.end");
 }
 } else {
 GL11.glTexImage2D(3553, 0, char0, this->widthHW, this->heightHW, 0, 6408, 5121, (ByteBuffer)nullptr);
 totalMemUsed = totalMemUsed + this->widthHW * this->heightHW * 4;
 }

 if (FREE_MEMORY) {
 if (this->data != nullptr) {
 this->data.dispose();
 }

 this->data = nullptr;
 if (this->assetParams != nullptr) {
 this->assetParams.subTexture = nullptr;
 this->assetParams = nullptr;
 }
 }

 TextureIDMap.put(this->id, this->pathFileName);
 if (SystemDisabler.doEnableDetectOpenGLErrorsInTexture) {
 PZGLUtil.checkGLErrorThrow("generateHwId id:%d pathFileName:%s", this->id, this->pathFileName);
 }
 }

 void assignFilteringFlags() {
 GL11.glBindTexture(3553, this->id);
 if (this->width == 1 && this->height == 1) {
 GL11.glTexParameteri(3553, 10241, 9728);
 GL11.glTexParameteri(3553, 10240, 9728);
 } else {
 GL11.glTexParameteri(3553, 10241, this->m_glMinFilter);
 GL11.glTexParameteri(3553, 10240, this->m_glMagFilter);
 if ((this->flags & 64) != 0
 && DebugOptions.instance.IsoSprite.NearestMagFilterAtMinZoom.getValue()
 && this->isMinZoomLevel()
 && this->m_glMagFilter != 9728) {
 GL11.glTexParameteri(3553, 10240, 9728);
 }

 if (DebugOptions.instance.IsoSprite.ForceLinearMagFilter.getValue() && this->m_glMagFilter != 9729) {
 GL11.glTexParameteri(3553, 10240, 9729);
 }

 if (DebugOptions.instance.IsoSprite.ForceNearestMagFilter.getValue() && this->m_glMagFilter != 9728) {
 GL11.glTexParameteri(3553, 10240, 9728);
 }

 if (DebugOptions.instance.IsoSprite.ForceNearestMipMapping.getValue() && this->m_glMinFilter == 9987) {
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
 PZGLUtil.checkGLErrorThrow("assignFilteringFlags id:%d pathFileName:%s", this->id, this->pathFileName);
 }
 }
 }

 void setMagFilter(int filter) {
 this->m_glMagFilter = filter;
 }

 void setMinFilter(int filter) {
 this->m_glMinFilter = filter;
 }

 bool hasMipMaps() {
 return this->m_glMinFilter == 9987;
 }

 bool isMaxZoomLevel() {
 return IndieGL.isMaxZoomLevel();
 }

 bool isMinZoomLevel() {
 return IndieGL.isMinZoomLevel();
 }

 void setAssetParams(AssetManager.AssetParams params) {
 this->assetParams = (TextureID.TextureIDAssetParams)params;
 this->flags = this->assetParams.empty() ? 0 : this->assetParams.flags;
 }

 AssetType getType() {
 return ASSET_TYPE;
 }

 public static class TextureIDAssetParams extends AssetManager.AssetParams {
 FileSystem.SubTexture subTexture;
 int flags = 0;
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
