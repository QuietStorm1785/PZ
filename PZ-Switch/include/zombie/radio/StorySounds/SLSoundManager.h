#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/iso/Vector2.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace StorySounds {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Turbo Story line sound manager
 */
class SLSoundManager {
public:
 static bool ENABLED = false;
 static bool DEBUG = false;
 static bool LUA_DEBUG = false;
 static StoryEmitter Emitter = new StoryEmitter();
 static SLSoundManager instance;
private
 HashMap<Integer, Boolean> state = std::make_unique<HashMap<>>();
private
 ArrayList<StorySound> storySounds = std::make_unique<ArrayList<>>();
 int nextTick = 0;
 float borderCenterX = 10500.0F;
 float borderCenterY = 9000.0F;
 float borderRadiusMin = 12000.0F;
 float borderRadiusMax = 16000.0F;
 float borderScale = 1.0F;

 static SLSoundManager getInstance() {
 if (instance.empty()) {
 instance = std::make_unique<SLSoundManager>();
 }

 return instance;
 }

private
 SLSoundManager() {
 this->state.put(12, false);
 this->state.put(13, false);
 }

 bool getDebug() { return DEBUG; }

 bool getLuaDebug() { return LUA_DEBUG; }

public
 ArrayList<StorySound> getStorySounds() { return this->storySounds; }

 void print(std::string_view line) {
 if (DEBUG) {
 System.out.println(line);
 }
 }

 void init() { this->loadSounds(); }

 void loadSounds() {
 this->storySounds.clear();

 try {
 File file =
 ZomboidFileSystem.instance.getMediaFile("sound" + File.separator);
 if (file.exists() && file.isDirectory()) {
 File[] files = file.listFiles();

 for (int int0 = 0; int0 < files.length; int0++) {
 if (files[int0].isFile()) {
 std::string string0 = files[int0].getName();
 if (string0.lastIndexOf(".") != -1 &&
 string0.lastIndexOf(".") != 0 &&
 string0.substring(string0.lastIndexOf(".") + 1) == "ogg")) {
 std::string string1 =
 string0.substring(0, string0.lastIndexOf("."));
 this->print("Adding sound: " + string1);
 this->addStorySound(new StorySound(string1, 1.0F);
 }
 }
 }
 }
 } catch (Exception exception) {
 System.out.print(exception.getMessage());
 }
 }

 void addStorySound(StorySound storySound) {
 this->storySounds.add(storySound);
 }

 void updateKeys() {
 for (Entry entry : this->state.entrySet()) {
 bool boolean0 = GameKeyboard.isKeyDown((Integer)entry.getKey());
 if (boolean0 && (Boolean)entry.getValue() != boolean0) {
 switch (entry.getKey()) {
 case 12:
 case 26:
 case 53:
 default:
 break;
 case 13:
 Emitter.coordinate3D = !Emitter.coordinate3D;
 }
 }

 entry.setValue(boolean0);
 }
 }

 void update(int storylineDay, int hour, int min) {
 this->updateKeys();
 Emitter.tick();
 }

 void thunderTest() {
 this->nextTick--;
 if (this->nextTick <= 0) {
 this->nextTick = Rand.Next(10, 180);
 float float0 = Rand.Next(0.0F, 8000.0F);
 double double0 = Math.random() * Math.PI * 2.0;
 float float1 = this->borderCenterX + (float)(Math.cos(double0) * float0);
 float float2 = this->borderCenterY + (float)(Math.sin(double0) * float0);
 if (Rand.Next(0, 100) < 60) {
 Emitter.playSound("thunder", 1.0F, float1, float2, 0.0F, 100.0F,
 8500.0F);
 } else {
 Emitter.playSound("thundereffect", 1.0F, float1, float2, 0.0F, 100.0F,
 8500.0F);
 }
 }
 }

 void render() { this->renderDebug(); }

 void renderDebug() {
 if (DEBUG) {
 std::string string = Emitter.coordinate3D ? "3D coordinates, X-Z-Y"
 : "2D coordinates X-Y-Z";
 int int0 = TextManager.instance.MeasureStringX(UIFont.Large, string) / 2;
 int int1 = TextManager.instance.MeasureStringY(UIFont.Large, string);
 int int2 = Core.getInstance().getScreenWidth() / 2;
 int int3 = Core.getInstance().getScreenHeight() / 2;
 this->renderLine(UIFont.Large, string, int2 - int0, int3);
 }
 }

 void renderLine(UIFont uIFont, std::string_view string, int int1,
 int int0) {
 TextManager.instance.DrawString(uIFont, int1 + 1, int0 + 1, string, 0.0,
 0.0, 0.0, 1.0);
 TextManager.instance.DrawString(uIFont, int1 - 1, int0 - 1, string, 0.0,
 0.0, 0.0, 1.0);
 TextManager.instance.DrawString(uIFont, int1 + 1, int0 - 1, string, 0.0,
 0.0, 0.0, 1.0);
 TextManager.instance.DrawString(uIFont, int1 - 1, int0 + 1, string, 0.0,
 0.0, 0.0, 1.0);
 TextManager.instance.DrawString(uIFont, int1, int0, string, 1.0, 1.0, 1.0,
 1.0);
 }

 Vector2 getRandomBorderPosition() {
 float float0 = Rand.Next(this->borderRadiusMin * this->borderScale,
 this->borderRadiusMax * this->borderScale);
 double double0 = Math.random() * Math.PI * 2.0;
 float float1 = this->borderCenterX + (float)(Math.cos(double0) * float0);
 float float2 = this->borderCenterY + (float)(Math.sin(double0) * float0);
 return new Vector2(float1, float2);
 }

 float getRandomBorderRange() {
 return Rand.Next(this->borderRadiusMin * this->borderScale * 1.5F,
 this->borderRadiusMax * this->borderScale * 1.5F);
 }
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie
