#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/iso/Vector2.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace radio {
namespace StorySounds {


class SLSoundManager {
public:
    static bool ENABLED = false;
    static bool DEBUG = false;
    static bool LUA_DEBUG = false;
    static StoryEmitter Emitter = std::make_shared<StoryEmitter>();
    static SLSoundManager instance;
   private std::unordered_map<int, bool> state = std::make_unique<std::unordered_map<>>();
   private std::vector<StorySound> storySounds = std::make_unique<std::vector<>>();
    int nextTick = 0;
    float borderCenterX = 10500.0F;
    float borderCenterY = 9000.0F;
    float borderRadiusMin = 12000.0F;
    float borderRadiusMax = 16000.0F;
    float borderScale = 1.0F;

    static SLSoundManager getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<SLSoundManager>();
      }

    return instance;
   }

    private SLSoundManager() {
      this.state.put(12, false);
      this.state.put(13, false);
   }

    bool getDebug() {
    return DEBUG;
   }

    bool getLuaDebug() {
    return LUA_DEBUG;
   }

   public std::vector<StorySound> getStorySounds() {
      return this.storySounds;
   }

    void print(const std::string& var1) {
      if (DEBUG) {
         System.out.println(var1);
      }
   }

    void init() {
      this.loadSounds();
   }

    void loadSounds() {
      this.storySounds.clear();

      try {
    File var1 = ZomboidFileSystem.instance.getMediaFile("sound" + File.separator);
         if (var1.exists() && var1.isDirectory()) {
            File[] var2 = var1.listFiles();

            for (int var3 = 0; var3 < var2.length; var3++) {
               if (var2[var3].isFile()) {
    std::string var4 = var2[var3].getName();
                  if (var4.lastIndexOf(".") != -1 && var4.lastIndexOf(".") != 0 && var4.substr(var4.lastIndexOf(".") + 1) == "ogg")) {
    std::string var5 = var4.substr(0, var4.lastIndexOf("."));
                     this.print("Adding sound: " + var5);
                     this.addStorySound(std::make_shared<StorySound>(var5, 1.0F));
                  }
               }
            }
         }
      } catch (Exception var6) {
         System.out.print(var6.getMessage());
      }
   }

    void addStorySound(StorySound var1) {
      this.storySounds.push_back(var1);
   }

    void updateKeys() {
      for (Entry var3 : this.state.entrySet()) {
    bool var1 = GameKeyboard.isKeyDown((int)var3.getKey());
         if (var1 && (bool)var3.getValue() != var1) {
            switch (var3.getKey()) {
               case 12:
               case 26:
               case 53:
               default:
                  break;
               case 13:
                  Emitter.coordinate3D = !Emitter.coordinate3D;
            }
         }

         var3.setValue(var1);
      }
   }

    void update(int var1, int var2, int var3) {
      this.updateKeys();
      Emitter.tick();
   }

    void thunderTest() {
      this.nextTick--;
      if (this.nextTick <= 0) {
         this.nextTick = Rand.Next(10, 180);
    float var1 = Rand.Next(0.0F, 8000.0F);
    double var2 = Math.random() * Math.PI * 2.0;
    float var4 = this.borderCenterX + (float)(Math.cos(var2) * var1);
    float var5 = this.borderCenterY + (float)(Math.sin(var2) * var1);
         if (Rand.Next(0, 100) < 60) {
            Emitter.playSound("thunder", 1.0F, var4, var5, 0.0F, 100.0F, 8500.0F);
         } else {
            Emitter.playSound("thundereffect", 1.0F, var4, var5, 0.0F, 100.0F, 8500.0F);
         }
      }
   }

    void render() {
      this.renderDebug();
   }

    void renderDebug() {
      if (DEBUG) {
    std::string var1 = Emitter.coordinate3D ? "3D coordinates, X-Z-Y" : "2D coordinates X-Y-Z";
    int var2 = TextManager.instance.MeasureStringX(UIFont.Large, var1) / 2;
    int var3 = TextManager.instance.MeasureStringY(UIFont.Large, var1);
    int var4 = Core.getInstance().getScreenWidth() / 2;
    int var5 = Core.getInstance().getScreenHeight() / 2;
         this.renderLine(UIFont.Large, var1, var4 - var2, var5);
      }
   }

    void renderLine(UIFont var1, const std::string& var2, int var3, int var4) {
      TextManager.instance.DrawString(var1, var3 + 1, var4 + 1, var2, 0.0, 0.0, 0.0, 1.0);
      TextManager.instance.DrawString(var1, var3 - 1, var4 - 1, var2, 0.0, 0.0, 0.0, 1.0);
      TextManager.instance.DrawString(var1, var3 + 1, var4 - 1, var2, 0.0, 0.0, 0.0, 1.0);
      TextManager.instance.DrawString(var1, var3 - 1, var4 + 1, var2, 0.0, 0.0, 0.0, 1.0);
      TextManager.instance.DrawString(var1, var3, var4, var2, 1.0, 1.0, 1.0, 1.0);
   }

    Vector2 getRandomBorderPosition() {
    float var1 = Rand.Next(this.borderRadiusMin * this.borderScale, this.borderRadiusMax * this.borderScale);
    double var2 = Math.random() * Math.PI * 2.0;
    float var4 = this.borderCenterX + (float)(Math.cos(var2) * var1);
    float var5 = this.borderCenterY + (float)(Math.sin(var2) * var1);
      return std::make_shared<Vector2>(var4, var5);
   }

    float getRandomBorderRange() {
      return Rand.Next(this.borderRadiusMin * this.borderScale * 1.5F, this.borderRadiusMax * this.borderScale * 1.5F);
   }
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie
