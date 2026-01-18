#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/textures/TexturePackPage.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace fileSystem {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TexturePackDevice {
public:
 static const int VERSION1 = 1;
 static const int VERSION_LATEST = 1;
 std::string m_name;
 std::string m_filename;
 int m_version = -1;
 ArrayList<TexturePackDevice.Page> m_pages =
 std::make_unique<ArrayList<>>();
 HashMap<String, TexturePackDevice.Page> m_pagemap =
 std::make_unique<HashMap<>>();
 HashMap<String, TexturePackDevice.SubTexture> m_submap =
 std::make_unique<HashMap<>>();
 int m_textureFlags;

 static long skipInput(InputStream inputStream, long long1) {
 long long0 = 0L;

 while (long0 < long1) {
 long long2 = inputStream.skip(long1 - long0);
 if (long2 > 0L) {
 long0 += long2;
 }
 }

 return long0;
 }

public
 TexturePackDevice(const std::string &string, int int0) {
 this->m_name = string;
 this->m_filename = ZomboidFileSystem.instance.getString(
 "media/texturepacks/" + string + ".pack");
 this->m_textureFlags = int0;
 }

 IFile createFile(IFile var1) { return nullptr; }

 void destroyFile(IFile var1) {}

 InputStream createStream(const std::string &string, InputStream var2) {
 this->initMetaData();
 return new TexturePackDevice.TexturePackInputStream(string, this);
 }

 void destroyStream(InputStream inputStream) {
 if (inputStream instanceof TexturePackDevice.TexturePackInputStream) {
 }
 }

 std::string name() { return this->m_name; }

 void getSubTextureInfo(FileSystem.TexturePackTextures texturePackTextures) {
 this->initMetaData();

 for (TexturePackDevice.SubTexture subTexture0 : this->m_submap.values()) {
 FileSystem.SubTexture subTexture1 = new FileSystem.SubTexture(
 this->name(), subTexture0.m_page.m_name, subTexture0.m_info);
 texturePackTextures.put(subTexture0.m_info.name, subTexture1);
 }
 }

 void initMetaData() {
 if (this->m_pages.empty()) {
 try(FileInputStream fileInputStream =
 new FileInputStream(this->m_filename);
 BufferedInputStream bufferedInputStream =
 new BufferedInputStream(fileInputStream);
 TexturePackDevice.PositionInputStream positionInputStream =
 new TexturePackDevice.PositionInputStream(bufferedInputStream);) {
 positionInputStream.mark(4);
 int int0 = positionInputStream.read();
 int int1 = positionInputStream.read();
 int int2 = positionInputStream.read();
 int int3 = positionInputStream.read();
 if (int0 == 80 && int1 == 90 && int2 == 80 && int3 == 75) {
 this->m_version = TexturePackPage.readInt(positionInputStream);
 if (this->m_version < 1 || this->m_version > 1) {
 throw IOException("invalid .pack file version " +
 this->m_version);
 }
 } else {
 positionInputStream.reset();
 this->m_version = 0;
 }

 int int4 = TexturePackPage.readInt(positionInputStream);

 for (int int5 = 0; int5 < int4; int5++) {
 TexturePackDevice.Page page = this->readPage(positionInputStream);
 this->m_pages.add(page);
 this->m_pagemap.put(page.m_name, page);

 for (TexturePackPage.SubTextureInfo subTextureInfo : page.m_sub) {
 this->m_submap.put(
 subTextureInfo.name,
 new TexturePackDevice.SubTexture(page, subTextureInfo);
 }
 }
 }
 }
 }

private
 TexturePackDevice.Page
 readPage(TexturePackDevice.PositionInputStream positionInputStream) throws
 IOException {
 TexturePackDevice.Page page = new TexturePackDevice.Page();
 std::string string0 = TexturePackPage.ReadString(positionInputStream);
 int int0 = TexturePackPage.readInt(positionInputStream);
 bool boolean0 = TexturePackPage.readInt(positionInputStream) != 0;
 page.m_name = string0;
 page.m_has_alpha = boolean0;

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string1 = TexturePackPage.ReadString(positionInputStream);
 int int2 = TexturePackPage.readInt(positionInputStream);
 int int3 = TexturePackPage.readInt(positionInputStream);
 int int4 = TexturePackPage.readInt(positionInputStream);
 int int5 = TexturePackPage.readInt(positionInputStream);
 int int6 = TexturePackPage.readInt(positionInputStream);
 int int7 = TexturePackPage.readInt(positionInputStream);
 int int8 = TexturePackPage.readInt(positionInputStream);
 int int9 = TexturePackPage.readInt(positionInputStream);
 page.m_sub.add(new TexturePackPage.SubTextureInfo(
 int2, int3, int4, int5, int6, int7, int8, int9, string1);
 }

 page.m_png_start = positionInputStream.getPosition();
 if (this->m_version == 0) {
 int int10 = 0;

 do {
 int10 = TexturePackPage.readIntByte(positionInputStream);
 } while (int10 != -559038737);
 } else {
 int int11 = TexturePackPage.readInt(positionInputStream);
 skipInput(positionInputStream, int11);
 }

 return page;
 }

 bool isAlpha(const std::string &string) {
 TexturePackDevice.Page page = this->m_pagemap.get(string);
 return page.m_has_alpha;
 }

 int getTextureFlags() { return this->m_textureFlags; }

 static class Page {
 std::string m_name;
 bool m_has_alpha = false;
 long m_png_start = -1L;
 ArrayList<TexturePackPage.SubTextureInfo> m_sub =
 std::make_unique<ArrayList<>>();
 }

 class PositionInputStream extends FilterInputStream {
 long pos = 0L;
 long mark = 0L;

 public
 PositionInputStream(InputStream inputStream) { super(inputStream); }

 public
 long getPosition() { return this->pos; }

 public
 int read() throws IOException {
 int int0 = super.read();
 if (int0 >= 0) {
 this->pos++;
 }

 return int0;
 }

 public
 int read(byte[] bytes, int int1, int int2) throws IOException {
 int int0 = super.read(bytes, int1, int2);
 if (int0 > 0) {
 this->pos += int0;
 }

 return int0;
 }

 public
 long skip(long long1) throws IOException {
 long long0 = super.skip(long1);
 if (long0 > 0L) {
 this->pos += long0;
 }

 return long0;
 }

 public
 void mark(int int0) {
 super.mark(int0);
 this->mark = this->pos;
 }

 public
 void reset() throws IOException {
 if (!this->markSupported()) {
 throw IOException("Mark not supported.");
 } else {
 super.reset();
 this->pos = this->mark;
 }
 }
 }

 static class SubTexture {
 TexturePackDevice.Page m_page;
 TexturePackPage.SubTextureInfo m_info;

 SubTexture(TexturePackDevice.Page page,
 TexturePackPage.SubTextureInfo subTextureInfo) {
 this->m_page = page;
 this->m_info = subTextureInfo;
 }
 }

 static class TexturePackInputStream extends FileInputStream {
 TexturePackDevice m_device;

 TexturePackInputStream(
 String string, TexturePackDevice texturePackDevice) throws IOException {
 super(texturePackDevice.m_filename);
 this->m_device = texturePackDevice;
 TexturePackDevice.Page page = this->m_device.m_pagemap.get(string);
 if (page.empty()) {
 throw std::make_unique<FileNotFoundException>();
 } else {
 TexturePackDevice.skipInput(this, page.m_png_start);
 if (texturePackDevice.m_version >= 1) {
 int int0 = TexturePackPage.readInt(this);
 }
 }
 }
 }
}
} // namespace fileSystem
} // namespace zombie
