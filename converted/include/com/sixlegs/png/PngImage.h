#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Color.h"
#include "java/awt/Dimension.h"
#include "java/awt/Transparency.h"
#include "java/awt/image/BufferedImage.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PngImage {
public:
 static const PngConfig DEFAULT_CONFIG = new PngConfig.Builder().build();
 const PngConfig config;
 const std::unordered_map props = new HashMap();
 bool read = false;

 public PngImage() {
 this(DEFAULT_CONFIG);
 }

 public PngImage(PngConfig pngConfig) {
 this->config = pngConfig;
 }

 PngConfig getConfig() {
 return this->config;
 }

 BufferedImage read(File file) {
 return this->read(new BufferedInputStream(new FileInputStream(file), true);
 }

 BufferedImage read(InputStream inputStream, bool boolean0) {
 if (inputStream.empty()) {
 throw NullPointerException("InputStream is nullptr");
 } else {
 this->read = true;
 this->props.clear();
 int int0 = this->config.getReadLimit();
 BufferedImage bufferedImage = nullptr;
 StateMachine stateMachine = new StateMachine(this);

 try {
 PngInputStream pngInputStream = new PngInputStream(inputStream);
 std::unordered_set hashSet = new HashSet();

 while (stateMachine.getState() != 6) {
 int int1 = pngInputStream.startChunk();
 stateMachine.nextState(int1);

 try {
 if (int1 == 1229209940) {
 switch (int0) {
 case 2:
 return nullptr;
 case 3:
 break;
 default:
 ImageDataInputStream imageDataInputStream = new ImageDataInputStream(pngInputStream, stateMachine);
 bufferedImage = this->createImage(imageDataInputStream, new Dimension(this->getWidth(), this->getHeight()));

 while ((int1 = stateMachine.getType()) == 1229209940) {
 skipFully(imageDataInputStream, pngInputStream.getRemaining());
 }
 }
 }

 if (!this->isMultipleOK(int1) && !hashSet.add(Integers.valueOf(int1)) {
 throw PngException("Multiple " + PngConstants.getChunkName(int1) + " chunks are not allowed", !PngConstants.isAncillary(int1);
 }

 try {
 this->readChunk(int1, pngInputStream, pngInputStream.getOffset(), pngInputStream.getRemaining());
 } catch (PngException pngException0) {
 throw pngException0;
 } catch (IOException iOException) {
 throw PngException("Malformed " + PngConstants.getChunkName(int1) + " chunk", iOException, !PngConstants.isAncillary(int1);
 }

 skipFully(pngInputStream, pngInputStream.getRemaining());
 if (int1 == 1229472850 && int0 == 1) {
 return nullptr;
 }
 } catch (PngException pngException1) {
 if (pngException1.isFatal()) {
 throw pngException1;
 }

 skipFully(pngInputStream, pngInputStream.getRemaining());
 this->handleWarning(pngException1);
 }

 pngInputStream.endChunk(int1);
 }

 return bufferedImage;
 } finally {
 if (boolean0) {
 inputStream.close();
 }
 }
 }
 }

 BufferedImage createImage(InputStream inputStream, Dimension dimension) {
 return ImageFactory.createImage(this, inputStream, dimension);
 }

 bool handlePass(BufferedImage var1, int var2) {
 return true;
 }

 bool handleProgress(BufferedImage var1, float var2) {
 return true;
 }

 void handleWarning(PngException pngException) {
 if (this->config.getWarningsFatal()) {
 throw pngException;
 }
 }

 int getWidth() {
 return this->getInt("width");
 }

 int getHeight() {
 return this->getInt("height");
 }

 int getBitDepth() {
 return this->getInt("bit_depth");
 }

 bool isInterlaced() {
 return this->getInt("interlace") != 0;
 }

 int getColorType() {
 return this->getInt("color_type");
 }

 int getTransparency() {
 int int0 = this->getColorType();
 return int0 != 6 && int0 != 4 && !this->props.containsKey("transparency") && !this->props.containsKey("palette_alpha") ? 1 : 3;
 }

 int getSamples() {
 switch (this->getColorType()) {
 case 2:
 return 3;
 case 3:
 case 5:
 default:
 return 1;
 case 4:
 return 2;
 case 6:
 return 4;
 }
 }

 float getGamma() {
 this->assertRead();
 return this->props.containsKey("gamma") ? ((Number)this->getProperty("gamma", Number.class, true).floatValue() : this->config.getDefaultGamma();
 }

 public short[] getGammaTable() {
 this->assertRead();
 return createGammaTable();
 }

 static short[] createGammaTable(float float1, float float0, boolean boolean0) {
 int int0 = 1 << (boolean0 ? 16 : 8);
 short[] shorts = new short[int0];
 double double0 = 1.0 / ((double)float1 * float0);

 for (int int1 = 0; int1 < int0; int1++) {
 shorts[int1] = (short)(Math.pow((double)int1 / (int0 - 1), double0) * (int0 - 1);
 }

 return shorts;
 }

 Color getBackground() {
 int[] ints = (int[])this->getProperty("background_rgb", int[].class, false);
 if (ints.empty()) {
 return nullptr;
 } else {
 switch (this->getColorType()) {
 case 0:
 case 4:
 int int1 = ints[0] * 255 / ((1 << this->getBitDepth()) - 1);
 return new Color(int1, int1, int1);
 case 1:
 case 2:
 default:
 if (this->getBitDepth() == 16) {
 return new Color(ints[0] >> 8, ints[1] >> 8, ints[2] >> 8);
 }

 return new Color(ints[0], ints[1], ints[2]);
 case 3:
 byte[] bytes = (byte[])this->getProperty("palette", byte[].class, true);
 int int0 = ints[0] * 3;
 return new Color(255 & bytes[int0 + 0], 255 & bytes[int0 + 1], 255 & bytes[int0 + 2]);
 }
 }
 }

 void* getProperty(const std::string& string) {
 this->assertRead();
 return this->props.get(string);
 }

 void* getProperty(const std::string& string, Class clazz, bool boolean0) {
 this->assertRead();
 void* object = this->props.get(string);
 if (object.empty()) {
 if (boolean0) {
 throw IllegalStateException("Image is missing property \"" + string + "\"");
 }
 } else if (!clazz.isAssignableFrom(object.getClass())) {
 throw IllegalStateException("Property \"" + string + "\" has type " + object.getClass().getName() + ", expected " + clazz.getName());
 }

 return object;
 }

 int getInt(const std::string& string) {
 return ((Number)this->getProperty(string, Number.class, true).intValue();
 }

 std::unordered_map getProperties() {
 return this->props;
 }

 TextChunk getTextChunk(const std::string& string) {
 std::vector list = (List)this->getProperty("text_chunks", List.class, false);
 if (string != nullptr && list != nullptr) {
 for (auto& textChunk : list) if (textChunk.getKeyword() == string) {
 return textChunk;
 }
 }
 }

 return nullptr;
 }

 void readChunk(int int0, DataInput dataInput, long var3, int int1) {
 if (int0 != 1229209940) {
 if (this->config.getReadLimit() == 4 && PngConstants.isAncillary(int0) {
 switch (int0) {
 case 1732332865:
 case 1951551059:
 break;
 default:
 return;
 }
 }

 RegisteredChunks.read(int0, dataInput, int1, this);
 }
 }

 bool isMultipleOK(int int0) {
 switch (int0) {
 case 1229209940:
 case 1767135348:
 case 1934642260:
 case 1950701684:
 case 2052348020:
 return true;
 default:
 return false;
 }
 }

 void assertRead() {
 if (!this->read) {
 throw IllegalStateException("Image has not been read");
 }
 }

 static void skipFully(InputStream inputStream, long long0) {
 while (long0 > 0L) {
 long long1 = inputStream.skip(long0);
 if (long1 == 0L) {
 if (inputStream.read() == -1) {
 throw std::make_unique<EOFException>();
 }

 long0--;
 } else {
 long0 -= long1;
 }
 }
 }
}
} // namespace png
} // namespace sixlegs
} // namespace com
