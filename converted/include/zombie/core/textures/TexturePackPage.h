#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URISyntaxException.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TexturePackPage {
public:
 public static HashMap<String, Stack<String>> FoundTextures = std::make_unique<HashMap<>>();
 public static HashMap<String, Texture> subTextureMap = std::make_unique<HashMap<>>();
 public static HashMap<String, Texture> subTextureMap2 = std::make_unique<HashMap<>>();
 public static HashMap<String, TexturePackPage> texturePackPageMap = std::make_unique<HashMap<>>();
 public static HashMap<String, String> TexturePackPageNameMap = std::make_unique<HashMap<>>();
 public HashMap<String, Texture> subTextures = std::make_unique<HashMap<>>();
 Texture tex = nullptr;
 static ByteBuffer SliceBuffer = nullptr;
 static bool bHasCache = false;
 static int percent = 0;
 static int chl1 = 0;
 static int chl2 = 0;
 static int chl3 = 0;
 static int chl4 = 0;
 static StringBuilder v = new StringBuilder(50);
 public static ArrayList<TexturePackPage.SubTextureInfo> TempSubTextureInfo = std::make_unique<ArrayList<>>();
 public static ArrayList<String> tempFilenameCheck = std::make_unique<ArrayList<>>();
 static bool bIgnoreWorldItemTextures = true;

 static void LoadDir(const std::string& var0) {
 }

 static void searchFolders(File var0) {
 }

 static Texture getTexture(const std::string& string) {
 if (string.contains(".png")) {
 return Texture.getSharedTexture(string);
 } else {
 return subTextureMap.containsKey(string) ? subTextureMap.get(string) : nullptr;
 }
 }

 static int readInt(InputStream inputStream) {
 int int0 = inputStream.read();
 int int1 = inputStream.read();
 int int2 = inputStream.read();
 int int3 = inputStream.read();
 chl1 = int0;
 chl2 = int1;
 chl3 = int2;
 chl4 = int3;
 if ((int0 | int1 | int2 | int3) < 0) {
 throw std::make_unique<EOFException>();
 } else {
 return (int0 << 0) + (int1 << 8) + (int2 << 16) + (int3 << 24);
 }
 }

 static int readInt(ByteBuffer byteBuffer) {
 uint8_t byte0 = byteBuffer.get();
 uint8_t byte1 = byteBuffer.get();
 uint8_t byte2 = byteBuffer.get();
 uint8_t byte3 = byteBuffer.get();
 chl1 = byte0;
 chl2 = byte1;
 chl3 = byte2;
 chl4 = byte3;
 return (byte0 << 0) + (byte1 << 8) + (byte2 << 16) + (byte3 << 24);
 }

 static int readIntByte(InputStream inputStream) {
 int int0 = chl2;
 int int1 = chl3;
 int int2 = chl4;
 int int3 = inputStream.read();
 chl1 = int0;
 chl2 = int1;
 chl3 = int2;
 chl4 = int3;
 if ((int0 | int1 | int2 | int3) < 0) {
 throw std::make_unique<EOFException>();
 } else {
 return (int0 << 0) + (int1 << 8) + (int2 << 16) + (int3 << 24);
 }
 }

 static std::string ReadString(InputStream inputStream) {
 v.setLength(0);
 int int0 = readInt(inputStream);

 for (int int1 = 0; int1 < int0; int1++) {
 v.append((char)inputStream.read());
 }

 return v.toString();
 }

 void loadFromPackFileDDS(BufferedInputStream bufferedInputStream) {
 std::string string0 = ReadString(bufferedInputStream);
 tempFilenameCheck.add(string0);
 int int0 = readInt(bufferedInputStream);
 bool boolean0 = readInt(bufferedInputStream) != 0;
 TempSubTextureInfo.clear();

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string1 = ReadString(bufferedInputStream);
 int int2 = readInt(bufferedInputStream);
 int int3 = readInt(bufferedInputStream);
 int int4 = readInt(bufferedInputStream);
 int int5 = readInt(bufferedInputStream);
 int int6 = readInt(bufferedInputStream);
 int int7 = readInt(bufferedInputStream);
 int int8 = readInt(bufferedInputStream);
 int int9 = readInt(bufferedInputStream);
 if (string1.contains("ZombieWalk") && string1.contains("BobZ_")) {
 TempSubTextureInfo.add(new TexturePackPage.SubTextureInfo(int2, int3, int4, int5, int6, int7, int8, int9, string1);
 }
 }

 if (TempSubTextureInfo.empty()) {
 int int10 = 0;

 do {
 int10 = readIntByte(bufferedInputStream);
 } while (int10 != -559038737);
 } else {
 Texture texture0 = new Texture(string0, bufferedInputStream, boolean0, Texture.PZFileformat.DDS);

 for (int int11 = 0; int11 < TempSubTextureInfo.size(); int11++) {
 TexturePackPage.SubTextureInfo subTextureInfo = TempSubTextureInfo.get(int11);
 Texture texture1 = texture0.split(subTextureInfo.x, subTextureInfo.y, subTextureInfo.w, subTextureInfo.h);
 texture1.copyMaskRegion(texture0, subTextureInfo.x, subTextureInfo.y, subTextureInfo.w, subTextureInfo.h);
 texture1.setName(subTextureInfo.name);
 this->subTextures.put(subTextureInfo.name, texture1);
 subTextureMap.put(subTextureInfo.name, texture1);
 texture1.offsetX = subTextureInfo.ox;
 texture1.offsetY = subTextureInfo.oy;
 texture1.widthOrig = subTextureInfo.fx;
 texture1.heightOrig = subTextureInfo.fy;
 }

 texture0.mask = nullptr;
 texturePackPageMap.put(string0, this);
 int int12 = 0;

 do {
 int12 = readIntByte(bufferedInputStream);
 } while (int12 != -559038737);
 }
 }

 void loadFromPackFile(BufferedInputStream bufferedInputStream) {
 std::string string0 = ReadString(bufferedInputStream);
 tempFilenameCheck.add(string0);
 int int0 = readInt(bufferedInputStream);
 bool boolean0 = readInt(bufferedInputStream) != 0;
 if (boolean0) {
 bool boolean1 = false;
 }

 TempSubTextureInfo.clear();

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string1 = ReadString(bufferedInputStream);
 int int2 = readInt(bufferedInputStream);
 int int3 = readInt(bufferedInputStream);
 int int4 = readInt(bufferedInputStream);
 int int5 = readInt(bufferedInputStream);
 int int6 = readInt(bufferedInputStream);
 int int7 = readInt(bufferedInputStream);
 int int8 = readInt(bufferedInputStream);
 int int9 = readInt(bufferedInputStream);
 if (!bIgnoreWorldItemTextures || !string1.startsWith("WItem_")) {
 TempSubTextureInfo.add(new TexturePackPage.SubTextureInfo(int2, int3, int4, int5, int6, int7, int8, int9, string1);
 }
 }

 Texture texture0 = new Texture(string0, bufferedInputStream, boolean0);

 for (int int10 = 0; int10 < TempSubTextureInfo.size(); int10++) {
 TexturePackPage.SubTextureInfo subTextureInfo = TempSubTextureInfo.get(int10);
 Texture texture1 = texture0.split(subTextureInfo.x, subTextureInfo.y, subTextureInfo.w, subTextureInfo.h);
 texture1.copyMaskRegion(texture0, subTextureInfo.x, subTextureInfo.y, subTextureInfo.w, subTextureInfo.h);
 texture1.setName(subTextureInfo.name);
 this->subTextures.put(subTextureInfo.name, texture1);
 subTextureMap.put(subTextureInfo.name, texture1);
 texture1.offsetX = subTextureInfo.ox;
 texture1.offsetY = subTextureInfo.oy;
 texture1.widthOrig = subTextureInfo.fx;
 texture1.heightOrig = subTextureInfo.fy;
 }

 texture0.mask = nullptr;
 texturePackPageMap.put(string0, this);
 int int11 = 0;

 do {
 int11 = readIntByte(bufferedInputStream);
 } while (int11 != -559038737);
 }

 public static class SubTextureInfo {
 int w;
 int h;
 int x;
 int y;
 int ox;
 int oy;
 int fx;
 int fy;
 std::string name;

 public SubTextureInfo(int _x, int _y, int _w, int _h, int _ox, int _oy, int _fx, int _fy, const std::string& _name) {
 this->x = _x;
 this->y = _y;
 this->w = _w;
 this->h = _h;
 this->ox = _ox;
 this->oy = _oy;
 this->fx = _fx;
 this->fy = _fy;
 this->name = _name;
 }
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
