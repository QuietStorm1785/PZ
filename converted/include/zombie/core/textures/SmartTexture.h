#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/CharacterSmartTexture.h"
#include "zombie/core/Core.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/opengl/SmartShader.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/model/CharacterMask.h"
#include "zombie/core/utils/WrappedBuffer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SmartTexture : public Texture {
public:
 public ArrayList<TextureCombinerCommand> commands = std::make_unique<ArrayList<>>();
 Texture result;
 bool dirty = true;
 static SmartShader hue;
 static SmartShader tint;
 static SmartShader masked;
 static SmartShader dirtMask;
 private HashMap<Integer, ArrayList<Integer>> categoryMap = std::make_unique<HashMap<>>();
 static SmartShader bodyMask;
 static SmartShader bodyMaskTint;
 static SmartShader bodyMaskHue;
 private static ArrayList<TextureCombinerShaderParam> bodyMaskParams = std::make_unique<ArrayList<>>();
 static SmartShader addHole;
 private static ArrayList<TextureCombinerShaderParam> addHoleParams = std::make_unique<ArrayList<>>();
 static SmartShader removeHole;
 private static ArrayList<TextureCombinerShaderParam> removeHoleParams = std::make_unique<ArrayList<>>();
 static SmartShader blit;

 public SmartTexture() {
 this->name = "SmartTexture";
 }

 void addToCat(int int0) {
 std::vector arrayList = nullptr;
 if (!this->categoryMap.containsKey(int0) {
 arrayList = std::make_unique<ArrayList>();
 this->categoryMap.put(int0, arrayList);
 } else {
 arrayList = this->categoryMap.get(int0);
 }

 arrayList.add(this->commands.size());
 }

 TextureCombinerCommand getFirstFromCategory(int int0) {
 return !this->categoryMap.containsKey(int0) ? nullptr : this->commands.get(this->categoryMap.get(int0).get(0);
 }

 void addOverlayPatches(const std::string& string0, const std::string& string1, int int0) {
 if (blit == nullptr) {
 this->create();
 }

 this->addToCat(int0);
 std::vector arrayList = new ArrayList();
 this->add(string0, blit, string1, arrayList, 770, 771);
 }

 void addOverlay(const std::string& string0, const std::string& string1, float float0, int int0) {
 if (masked == nullptr) {
 this->create();
 }

 this->addToCat(int0);
 std::vector arrayList = new ArrayList();
 arrayList.add(new TextureCombinerShaderParam("intensity", float0);
 arrayList.add(new TextureCombinerShaderParam("bloodDark", 0.5F, 0.5F);
 this->addSeparate(string0, masked, string1, arrayList, 774, 771, 772, 771);
 }

 void addDirtOverlay(const std::string& string0, const std::string& string1, float float0, int int0) {
 if (dirtMask == nullptr) {
 this->create();
 }

 this->addToCat(int0);
 std::vector arrayList = new ArrayList();
 arrayList.add(new TextureCombinerShaderParam("intensity", float0);
 this->addSeparate(string0, dirtMask, string1, arrayList, 774, 771, 772, 771);
 }

 void addOverlay(const std::string& string) {
 if (tint == nullptr) {
 this->create();
 }

 this->addSeparate(string, 774, 771, 772, 771);
 }

 void addRect(const std::string& string, int int0, int int1, int int2, int int3) {
 this->commands.add(TextureCombinerCommand.get().init(getTextureWithFlags(string), int0, int1, int2, int3);
 this->dirty = true;
 }

 void destroy() {
 if (this->result != nullptr) {
 TextureCombiner.instance.releaseTexture(this->result);
 }

 this->clear();
 this->dirty = false;
 }

 void addTint(const std::string& string, int int0, float float0, float float1, float float2) {
 this->addTint(getTextureWithFlags(string), int0, float0, float1, float2);
 }

 void addTint(Texture texture, int int0, float float0, float float1, float float2) {
 if (tint == nullptr) {
 this->create();
 }

 this->addToCat(int0);
 std::vector arrayList = new ArrayList();
 arrayList.add(new TextureCombinerShaderParam("R", float0);
 arrayList.add(new TextureCombinerShaderParam("G", float1);
 arrayList.add(new TextureCombinerShaderParam("B", float2);
 this->add(texture, tint, arrayList);
 }

 void addHue(const std::string& string, int int0, float float0) {
 this->addHue(getTextureWithFlags(string), int0, float0);
 }

 void addHue(Texture texture, int int0, float float0) {
 if (hue == nullptr) {
 this->create();
 }

 this->addToCat(int0);
 std::vector arrayList = new ArrayList();
 arrayList.add(new TextureCombinerShaderParam("HueChange", float0);
 this->add(texture, hue, arrayList);
 }

 Texture addHole(BloodBodyPartType bloodBodyPartType) {
 std::string string = "media/textures/HoleTextures/" + CharacterSmartTexture.MaskFiles[bloodBodyPartType.index()] + ".png";
 if (addHole == nullptr) {
 this->create();
 }

 this->addToCat(CharacterSmartTexture.ClothingItemCategory);
 this->calculate();
 Texture texture = this->result;
 this->clear();
 this->result = nullptr;
 this->commands.add(TextureCombinerCommand.get().initSeparate(texture, addHole, addHoleParams, getTextureWithFlags(string), 770, 0, 1, 771);
 this->dirty = true;
 return texture;
 }

 void removeHole(const std::string& string1, BloodBodyPartType bloodBodyPartType) {
 std::string string0 = "media/textures/HoleTextures/" + CharacterSmartTexture.MaskFiles[bloodBodyPartType.index()] + ".png";
 this->removeHole(getTextureWithFlags(string1), getTextureWithFlags(string0), bloodBodyPartType);
 }

 void removeHole(Texture texture, BloodBodyPartType bloodBodyPartType) {
 std::string string = "media/textures/HoleTextures/" + CharacterSmartTexture.MaskFiles[bloodBodyPartType.index()] + ".png";
 this->removeHole(texture, getTextureWithFlags(string), bloodBodyPartType);
 }

 void removeHole(Texture texture0, Texture texture1, BloodBodyPartType var3) {
 if (removeHole == nullptr) {
 this->create();
 }

 this->addToCat(CharacterSmartTexture.ClothingItemCategory);
 this->commands.add(TextureCombinerCommand.get().init(texture0, removeHole, removeHoleParams, texture1, 770, 771);
 this->dirty = true;
 }

 void mask(const std::string& string1, const std::string& string0, int int0) {
 this->mask(getTextureWithFlags(string1), getTextureWithFlags(string0), int0);
 }

 void mask(Texture texture0, Texture texture1, int int0) {
 if (bodyMask == nullptr) {
 this->create();
 }

 this->addToCat(int0);
 this->commands.add(TextureCombinerCommand.get().init(texture0, bodyMask, bodyMaskParams, texture1, 770, 771);
 this->dirty = true;
 }

 void maskHue(const std::string& string1, const std::string& string0, int int0, float float0) {
 this->maskHue(getTextureWithFlags(string1), getTextureWithFlags(string0), int0, float0);
 }

 void maskHue(Texture texture0, Texture texture1, int int0, float float0) {
 if (bodyMask == nullptr) {
 this->create();
 }

 this->addToCat(int0);
 std::vector arrayList = new ArrayList();
 arrayList.add(new TextureCombinerShaderParam("HueChange", float0);
 this->commands.add(TextureCombinerCommand.get().init(texture0, bodyMaskHue, arrayList, texture1, 770, 771);
 this->dirty = true;
 }

 void maskTint(const std::string& string1, const std::string& string0, int int0, float float0, float float1, float float2) {
 this->maskTint(getTextureWithFlags(string1), getTextureWithFlags(string0), int0, float0, float1, float2);
 }

 void maskTint(Texture texture0, Texture texture1, int int0, float float0, float float1, float float2) {
 if (bodyMask == nullptr) {
 this->create();
 }

 this->addToCat(int0);
 std::vector arrayList = new ArrayList();
 arrayList.add(new TextureCombinerShaderParam("R", float0);
 arrayList.add(new TextureCombinerShaderParam("G", float1);
 arrayList.add(new TextureCombinerShaderParam("B", float2);
 this->commands.add(TextureCombinerCommand.get().init(texture0, bodyMaskTint, arrayList, texture1, 770, 771);
 this->dirty = true;
 }

 void addMaskedTexture(CharacterMask characterMask, const std::string& string0, const std::string& string1, int int0, ImmutableColor immutableColor, float float0) {
 addMaskedTexture(this, characterMask, string0, getTextureWithFlags(string1), int0, immutableColor, float0);
 }

 void addMaskedTexture(CharacterMask characterMask, const std::string& string, Texture texture, int int0, ImmutableColor immutableColor, float float0) {
 addMaskedTexture(this, characterMask, string, texture, int0, immutableColor, float0);
 }

 static void addMaskFlags(SmartTexture smartTexture, CharacterMask characterMask, const std::string& string, Texture texture, int int0) {
 Consumer consumer = Lambda.consumer(
 smartTexture,
 string,
 texture,
 int0,
 (part, smartTexturex, stringx, texturex, integer) -> smartTexturex.mask(texturex, getTextureWithFlags(stringx + "/" + part + ".png"), integer)
 );
 characterMask.forEachVisible(consumer);
 }

 static void addMaskFlagsHue(SmartTexture smartTexture, CharacterMask characterMask, const std::string& string, Texture texture, int int0, float float0) {
 Consumer consumer = Lambda.consumer(
 smartTexture,
 string,
 texture,
 int0,
 float0,
 (part, smartTexturex, stringx, texturex, integer, float0x) -> smartTexturex.maskHue(
 texturex, getTextureWithFlags(stringx + "/" + part + ".png"), integer, float0x
 )
 );
 characterMask.forEachVisible(consumer);
 }

 private static void addMaskFlagsTint(
 SmartTexture smartTexture, CharacterMask characterMask, String string, Texture texture, int int0, ImmutableColor immutableColor
 ) {
 Consumer consumer = Lambda.consumer(
 smartTexture,
 string,
 texture,
 int0,
 immutableColor,
 (part, smartTexturex, stringx, texturex, integer, immutableColorx) -> smartTexturex.maskTint(
 texturex, getTextureWithFlags(stringx + "/" + part + ".png"), integer, immutableColorx.r, immutableColorx.g, immutableColorx.b
 )
 );
 characterMask.forEachVisible(consumer);
 }

 private static void addMaskedTexture(
 SmartTexture smartTexture, CharacterMask characterMask, String string, Texture texture, int int0, ImmutableColor immutableColor, float float0
 ) {
 if (!characterMask.isNothingVisible()) {
 if (characterMask.isAllVisible()) {
 if (!ImmutableColor.white == immutableColor) {
 smartTexture.addTint(texture, int0, immutableColor.r, immutableColor.g, immutableColor.b);
 } else if (!(float0 < -1.0E-4F) && !(float0 > 1.0E-4F) {
 smartTexture.add(texture);
 } else {
 smartTexture.addHue(texture, int0, float0);
 }
 } else {
 if (!ImmutableColor.white == immutableColor) {
 addMaskFlagsTint(smartTexture, characterMask, string, texture, int0, immutableColor);
 } else if (!(float0 < -1.0E-4F) && !(float0 > 1.0E-4F) {
 addMaskFlags(smartTexture, characterMask, string, texture, int0);
 } else {
 addMaskFlagsHue(smartTexture, characterMask, string, texture, int0, float0);
 }
 }
 }
 }

 void addTexture(const std::string& string, int int0, ImmutableColor immutableColor, float float0) {
 addTexture(this, string, int0, immutableColor, float0);
 }

 static void addTexture(SmartTexture smartTexture, const std::string& string, int int0, ImmutableColor immutableColor, float float0) {
 if (!ImmutableColor.white == immutableColor) {
 smartTexture.addTint(string, int0, immutableColor.r, immutableColor.g, immutableColor.b);
 } else if (!(float0 < -1.0E-4F) && !(float0 > 1.0E-4F) {
 smartTexture.add(string);
 } else {
 smartTexture.addHue(string, int0, float0);
 }
 }

 void create() {
 tint = new SmartShader("hueChange");
 hue = new SmartShader("hueChange");
 masked = new SmartShader("overlayMask");
 dirtMask = new SmartShader("dirtMask");
 bodyMask = new SmartShader("bodyMask");
 bodyMaskHue = new SmartShader("bodyMaskHue");
 bodyMaskTint = new SmartShader("bodyMaskTint");
 addHole = new SmartShader("addHole");
 removeHole = new SmartShader("removeHole");
 blit = new SmartShader("blit");
 }

 WrappedBuffer getData() {
 synchronized (this) {
 if (this->dirty) {
 this->calculate();
 }

 return this->result.dataid.getData();
 }
 }

 public synchronized void bind() {
 if (this->dirty) {
 this->calculate();
 }

 this->result.bind(3553);
 }

 int getID() {
 synchronized (this) {
 if (this->dirty) {
 this->calculate();
 }
 }

 return this->result.dataid.id;
 }

 void calculate() {
 synchronized (this) {
 if (Core.bDebug) {
 GL11.glGetError();
 }

 try {
 this->result = TextureCombiner.instance.combine(this->commands);
 } catch (Exception exception) {
 DebugLog.General.error(exception.getClass().getSimpleName() + " encountered while combining texture.");
 DebugLog.General.error("Intended width : " + TextureCombiner.getResultingWidth(this->commands);
 DebugLog.General.error("Intended height: " + TextureCombiner.getResultingHeight(this->commands);
 DebugLog.General.error("");
 DebugLog.General.error("Commands list: " + PZArrayUtil.arrayToString(this->commands);
 DebugLog.General.error("");
 DebugLog.General.error("Stack trace: ");
 ExceptionLogger.logException(exception);
 DebugLog.General.error("This SmartTexture will no longer be valid.");
 this->width = -1;
 this->height = -1;
 this->dirty = false;
 return;
 }

 this->width = this->result.width;
 this->height = this->result.height;
 this->dirty = false;
 }
 }

 void clear() {
 TextureCombinerCommand.pool.release(this->commands);
 this->commands.clear();
 this->categoryMap.clear();
 this->dirty = false;
 }

 void add(const std::string& string) {
 this->add(getTextureWithFlags(string);
 }

 void add(Texture texture) {
 if (blit == nullptr) {
 this->create();
 }

 this->commands.add(TextureCombinerCommand.get().init(texture, blit);
 this->dirty = true;
 }

 void add(const std::string& string, SmartShader smartShader, ArrayList<TextureCombinerShaderParam> arrayList) {
 this->add(getTextureWithFlags(string), smartShader, arrayList);
 }

 void add(Texture texture, SmartShader smartShader, ArrayList<TextureCombinerShaderParam> arrayList) {
 this->commands.add(TextureCombinerCommand.get().init(texture, smartShader, arrayList);
 this->dirty = true;
 }

 void add(const std::string& string1, SmartShader smartShader, const std::string& string0, int int0, int int1) {
 this->add(getTextureWithFlags(string1), smartShader, getTextureWithFlags(string0), int0, int1);
 }

 void add(Texture texture0, SmartShader smartShader, Texture texture1, int int0, int int1) {
 this->commands.add(TextureCombinerCommand.get().init(texture0, smartShader, texture1, int0, int1);
 this->dirty = true;
 }

 void add(const std::string& string, int int0, int int1) {
 this->add(getTextureWithFlags(string), int0, int1);
 }

 void add(Texture texture, int int0, int int1) {
 this->addSeparate(texture, int0, int1, 1, 771);
 }

 void addSeparate(const std::string& string, int int0, int int1, int int2, int int3) {
 this->addSeparate(getTextureWithFlags(string), int0, int1, int2, int3);
 }

 void addSeparate(Texture texture, int int0, int int1, int int2, int int3) {
 this->commands.add(TextureCombinerCommand.get().initSeparate(texture, int0, int1, int2, int3);
 this->dirty = true;
 }

 void add(const std::string& string1, SmartShader smartShader, const std::string& string0, ArrayList<TextureCombinerShaderParam> arrayList, int int0, int int1) {
 this->add(getTextureWithFlags(string1), smartShader, getTextureWithFlags(string0), arrayList, int0, int1);
 }

 void add(Texture texture0, SmartShader smartShader, Texture texture1, ArrayList<TextureCombinerShaderParam> arrayList, int int0, int int1) {
 this->addSeparate(texture0, smartShader, texture1, arrayList, int0, int1, 1, 771);
 }

 public void addSeparate(
 String string1, SmartShader smartShader, String string0, ArrayList<TextureCombinerShaderParam> arrayList, int int0, int int1, int int2, int int3
 ) {
 this->addSeparate(getTextureWithFlags(string1), smartShader, getTextureWithFlags(string0), arrayList, int0, int1, int2, int3);
 }

 public void addSeparate(
 Texture texture0, SmartShader smartShader, Texture texture1, ArrayList<TextureCombinerShaderParam> arrayList, int int0, int int1, int int2, int int3
 ) {
 this->commands.add(TextureCombinerCommand.get().initSeparate(texture0, smartShader, arrayList, texture1, int0, int1, int2, int3);
 this->dirty = true;
 }

 static Texture getTextureWithFlags(const std::string& string) {
 return Texture.getSharedTexture(string, ModelManager.instance.getTextureFlags());
 }

 void saveOnRenderThread(const std::string& string) {
 if (this->dirty) {
 this->calculate();
 }

 this->result.saveOnRenderThread(string);
 }

 void setDirty() {
 this->dirty = true;
 }

 bool isEmpty() {
 return this->result == nullptr ? true : this->result.empty();
 }

 bool isFailure() {
 return this->result == nullptr ? false : this->result.isFailure();
 }

 bool isReady() {
 return this->result == nullptr ? false : this->result.isReady();
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
