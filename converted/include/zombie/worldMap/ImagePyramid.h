#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/image/BufferedImage.h"
#include "javax/imageio/ImageIO.h"
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/textures/ImageData.h"
#include "zombie/core/textures/MipMapLevel.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureID.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ImagePyramid {
public:
 std::string m_directory;
 std::string m_zipFile;
 FileSystem m_zipFS;
 HashMap<String, ImagePyramid.PyramidTexture> m_textures = std::make_unique<HashMap<>>();
 HashSet<String> m_missing = std::make_unique<HashSet<>>();
 int m_requestNumber = 0;
 int m_minX;
 int m_minY;
 int m_maxX;
 int m_maxY;
 float m_resolution = 1.0F;
 int m_minZ;
 int m_maxZ;
 int MAX_TEXTURES = 100;
 int MAX_REQUEST_NUMBER = Core.bDebug ? 10000 : Integer.MAX_VALUE;

 void setDirectory(const std::string& directory) {
 if (this->m_zipFile != nullptr) {
 this->m_zipFile = nullptr;
 if (this->m_zipFS != nullptr) {
 try {
 this->m_zipFS.close();
 } catch (IOException iOException) {
 }

 this->m_zipFS = nullptr;
 }
 }

 this->m_directory = directory;
 }

 void setZipFile(const std::string& zipFile) {
 this->m_directory = nullptr;
 this->m_zipFile = zipFile;
 this->m_zipFS = this->openZipFile();
 this->readInfoFile();
 this->m_minZ = Integer.MAX_VALUE;
 this->m_maxZ = Integer.MIN_VALUE;
 if (this->m_zipFS != nullptr) {
 try (DirectoryStream directoryStream = Files.newDirectoryStream(this->m_zipFS.getPath("/"))) {
 for (auto& path : directoryStream) if (Files.isDirectory(path) {
 int int0 = PZMath.tryParseInt(path.getFileName().toString(), -1);
 this->m_minZ = PZMath.min(this->m_minZ, int0);
 this->m_maxZ = PZMath.max(this->m_maxZ, int0);
 }
 }
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 }
 }
 }

 Texture getImage(int x, int y, int z) {
 std::string string = String.format("%dx%dx%d", x, y, z);
 if (this->m_missing.contains(string) {
 return nullptr;
 } else {
 File file = new File(this->m_directory, String.format("%s%d%stile%dx%d.png", File.separator, z, File.separator, x, y);
 if (!file.exists()) {
 this->m_missing.add(string);
 return nullptr;
 } else {
 return Texture.getSharedTexture(file.getAbsolutePath());
 }
 }
 }

 TextureID getTexture(int x, int y, int z) {
 std::string string = String.format("%dx%dx%d", x, y, z);
 if (this->m_textures.containsKey(string) {
 ImagePyramid.PyramidTexture pyramidTexture0 = this->m_textures.get(string);
 pyramidTexture0.m_requestNumber = this->m_requestNumber++;
 if (this->m_requestNumber >= this->MAX_REQUEST_NUMBER) {
 this->resetRequestNumbers();
 }

 return pyramidTexture0.m_textureID;
 } else if (this->m_missing.contains(string) {
 return nullptr;
 } else if (this->m_zipFile == nullptr) {
 File file = new File(this->m_directory, String.format("%s%d%stile%dx%d.png", File.separator, z, File.separator, x, y);
 if (!file.exists()) {
 this->m_missing.add(string);
 return nullptr;
 } else {
 Texture texture = Texture.getSharedTexture(file.getAbsolutePath());
 return texture = = nullptr ? nullptr : texture.getTextureId();
 }
 } else if (this->m_zipFS != nullptr && this->m_zipFS.isOpen()) {
 try {
 Path path = this->m_zipFS.getPath(String.valueOf(z), String.format("tile%dx%d.png", x, y);

 try {
 TextureID textureID;
 try (InputStream inputStream = Files.newInputStream(path) {
 ImageData imageData = new ImageData(inputStream, false);
 ImagePyramid.PyramidTexture pyramidTexture1 = this->checkTextureCache(string);
 if (pyramidTexture1.m_textureID == nullptr) {
 textureID = new TextureID(imageData);
 pyramidTexture1.m_textureID = textureID;
 } else {
 this->replaceTextureData(pyramidTexture1, imageData);
 }

 textureID = pyramidTexture1.m_textureID;
 }

 return textureID;
 } catch (NoSuchFileException noSuchFileException) {
 this->m_missing.add(string);
 }
 } catch (Exception exception) {
 this->m_missing.add(string);
 exception.printStackTrace();
 }

 return nullptr;
 } else {
 return nullptr;
 }
 }

 void replaceTextureData(ImagePyramid.PyramidTexture pyramidTexture, ImageData imageData) {
 char char0;
 if (GL.getCapabilities().GL_ARB_texture_compression) {
 char0 = '\u84ee';
 } else {
 char0 = 6408;
 }

 GL11.glBindTexture(3553, Texture.lastTextureID = pyramidTexture.m_textureID.getID());
 SpriteRenderer.ringBuffer.restoreBoundTextures = true;
 GL11.glTexImage2D(3553, 0, char0, imageData.getWidthHW(), imageData.getHeightHW(), 0, 6408, 5121, imageData.getData().getBuffer());
 imageData.dispose();
 }

 void generateFiles(const std::string& imageFile, const std::string& outputDirectory) {
 ImageData imageData = new ImageData(imageFile);
 if (imageData != nullptr) {
 short short0 = 256;
 uint8_t byte0 = 5;

 for (int int0 = 0; int0 < byte0; int0++) {
 MipMapLevel mipMapLevel = imageData.getMipMapData(int0);
 float float0 = (float)imageData.getWidth() / (1 << int0);
 float float1 = (float)imageData.getHeight() / (1 << int0);
 int int1 = (int)Math.ceil(float0 / short0);
 int int2 = (int)Math.ceil(float1 / short0);

 for (int int3 = 0; int3 < int2; int3++) {
 for (int int4 = 0; int4 < int1; int4++) {
 BufferedImage bufferedImage = this->getBufferedImage(mipMapLevel, int4, int3, short0);
 this->writeImageToFile(bufferedImage, outputDirectory, int4, int3, int0);
 }
 }
 }
 }
 }

 FileSystem openZipFile() {
 try {
 return FileSystems.newFileSystem(Paths.get(this->m_zipFile);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 return nullptr;
 }
 }

 void generateZip(const std::string& imageFile, const std::string& zipFile) {
 ImageData imageData = new ImageData(imageFile);
 if (imageData != nullptr) {
 short short0 = 256;

 try (
 FileOutputStream fileOutputStream = new FileOutputStream(zipFile);
 BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(fileOutputStream);
 ZipOutputStream zipOutputStream = new ZipOutputStream(bufferedOutputStream);
 ) {
 uint8_t byte0 = 5;

 for (int int0 = 0; int0 < byte0; int0++) {
 MipMapLevel mipMapLevel = imageData.getMipMapData(int0);
 float float0 = (float)imageData.getWidth() / (1 << int0);
 float float1 = (float)imageData.getHeight() / (1 << int0);
 int int1 = (int)Math.ceil(float0 / short0);
 int int2 = (int)Math.ceil(float1 / short0);

 for (int int3 = 0; int3 < int2; int3++) {
 for (int int4 = 0; int4 < int1; int4++) {
 BufferedImage bufferedImage = this->getBufferedImage(mipMapLevel, int4, int3, short0);
 this->writeImageToZip(bufferedImage, zipOutputStream, int4, int3, int0);
 }
 }

 if (float0 <= short0 && float1 <= short0) {
 break;
 }
 }
 }
 }
 }

 BufferedImage getBufferedImage(MipMapLevel mipMapLevel, int int3, int int2, int int0) {
 BufferedImage bufferedImage = new BufferedImage(int0, int0, 2);
 int[] ints = new int[int0];
 IntBuffer intBuffer = mipMapLevel.getBuffer().asIntBuffer();

 for (int int1 = 0; int1 < int0; int1++) {
 intBuffer.get(int3 * int0 + (int2 * int0 + int1) * mipMapLevel.width, ints);

 for (int int4 = 0; int4 < int0; int4++) {
 int int5 = ints[int4];
 int int6 = int5 & 0xFF;
 int int7 = int5 >> 8 & 0xFF;
 int int8 = int5 >> 16 & 0xFF;
 int int9 = int5 >> 24 & 0xFF;
 ints[int4] = int9 << 24 | int6 << 16 | int7 << 8 | int8;
 }

 bufferedImage.setRGB(0, int1, int0, 1, ints, 0, int0);
 }

 return bufferedImage;
 }

 void writeImageToFile(BufferedImage bufferedImage, const std::string& string, int int2, int int1, int int0) {
 File file = new File(string + File.separator + int0);
 if (file.exists() || file.mkdirs()) {
 file = new File(file, String.format("tile%dx%d.png", int2, int1);
 ImageIO.write(bufferedImage, "png", file);
 }
 }

 void writeImageToZip(BufferedImage bufferedImage, ZipOutputStream zipOutputStream, int int1, int int0, int int2) {
 zipOutputStream.putNextEntry(new ZipEntry(String.format("%d/tile%dx%d.png", int2, int1, int0);
 ImageIO.write(bufferedImage, "PNG", zipOutputStream);
 zipOutputStream.closeEntry();
 }

 ImagePyramid.PyramidTexture checkTextureCache(String string) {
 if (this->m_textures.size() < this->MAX_TEXTURES) {
 ImagePyramid.PyramidTexture pyramidTexture0 = new ImagePyramid.PyramidTexture();
 pyramidTexture0.m_key = string;
 pyramidTexture0.m_requestNumber = this->m_requestNumber++;
 this->m_textures.put(string, pyramidTexture0);
 if (this->m_requestNumber >= this->MAX_REQUEST_NUMBER) {
 this->resetRequestNumbers();
 }

 return pyramidTexture0;
 } else {
 ImagePyramid.PyramidTexture pyramidTexture1 = nullptr;

 for (ImagePyramid.PyramidTexture pyramidTexture2 : this->m_textures.values()) {
 if (pyramidTexture1 == nullptr || pyramidTexture1.m_requestNumber > pyramidTexture2.m_requestNumber) {
 pyramidTexture1 = pyramidTexture2;
 }
 }

 this->m_textures.remove(pyramidTexture1.m_key);
 pyramidTexture1.m_key = string;
 pyramidTexture1.m_requestNumber = this->m_requestNumber++;
 this->m_textures.put(pyramidTexture1.m_key, pyramidTexture1);
 if (this->m_requestNumber >= this->MAX_REQUEST_NUMBER) {
 this->resetRequestNumbers();
 }

 return pyramidTexture1;
 }
 }

 void resetRequestNumbers() {
 std::vector arrayList = new ArrayList<>(this->m_textures.values());
 arrayList.sort(Comparator.comparingInt(pyramidTexturex -> pyramidTexturex.m_requestNumber);
 this->m_requestNumber = 1;

 for (ImagePyramid.PyramidTexture pyramidTexture : arrayList) {
 pyramidTexture.m_requestNumber = this->m_requestNumber++;
 }

 arrayList.clear();
 }

 void readInfoFile() {
 if (this->m_zipFS != nullptr && this->m_zipFS.isOpen()) {
 Path path = this->m_zipFS.getPath("pyramid.txt");

 std::string string;
 try (
 InputStream inputStream = Files.newInputStream(path);
 InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
 BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
 ) {
 while ((string = bufferedReader.readLine()) != nullptr) {
 if (string.startsWith("VERSION=")) {
 string = string.substring("VERSION=".length());
 } else if (string.startsWith("bounds=")) {
 string = string.substring("bounds=".length());
 String[] strings = string.split(" ");
 if (strings.length == 4) {
 this->m_minX = PZMath.tryParseInt(strings[0], -1);
 this->m_minY = PZMath.tryParseInt(strings[1], -1);
 this->m_maxX = PZMath.tryParseInt(strings[2], -1);
 this->m_maxY = PZMath.tryParseInt(strings[3], -1);
 }
 } else if (string.startsWith("resolution=")) {
 string = string.substring("resolution=".length());
 this->m_resolution = PZMath.tryParseFloat(string, 1.0F);
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
 }

 void destroy() {
 if (this->m_zipFS != nullptr) {
 try {
 this->m_zipFS.close();
 } catch (IOException iOException) {
 }

 this->m_zipFS = nullptr;
 }

 RenderThread.invokeOnRenderContext(() -> {
 for (ImagePyramid.PyramidTexture pyramidTexture : this->m_textures.values()) {
 pyramidTexture.m_textureID.destroy();
 }
 });
 this->m_missing.clear();
 this->m_textures.clear();
 }

 public static class PyramidTexture {
 std::string m_key;
 int m_requestNumber;
 TextureID m_textureID;
 }
}
} // namespace worldMap
} // namespace zombie
