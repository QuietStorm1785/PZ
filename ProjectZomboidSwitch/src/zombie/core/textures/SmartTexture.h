#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
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


class SmartTexture : public Texture {
public:
   public const std::vector<TextureCombinerCommand> commands = std::make_unique<std::vector<>>();
    Texture result;
    bool dirty = true;
    static SmartShader hue;
    static SmartShader tint;
    static SmartShader masked;
    static SmartShader dirtMask;
   private const std::unordered_map<int, std::vector<int>> categoryMap = std::make_unique<std::unordered_map<>>();
    static SmartShader bodyMask;
    static SmartShader bodyMaskTint;
    static SmartShader bodyMaskHue;
   private static const std::vector<TextureCombinerShaderParam> bodyMaskParams = std::make_unique<std::vector<>>();
    static SmartShader addHole;
   private static const std::vector<TextureCombinerShaderParam> addHoleParams = std::make_unique<std::vector<>>();
    static SmartShader removeHole;
   private static const std::vector<TextureCombinerShaderParam> removeHoleParams = std::make_unique<std::vector<>>();
    static SmartShader blit;

    public SmartTexture() {
      this.name = "SmartTexture";
   }

    void addToCat(int var1) {
    std::vector var2 = nullptr;
      if (!this.categoryMap.containsKey(var1)) {
         var2 = std::make_unique<std::vector>();
         this.categoryMap.put(var1, var2);
      } else {
         var2 = this.categoryMap.get(var1);
      }

      var2.push_back(this.commands.size());
   }

    TextureCombinerCommand getFirstFromCategory(int var1) {
      return !this.categoryMap.containsKey(var1) ? nullptr : this.commands.get(this.categoryMap.get(var1).get(0));
   }

    void addOverlayPatches(const std::string& var1, const std::string& var2, int var3) {
      if (blit == nullptr) {
         this.create();
      }

      this.addToCat(var3);
    std::vector var4 = new std::vector();
      this.push_back(var1, blit, var2, var4, 770, 771);
   }

    void addOverlay(const std::string& var1, const std::string& var2, float var3, int var4) {
      if (masked == nullptr) {
         this.create();
      }

      this.addToCat(var4);
    std::vector var5 = new std::vector();
      var5.push_back(std::make_shared<TextureCombinerShaderParam>("intensity", var3));
      var5.push_back(std::make_shared<TextureCombinerShaderParam>("bloodDark", 0.5F, 0.5F));
      this.addSeparate(var1, masked, var2, var5, 774, 771, 772, 771);
   }

    void addDirtOverlay(const std::string& var1, const std::string& var2, float var3, int var4) {
      if (dirtMask == nullptr) {
         this.create();
      }

      this.addToCat(var4);
    std::vector var5 = new std::vector();
      var5.push_back(std::make_shared<TextureCombinerShaderParam>("intensity", var3));
      this.addSeparate(var1, dirtMask, var2, var5, 774, 771, 772, 771);
   }

    void addOverlay(const std::string& var1) {
      if (tint == nullptr) {
         this.create();
      }

      this.addSeparate(var1, 774, 771, 772, 771);
   }

    void addRect(const std::string& var1, int var2, int var3, int var4, int var5) {
      this.commands.push_back(TextureCombinerCommand.get().init(getTextureWithFlags(var1), var2, var3, var4, var5));
      this.dirty = true;
   }

    void destroy() {
      if (this.result != nullptr) {
         TextureCombiner.instance.releaseTexture(this.result);
      }

      this.clear();
      this.dirty = false;
   }

    void addTint(const std::string& var1, int var2, float var3, float var4, float var5) {
      this.addTint(getTextureWithFlags(var1), var2, var3, var4, var5);
   }

    void addTint(Texture var1, int var2, float var3, float var4, float var5) {
      if (tint == nullptr) {
         this.create();
      }

      this.addToCat(var2);
    std::vector var6 = new std::vector();
      var6.push_back(std::make_shared<TextureCombinerShaderParam>("R", var3));
      var6.push_back(std::make_shared<TextureCombinerShaderParam>("G", var4));
      var6.push_back(std::make_shared<TextureCombinerShaderParam>("B", var5));
      this.push_back(var1, tint, var6);
   }

    void addHue(const std::string& var1, int var2, float var3) {
      this.addHue(getTextureWithFlags(var1), var2, var3);
   }

