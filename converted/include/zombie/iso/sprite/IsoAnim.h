#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"

namespace zombie {
namespace iso {
namespace sprite {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoAnim {
public:
 public static HashMap<String, IsoAnim> GlobalAnimMap = std::make_unique<HashMap<>>();
 short FinishUnloopedOnFrame = 0;
 short FrameDelay = 0;
 short LastFrame = 0;
 public ArrayList<IsoDirectionFrame> Frames = new ArrayList<>(8);
 std::string name;
 bool looped = true;
 int ID = 0;
 private static ThreadLocal<StringBuilder> tlsStrBuf = std::make_unique<ThreadLocal<StringBuilder>>() {
 StringBuilder initialValue() {
 return std::make_unique<StringBuilder>();
 }
 };
 public IsoDirectionFrame[] FramesArray = new IsoDirectionFrame[0];

 static void DisposeAll() {
 GlobalAnimMap.clear();
 }

 void LoadExtraFrame(const std::string& string2, const std::string& string0, int int0) {
 this->name = string0;
 std::string string1 = string2 + "_";
 std::string string3 = "_" + string0 + "_";
 int integer = new Integer(int0);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(
 Texture.getSharedTexture(string1 + "8" + string3 + integer.toString() + ".png"),
 Texture.getSharedTexture(string1 + "9" + string3 + integer.toString() + ".png"),
 Texture.getSharedTexture(string1 + "6" + string3 + integer.toString() + ".png"),
 Texture.getSharedTexture(string1 + "3" + string3 + integer.toString() + ".png"),
 Texture.getSharedTexture(string1 + "2" + string3 + integer.toString() + ".png")
 );
 this->Frames.add(directionFrame);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesReverseAltName(const std::string& ObjectName, const std::string& AnimName, const std::string& AltName, int nFrames) {
 this->name = AltName;
 StringBuilder stringBuilder = tlsStrBuf.get();
 stringBuilder.setLength(0);
 stringBuilder.append(ObjectName);
 stringBuilder.append("_%_");
 stringBuilder.append(AnimName);
 stringBuilder.append("_^");
 int int0 = stringBuilder.lastIndexOf("^");
 int int1 = stringBuilder.indexOf("_%_") + 1;
 stringBuilder.setCharAt(int1, '9');
 stringBuilder.setCharAt(int0, '0');
 if (GameServer.bServer && !ServerGUI.isCreated()) {
 for (int int2 = 0; int2 < nFrames; int2++) {
 this->Frames.add(new IsoDirectionFrame(nullptr);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 Texture texture = Texture.getSharedTexture(stringBuilder.toString());
 if (texture != nullptr) {
 for (int int3 = 0; int3 < nFrames; int3++) {
 if (int3 == 10) {
 stringBuilder.setLength(0);
 stringBuilder.append(ObjectName);
 stringBuilder.append("_1_");
 stringBuilder.append(AnimName);
 stringBuilder.append("_10");
 }

 int integer = int3;
 void* object = nullptr;
 std::string string0 = integer.toString();
 if (texture == nullptr) {
 stringBuilder.setCharAt(int1, '8');

 try {
 stringBuilder.setCharAt(int0, integer.toString().charAt(0);
 } catch (Exception exception) {
 this->LoadFramesReverseAltName(ObjectName, AnimName, AltName, nFrames);
 }

 std::string string1 = stringBuilder.toString();
 stringBuilder.setCharAt(int1, '9');
 std::string string2 = stringBuilder.toString();
 stringBuilder.setCharAt(int1, '6');
 std::string string3 = stringBuilder.toString();
 stringBuilder.setCharAt(int1, '3');
 std::string string4 = stringBuilder.toString();
 stringBuilder.setCharAt(int1, '2');
 std::string string5 = stringBuilder.toString();
 object = new IsoDirectionFrame(
 Texture.getSharedTexture(string1),
 Texture.getSharedTexture(string2),
 Texture.getSharedTexture(string3),
 Texture.getSharedTexture(string4),
 Texture.getSharedTexture(string5)
 );
 } else {
 stringBuilder.setCharAt(int1, '9');

 for (int int4 = 0; int4 < string0.length(); int4++) {
 stringBuilder.setCharAt(int0 + int4, string0.charAt(int4);
 }

 std::string string6 = stringBuilder.toString();
 stringBuilder.setCharAt(int1, '6');
 std::string string7 = stringBuilder.toString();
 stringBuilder.setCharAt(int1, '3');
 std::string string8 = stringBuilder.toString();
 stringBuilder.setCharAt(int1, '2');
 std::string string9 = stringBuilder.toString();
 stringBuilder.setCharAt(int1, '1');
 std::string string10 = stringBuilder.toString();
 stringBuilder.setCharAt(int1, '4');
 std::string string11 = stringBuilder.toString();
 stringBuilder.setCharAt(int1, '7');
 std::string string12 = stringBuilder.toString();
 stringBuilder.setCharAt(int1, '8');
 std::string string13 = stringBuilder.toString();
 object = new IsoDirectionFrame(
 Texture.getSharedTexture(string6),
 Texture.getSharedTexture(string7),
 Texture.getSharedTexture(string8),
 Texture.getSharedTexture(string9),
 Texture.getSharedTexture(string10),
 Texture.getSharedTexture(string11),
 Texture.getSharedTexture(string12),
 Texture.getSharedTexture(string13)
 );
 }

 this->Frames.add(0, (IsoDirectionFrame)object);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }
 }

 void LoadFrames(const std::string& ObjectName, const std::string& AnimName, int nFrames) {
 this->name = AnimName;
 StringBuilder stringBuilder = tlsStrBuf.get();
 stringBuilder.setLength(0);
 stringBuilder.append(ObjectName);
 stringBuilder.append("_%_");
 stringBuilder.append(AnimName);
 stringBuilder.append("_^");
 int int0 = stringBuilder.indexOf("_%_") + 1;
 int int1 = stringBuilder.lastIndexOf("^");
 stringBuilder.setCharAt(int0, '9');
 stringBuilder.setCharAt(int1, '0');
 if (GameServer.bServer && !ServerGUI.isCreated()) {
 for (int int2 = 0; int2 < nFrames; int2++) {
 this->Frames.add(new IsoDirectionFrame(nullptr);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 }

 Texture texture = Texture.getSharedTexture(stringBuilder.toString());
 if (texture != nullptr) {
 for (int int3 = 0; int3 < nFrames; int3++) {
 if (int3 % 10 == 0 && int3 > 0) {
 stringBuilder.setLength(0);
 stringBuilder.append(ObjectName);
 stringBuilder.append("_%_");
 stringBuilder.append(AnimName);
 stringBuilder.append("_^_");
 int0 = stringBuilder.indexOf("_%_") + 1;
 int1 = stringBuilder.lastIndexOf("^");
 }

 int integer = int3;
 void* object = nullptr;
 std::string string0 = integer.toString();
 if (texture != nullptr) {
 stringBuilder.setCharAt(int0, '9');

 for (int int4 = 0; int4 < string0.length(); int4++) {
 stringBuilder.setCharAt(int1 + int4, string0.charAt(int4);
 }

 std::string string1 = stringBuilder.toString();
 stringBuilder.setCharAt(int0, '6');
 std::string string2 = stringBuilder.toString();
 stringBuilder.setCharAt(int0, '3');
 std::string string3 = stringBuilder.toString();
 stringBuilder.setCharAt(int0, '2');
 std::string string4 = stringBuilder.toString();
 stringBuilder.setCharAt(int0, '1');
 std::string string5 = stringBuilder.toString();
 stringBuilder.setCharAt(int0, '4');
 std::string string6 = stringBuilder.toString();
 stringBuilder.setCharAt(int0, '7');
 std::string string7 = stringBuilder.toString();
 stringBuilder.setCharAt(int0, '8');
 std::string string8 = stringBuilder.toString();
 object = new IsoDirectionFrame(
 Texture.getSharedTexture(string1),
 Texture.getSharedTexture(string2),
 Texture.getSharedTexture(string3),
 Texture.getSharedTexture(string4),
 Texture.getSharedTexture(string5),
 Texture.getSharedTexture(string6),
 Texture.getSharedTexture(string7),
 Texture.getSharedTexture(string8)
 );
 } else {
 try {
 stringBuilder.setCharAt(int0, '8');
 } catch (Exception exception0) {
 this->LoadFrames(ObjectName, AnimName, nFrames);
 }

 for (int int5 = 0; int5 < string0.length(); int5++) {
 try {
 stringBuilder.setCharAt(int1 + int5, integer.toString().charAt(int5);
 } catch (Exception exception1) {
 this->LoadFrames(ObjectName, AnimName, nFrames);
 }
 }

 std::string string9 = stringBuilder.toString();
 stringBuilder.setCharAt(int0, '9');
 std::string string10 = stringBuilder.toString();
 stringBuilder.setCharAt(int0, '6');
 std::string string11 = stringBuilder.toString();
 stringBuilder.setCharAt(int0, '3');
 std::string string12 = stringBuilder.toString();
 stringBuilder.setCharAt(int0, '2');
 std::string string13 = stringBuilder.toString();
 object = new IsoDirectionFrame(
 Texture.getSharedTexture(string9),
 Texture.getSharedTexture(string10),
 Texture.getSharedTexture(string11),
 Texture.getSharedTexture(string12),
 Texture.getSharedTexture(string13)
 );
 }

 this->Frames.add((IsoDirectionFrame)object);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }
 }

 void LoadFramesUseOtherFrame(const std::string& ObjectName, const std::string& Variant, const std::string& AnimName, const std::string& OtherAnimName, int nOtherFrameFrame, const std::string& pal) {
 this->name = AnimName;
 std::string string0 = OtherAnimName + "_" + Variant + "_";
 std::string string1 = "_";
 std::string string2 = "";
 if (pal != nullptr) {
 string2 = "_" + pal;
 }

 for (int int0 = 0; int0 < 1; int0++) {
 int integer = new Integer(nOtherFrameFrame);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(
 Texture.getSharedTexture(string0 + "8" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "9" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "6" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "3" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "2" + string1 + integer.toString() + string2 + ".png")
 );
 this->Frames.add(directionFrame);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesBits(const std::string& ObjectName, const std::string& Variant, const std::string& AnimName, int nFrames) {
 this->name = AnimName;
 std::string string0 = AnimName + "_" + Variant + "_";
 std::string string1 = "_";

 for (int int0 = 0; int0 < nFrames; int0++) {
 int integer = new Integer(int0);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(
 Texture.getSharedTexture(string0 + "8" + string1 + integer.toString() + ".png"),
 Texture.getSharedTexture(string0 + "9" + string1 + integer.toString() + ".png"),
 Texture.getSharedTexture(string0 + "6" + string1 + integer.toString() + ".png"),
 Texture.getSharedTexture(string0 + "3" + string1 + integer.toString() + ".png"),
 Texture.getSharedTexture(string0 + "2" + string1 + integer.toString() + ".png")
 );
 this->Frames.add(directionFrame);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesBits(const std::string& ObjectName, const std::string& AnimName, int nFrames) {
 this->name = AnimName;
 std::string string0 = ObjectName + "_" + AnimName + "_";
 std::string string1 = "_";

 for (int int0 = 0; int0 < nFrames; int0++) {
 int integer = new Integer(int0);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(
 Texture.getSharedTexture(string0 + "8" + string1 + integer.toString() + ".png"),
 Texture.getSharedTexture(string0 + "9" + string1 + integer.toString() + ".png"),
 Texture.getSharedTexture(string0 + "6" + string1 + integer.toString() + ".png"),
 Texture.getSharedTexture(string0 + "3" + string1 + integer.toString() + ".png"),
 Texture.getSharedTexture(string0 + "2" + string1 + integer.toString() + ".png")
 );
 this->Frames.add(directionFrame);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesBitRepeatFrame(const std::string& ObjectName, const std::string& AnimName, int RepeatFrame) {
 this->name = AnimName;
 std::string string0 = "_";
 std::string string1 = "";
 int integer = new Integer(RepeatFrame);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(
 Texture.getSharedTexture(AnimName + "8" + string0 + integer.toString() + string1 + ".png"),
 Texture.getSharedTexture(AnimName + "9" + string0 + integer.toString() + string1 + ".png"),
 Texture.getSharedTexture(AnimName + "6" + string0 + integer.toString() + string1 + ".png"),
 Texture.getSharedTexture(AnimName + "3" + string0 + integer.toString() + string1 + ".png"),
 Texture.getSharedTexture(AnimName + "2" + string0 + integer.toString() + string1 + ".png")
 );
 this->Frames.add(directionFrame);
 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesBitRepeatFrame(const std::string& ObjectName, const std::string& Variant, const std::string& AnimName, int RepeatFrame, const std::string& pal) {
 this->name = AnimName;
 std::string string0 = AnimName + "_" + Variant + "_";
 std::string string1 = "_";
 std::string string2 = "";
 if (pal != nullptr) {
 string2 = "_" + pal;
 }

 int integer = new Integer(RepeatFrame);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(
 Texture.getSharedTexture(string0 + "8" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "9" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "6" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "3" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "2" + string1 + integer.toString() + string2 + ".png")
 );
 this->Frames.add(directionFrame);
 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesBits(const std::string& ObjectName, const std::string& Variant, const std::string& AnimName, int nFrames, const std::string& pal) {
 this->name = AnimName;
 std::string string0 = AnimName + "_" + Variant + "_";
 std::string string1 = "_";
 std::string string2 = "";
 if (pal != nullptr) {
 string2 = "_" + pal;
 }

 for (int int0 = 0; int0 < nFrames; int0++) {
 int integer = new Integer(int0);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(
 Texture.getSharedTexture(string0 + "8" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "9" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "6" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "3" + string1 + integer.toString() + string2 + ".png"),
 Texture.getSharedTexture(string0 + "2" + string1 + integer.toString() + string2 + ".png")
 );
 this->Frames.add(directionFrame);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesPcx(const std::string& ObjectName, const std::string& AnimName, int nFrames) {
 this->name = AnimName;
 std::string string0 = ObjectName + "_";
 std::string string1 = "_" + AnimName + "_";

 for (int int0 = 0; int0 < nFrames; int0++) {
 int integer = new Integer(int0);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(
 Texture.getSharedTexture(string0 + "8" + string1 + integer.toString() + ".pcx"),
 Texture.getSharedTexture(string0 + "9" + string1 + integer.toString() + ".pcx"),
 Texture.getSharedTexture(string0 + "6" + string1 + integer.toString() + ".pcx"),
 Texture.getSharedTexture(string0 + "3" + string1 + integer.toString() + ".pcx"),
 Texture.getSharedTexture(string0 + "2" + string1 + integer.toString() + ".pcx")
 );
 this->Frames.add(directionFrame);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void Dispose() {
 for (int int0 = 0; int0 < this->Frames.size(); int0++) {
 IsoDirectionFrame directionFrame = this->Frames.get(int0);
 directionFrame.SetAllDirections(nullptr);
 }
 }

 Texture LoadFrameExplicit(const std::string& string) {
 Texture texture = Texture.getSharedTexture(string);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(texture);
 this->Frames.add(directionFrame);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 return texture;
 }

 void LoadFramesNoDir(const std::string& string2, const std::string& string0, int int1) {
 this->name = string0;
 std::string string1 = "media/" + string2;
 std::string string3 = "_" + string0 + "_";

 for (int int0 = 0; int0 < int1; int0++) {
 int integer = new Integer(int0);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(Texture.getSharedTexture(string1 + string3 + integer.toString() + ".png"));
 this->Frames.add(directionFrame);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesNoDirPage(const std::string& string2, const std::string& string0, int int1) {
 this->name = string0;
 std::string string1 = string2;
 std::string string3 = "_" + string0 + "_";

 for (int int0 = 0; int0 < int1; int0++) {
 int integer = new Integer(int0);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(Texture.getSharedTexture(string1 + string3 + integer.toString()));
 this->Frames.add(directionFrame);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesNoDirPageDirect(const std::string& string2, const std::string& string0, int int1) {
 this->name = string0;
 std::string string1 = string2;
 std::string string3 = "_" + string0 + "_";

 for (int int0 = 0; int0 < int1; int0++) {
 int integer = new Integer(int0);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(Texture.getSharedTexture(string1 + string3 + integer.toString() + ".png"));
 this->Frames.add(directionFrame);
 }

 this->FramesArray = this->Frames.toArray(this->FramesArray);
 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 }

 void LoadFramesNoDirPage(const std::string& string1) {
 this->name = "default";
 std::string string0 = string1;

 for (int int0 = 0; int0 < 1; int0++) {
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(Texture.getSharedTexture(string0);
 this->Frames.add(directionFrame);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesPageSimple(const std::string& NObjectName, const std::string& SObjectName, const std::string& EObjectName, const std::string& WObjectName) {
 this->name = "default";

 for (int int0 = 0; int0 < 1; int0++) {
 new Integer();
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(
 Texture.getSharedTexture(NObjectName),
 Texture.getSharedTexture(SObjectName),
 Texture.getSharedTexture(EObjectName),
 Texture.getSharedTexture(WObjectName)
 );
 this->Frames.add(directionFrame);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesNoDirPalette(const std::string& string2, const std::string& string0, int int1, const std::string& string4) {
 this->name = string0;
 std::string string1 = "media/characters/" + string2;
 std::string string3 = "_" + string0 + "_";

 for (int int0 = 0; int0 < int1; int0++) {
 int integer = new Integer(int0);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(Texture.getSharedTexture(string1 + string3 + integer.toString() + ".pcx", string4);
 this->Frames.add(directionFrame);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void LoadFramesPalette(const std::string& string2, const std::string& string0, int int1, const std::string& string4) {
 this->name = string0;
 std::string string1 = string2 + "_";
 std::string string3 = "_" + string0 + "_";

 for (int int0 = 0; int0 < int1; int0++) {
 int integer = new Integer(int0);
 IsoDirectionFrame directionFrame = new IsoDirectionFrame(
 Texture.getSharedTexture(string1 + "8" + string3 + integer.toString() + "_" + string4),
 Texture.getSharedTexture(string1 + "9" + string3 + integer.toString() + "_" + string4),
 Texture.getSharedTexture(string1 + "6" + string3 + integer.toString() + "_" + string4),
 Texture.getSharedTexture(string1 + "3" + string3 + integer.toString() + "_" + string4),
 Texture.getSharedTexture(string1 + "2" + string3 + integer.toString() + "_" + string4)
 );
 this->Frames.add(directionFrame);
 }

 this->FinishUnloopedOnFrame = (short)(this->Frames.size() - 1);
 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }

 void DupeFrame() {
 for (int int0 = 0; int0 < 8; int0++) {
 IsoDirectionFrame directionFrame = new IsoDirectionFrame();
 directionFrame.directions[int0] = this->Frames.get(0).directions[int0];
 directionFrame.bDoFlip = this->Frames.get(0).bDoFlip;
 this->Frames.add(directionFrame);
 }

 this->FramesArray = this->Frames.toArray(this->FramesArray);
 }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
