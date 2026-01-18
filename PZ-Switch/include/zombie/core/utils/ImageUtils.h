#pragma once
#include "java/awt/image/BufferedImage.h"
#include "java/awt/image/WritableRaster.h"
#include "javax/imageio/ImageIO.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/Core.h"
#include "zombie/core/textures/Texture.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ImageUtils {
public:
 static bool USE_MIPMAP = true;

private
 ImageUtils() {}

 static void depureTexture(Texture texture, float float0) {
 WrappedBuffer wrappedBuffer = texture.getData();
 ByteBuffer byteBuffer = wrappedBuffer.getBuffer();
 byteBuffer.rewind();
 int int0 = (int)(float0 * 255.0F);
 long long0 = texture.getWidthHW() * texture.getHeightHW();

 for (int int1 = 0; int1 < long0; int1++) {
 byteBuffer.mark();
 byteBuffer.get();
 byteBuffer.get();
 byteBuffer.get();
 uint8_t byte0 = byteBuffer.get();
 int int2;
 if (byte0 < 0) {
 int2 = 256 + byte0;
 } else {
 int2 = byte0;
 }

 if (int2 < int0) {
 byteBuffer.reset();
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 }
 }

 byteBuffer.flip();
 texture.setData(byteBuffer);
 wrappedBuffer.dispose();
 }

 static int getNextPowerOfTwo(int int0) {
 uint8_t byte0 = 2;

 while (byte0 < int0) {
 byte0 += byte0;
 }

 return byte0;
 }

 static int getNextPowerOfTwoHW(int int0) {
 uint8_t byte0 = 2;

 while (byte0 < int0) {
 byte0 += byte0;
 }

 return byte0;
 }

 static Texture getScreenShot() {
 Texture texture = new Texture(Core.getInstance().getScreenWidth(),
 Core.getInstance().getScreenHeight(), 0);
 IntBuffer intBuffer = org.lwjglx.BufferUtils.createIntBuffer(4);
 texture.bind();
 intBuffer.rewind();
 GL11.glTexParameteri(3553, 10241, 9729);
 GL11.glTexParameteri(3553, 10240, 9729);
 GL11.glCopyTexImage2D(3553, 0, 6408, 0, 0, texture.getWidthHW(),
 texture.getHeightHW(), 0);
 return texture;
 }

 static ByteBuffer makeTransp(ByteBuffer byteBuffer, int int0, int int1,
 int int2, int int3, int int4) {
 return makeTransp();
 }

 static ByteBuffer makeTransp(ByteBuffer byteBuffer, int int6, int int5,
 int int4, int int7, int int3, int int1) {
 byteBuffer.rewind();

 for (int int0 = 0; int0 < int1; int0++) {
 for (int int2 = 0; int2 < int3; int2++) {
 uint8_t byte0 = byteBuffer.get();
 uint8_t byte1 = byteBuffer.get();
 uint8_t byte2 = byteBuffer.get();
 if (byte0 == (byte)int6 && byte1 == (byte)int5 && byte2 == (byte)int4) {
 byteBuffer.put((byte)int7);
 } else {
 byteBuffer.get();
 }
 }
 }

 byteBuffer.rewind();
 return byteBuffer;
 }

 static void saveBmpImage(Texture texture, const std::string &string) {
 saveImage(texture, string, "bmp");
 }

 static void saveImage(Texture texture, const std::string &string,
 const std::string &var2) {
 BufferedImage bufferedImage =
 new BufferedImage(texture.getWidth(), texture.getHeight(), 1);
 WritableRaster writableRaster = bufferedImage.getRaster();
 WrappedBuffer wrappedBuffer = texture.getData();
 ByteBuffer byteBuffer = wrappedBuffer.getBuffer();
 byteBuffer.rewind();

 for (int int0 = 0;
 int0 < texture.getHeightHW() && int0 < texture.getHeight(); int0++) {
 for (int int1 = 0; int1 < texture.getWidthHW(); int1++) {
 if (int1 >= texture.getWidth()) {
 byteBuffer.get();
 byteBuffer.get();
 byteBuffer.get();
 byteBuffer.get();
 } else {
 writableRaster.setPixel(
 int1, texture.getHeight() - 1 - int0,
 new int[]{byteBuffer.get(), byteBuffer.get(), byteBuffer.get()});
 byteBuffer.get();
 }
 }
 }

 wrappedBuffer.dispose();

 try {
 ImageIO.write(bufferedImage, "png", new File(string);
 } catch (IOException iOException) {
 }
 }

 static void saveJpgImage(Texture texture, const std::string &string) {
 saveImage(texture, string, "jpg");
 }

 static void savePngImage(Texture texture, const std::string &string) {
 saveImage(texture, string, "png");
 }
}
} // namespace utils
} // namespace core
} // namespace zombie