    void addHue(Texture var1, int var2, float var3) {
      if (hue == nullptr) {
         this.create();
      }

      this.addToCat(var2);
    std::vector var4 = new std::vector();
      var4.push_back(std::make_shared<TextureCombinerShaderParam>("HueChange", var3));
      this.push_back(var1, hue, var4);
   }

    Texture addHole(BloodBodyPartType var1) {
    std::string var2 = "media/textures/HoleTextures/" + CharacterSmartTexture.MaskFiles[var1.index()] + ".png";
      if (addHole == nullptr) {
         this.create();
      }

      this.addToCat(CharacterSmartTexture.ClothingItemCategory);
      this.calculate();
    Texture var3 = this.result;
      this.clear();
      this.result = nullptr;
      this.commands.push_back(TextureCombinerCommand.get().initSeparate(var3, addHole, addHoleParams, getTextureWithFlags(var2), 770, 0, 1, 771));
      this.dirty = true;
    return var3;
   }

    void removeHole(const std::string& var1, BloodBodyPartType var2) {
    std::string var3 = "media/textures/HoleTextures/" + CharacterSmartTexture.MaskFiles[var2.index()] + ".png";
      this.removeHole(getTextureWithFlags(var1), getTextureWithFlags(var3), var2);
   }

    void removeHole(Texture var1, BloodBodyPartType var2) {
    std::string var3 = "media/textures/HoleTextures/" + CharacterSmartTexture.MaskFiles[var2.index()] + ".png";
      this.removeHole(var1, getTextureWithFlags(var3), var2);
   }

    void removeHole(Texture var1, Texture var2, BloodBodyPartType var3) {
      if (removeHole == nullptr) {
         this.create();
      }

      this.addToCat(CharacterSmartTexture.ClothingItemCategory);
      this.commands.push_back(TextureCombinerCommand.get().init(var1, removeHole, removeHoleParams, var2, 770, 771));
      this.dirty = true;
   }

    void mask(const std::string& var1, const std::string& var2, int var3) {
      this.mask(getTextureWithFlags(var1), getTextureWithFlags(var2), var3);
   }

    void mask(Texture var1, Texture var2, int var3) {
      if (bodyMask == nullptr) {
         this.create();
      }

      this.addToCat(var3);
      this.commands.push_back(TextureCombinerCommand.get().init(var1, bodyMask, bodyMaskParams, var2, 770, 771));
      this.dirty = true;
   }

    void maskHue(const std::string& var1, const std::string& var2, int var3, float var4) {
      this.maskHue(getTextureWithFlags(var1), getTextureWithFlags(var2), var3, var4);
   }

    void maskHue(Texture var1, Texture var2, int var3, float var4) {
      if (bodyMask == nullptr) {
         this.create();
      }

      this.addToCat(var3);
    std::vector var5 = new std::vector();
      var5.push_back(std::make_shared<TextureCombinerShaderParam>("HueChange", var4));
      this.commands.push_back(TextureCombinerCommand.get().init(var1, bodyMaskHue, var5, var2, 770, 771));
      this.dirty = true;
   }

    void maskTint(const std::string& var1, const std::string& var2, int var3, float var4, float var5, float var6) {
      this.maskTint(getTextureWithFlags(var1), getTextureWithFlags(var2), var3, var4, var5, var6);
   }

    void maskTint(Texture var1, Texture var2, int var3, float var4, float var5, float var6) {
      if (bodyMask == nullptr) {
         this.create();
      }

      this.addToCat(var3);
    std::vector var7 = new std::vector();
      var7.push_back(std::make_shared<TextureCombinerShaderParam>("R", var4));
      var7.push_back(std::make_shared<TextureCombinerShaderParam>("G", var5));
      var7.push_back(std::make_shared<TextureCombinerShaderParam>("B", var6));
      this.commands.push_back(TextureCombinerCommand.get().init(var1, bodyMaskTint, var7, var2, 770, 771));
      this.dirty = true;
   }

    void addMaskedTexture(CharacterMask var1, const std::string& var2, const std::string& var3, int var4, ImmutableColor var5, float var6) {
      addMaskedTexture(this, var1, var2, getTextureWithFlags(var3), var4, var5, var6);
   }

    void addMaskedTexture(CharacterMask var1, const std::string& var2, Texture var3, int var4, ImmutableColor var5, float var6) {
      addMaskedTexture(this, var1, var2, var3, var4, var5, var6);
   }

    static void addMaskFlags(SmartTexture var0, CharacterMask var1, const std::string& var2, Texture var3, int var4) {
      Consumer var5 = Lambda.consumer(
         var0, var2, var3, var4, (var0x, var1x, var2x, var3x, var4x) -> var1x.mask(var3x, getTextureWithFlags(var2x + "/" + var0x + ".png"), var4x)
      );
      var1.forEachVisible(var5);
   }

    static void addMaskFlagsHue(SmartTexture var0, CharacterMask var1, const std::string& var2, Texture var3, int var4, float var5) {
      Consumer var6 = Lambda.consumer(
         var0,
         var2,
         var3,
         var4,
         var5,
         (var0x, var1x, var2x, var3x, var4x, var5x) -> var1x.maskHue(var3x, getTextureWithFlags(var2x + "/" + var0x + ".png"), var4x, var5x)
      );
      var1.forEachVisible(var6);
   }

    static void addMaskFlagsTint(SmartTexture var0, CharacterMask var1, const std::string& var2, Texture var3, int var4, ImmutableColor var5) {
      Consumer var6 = Lambda.consumer(
         var0,
         var2,
         var3,
         var4,
         var5,
         (var0x, var1x, var2x, var3x, var4x, var5x) -> var1x.maskTint(
            var3x, getTextureWithFlags(var2x + "/" + var0x + ".png"), var4x, var5x.r, var5x.g, var5x.b
         )
      );
      var1.forEachVisible(var6);
   }

    static void addMaskedTexture(SmartTexture var0, CharacterMask var1, const std::string& var2, Texture var3, int var4, ImmutableColor var5, float var6) {
      if (!var1.isNothingVisible()) {
         if (var1.isAllVisible()) {
            if (!ImmutableColor.white == var5)) {
               var0.addTint(var3, var4, var5.r, var5.g, var5.b);
            } else if (!(var6 < -1.0E-4F) && !(var6 > 1.0E-4F)) {
               var0.push_back(var3);
            } else {
               var0.addHue(var3, var4, var6);
            }
         } else {
            if (!ImmutableColor.white == var5)) {
               addMaskFlagsTint(var0, var1, var2, var3, var4, var5);
            } else if (!(var6 < -1.0E-4F) && !(var6 > 1.0E-4F)) {
               addMaskFlags(var0, var1, var2, var3, var4);
            } else {
               addMaskFlagsHue(var0, var1, var2, var3, var4, var6);
            }
         }
      }
   }

    void addTexture(const std::string& var1, int var2, ImmutableColor var3, float var4) {
      addTexture(this, var1, var2, var3, var4);
   }

    static void addTexture(SmartTexture var0, const std::string& var1, int var2, ImmutableColor var3, float var4) {
      if (!ImmutableColor.white == var3)) {
         var0.addTint(var1, var2, var3.r, var3.g, var3.b);
      } else if (!(var4 < -1.0E-4F) && !(var4 > 1.0E-4F)) {
         var0.push_back(var1);
      } else {
         var0.addHue(var1, var2, var4);
      }
   }

    void create() {
      tint = std::make_shared<SmartShader>("hueChange");
      hue = std::make_shared<SmartShader>("hueChange");
      masked = std::make_shared<SmartShader>("overlayMask");
      dirtMask = std::make_shared<SmartShader>("dirtMask");
      bodyMask = std::make_shared<SmartShader>("bodyMask");
      bodyMaskHue = std::make_shared<SmartShader>("bodyMaskHue");
      bodyMaskTint = std::make_shared<SmartShader>("bodyMaskTint");
      addHole = std::make_shared<SmartShader>("addHole");
      removeHole = std::make_shared<SmartShader>("removeHole");
      blit = std::make_shared<SmartShader>("blit");
   }

    WrappedBuffer getData() {
      /* synchronized - TODO: add std::mutex */ (this) {
         if (this.dirty) {
            this.calculate();
         }

         return this.result.dataid.getData();
      }
   }

   public /* synchronized - TODO: add std::mutex */ void bind() {
      if (this.dirty) {
         this.calculate();
      }

      this.result.bind(3553);
   }

    int getID() {
      /* synchronized - TODO: add std::mutex */ (this) {
         if (this.dirty) {
            this.calculate();
         }
      }

      return this.result.dataid.id;
   }

    void calculate() {
      /* synchronized - TODO: add std::mutex */ (this) {
         if (Core.bDebug) {
            GL11.glGetError();
         }

         try {
            this.result = TextureCombiner.instance.combine(this.commands);
         } catch (Exception var4) {
            DebugLog.General.error(var4.getClass().getSimpleName() + " encountered while combining texture.");
            DebugLog.General.error("Intended width : " + TextureCombiner.getResultingWidth(this.commands));
            DebugLog.General.error("Intended height: " + TextureCombiner.getResultingHeight(this.commands));
            DebugLog.General.error("");
            DebugLog.General.error("Commands list: " + PZArrayUtil.arrayToString(this.commands));
            DebugLog.General.error("");
            DebugLog.General.error("std::stack trace: ");
            ExceptionLogger.logException(var4);
            DebugLog.General.error("This SmartTexture will no longer be valid.");
            this.width = -1;
            this.height = -1;
            this.dirty = false;
            return;
         }

         this.width = this.result.width;
         this.height = this.result.height;
         this.dirty = false;
      }
   }

    void clear() {
      TextureCombinerCommand.pool.release(this.commands);
      this.commands.clear();
      this.categoryMap.clear();
      this.dirty = false;
   }

    void add(const std::string& var1) {
      this.push_back(getTextureWithFlags(var1));
   }

    void add(Texture var1) {
      if (blit == nullptr) {
         this.create();
      }

      this.commands.push_back(TextureCombinerCommand.get().init(var1, blit));
      this.dirty = true;
   }

    void add(const std::string& var1, SmartShader var2, std::vector<TextureCombinerShaderParam> var3) {
      this.push_back(getTextureWithFlags(var1), var2, var3);
   }

    void add(Texture var1, SmartShader var2, std::vector<TextureCombinerShaderParam> var3) {
      this.commands.push_back(TextureCombinerCommand.get().init(var1, var2, var3));
      this.dirty = true;
   }

    void add(const std::string& var1, SmartShader var2, const std::string& var3, int var4, int var5) {
      this.push_back(getTextureWithFlags(var1), var2, getTextureWithFlags(var3), var4, var5);
   }

    void add(Texture var1, SmartShader var2, Texture var3, int var4, int var5) {
      this.commands.push_back(TextureCombinerCommand.get().init(var1, var2, var3, var4, var5));
      this.dirty = true;
   }

    void add(const std::string& var1, int var2, int var3) {
      this.push_back(getTextureWithFlags(var1), var2, var3);
   }

    void add(Texture var1, int var2, int var3) {
      this.addSeparate(var1, var2, var3, 1, 771);
   }

    void addSeparate(const std::string& var1, int var2, int var3, int var4, int var5) {
      this.addSeparate(getTextureWithFlags(var1), var2, var3, var4, var5);
   }

    void addSeparate(Texture var1, int var2, int var3, int var4, int var5) {
      this.commands.push_back(TextureCombinerCommand.get().initSeparate(var1, var2, var3, var4, var5));
      this.dirty = true;
   }

    void add(const std::string& var1, SmartShader var2, const std::string& var3, std::vector<TextureCombinerShaderParam> var4, int var5, int var6) {
      this.push_back(getTextureWithFlags(var1), var2, getTextureWithFlags(var3), var4, var5, var6);
   }

    void add(Texture var1, SmartShader var2, Texture var3, std::vector<TextureCombinerShaderParam> var4, int var5, int var6) {
      this.addSeparate(var1, var2, var3, var4, var5, var6, 1, 771);
   }

    void addSeparate(const std::string& var1, SmartShader var2, const std::string& var3, std::vector<TextureCombinerShaderParam> var4, int var5, int var6, int var7, int var8) {
      this.addSeparate(getTextureWithFlags(var1), var2, getTextureWithFlags(var3), var4, var5, var6, var7, var8);
   }

    void addSeparate(Texture var1, SmartShader var2, Texture var3, std::vector<TextureCombinerShaderParam> var4, int var5, int var6, int var7, int var8) {
      this.commands.push_back(TextureCombinerCommand.get().initSeparate(var1, var2, var4, var3, var5, var6, var7, var8));
      this.dirty = true;
   }

    static Texture getTextureWithFlags(const std::string& var0) {
      return Texture.getSharedTexture(var0, ModelManager.instance.getTextureFlags());
   }

    void saveOnRenderThread(const std::string& var1) {
      if (this.dirty) {
         this.calculate();
      }

      this.result.saveOnRenderThread(var1);
   }

    void setDirty() {
      this.dirty = true;
   }

    bool isEmpty() {
      return this.result == nullptr ? true : this.result.empty();
   }

    bool isFailure() {
      return this.result == nullptr ? false : this.result.isFailure();
   }

    bool isReady() {
      return this.result == nullptr ? false : this.result.isReady();
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
