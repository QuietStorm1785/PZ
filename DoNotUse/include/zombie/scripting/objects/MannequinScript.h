#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace scripting {
namespace objects {


class MannequinScript : public BaseScriptObject {
public:
    std::string name;
    bool bFemale = true;
    std::string modelScriptName;
    std::string texture;
    std::string animSet;
    std::string animState;
    std::string pose;
    std::string outfit;

    std::string getName() {
      return this.name;
   }

    bool isFemale() {
      return this.bFemale;
   }

    void setFemale(bool var1) {
      this.bFemale = var1;
   }

    std::string getModelScriptName() {
      return this.modelScriptName;
   }

    void setModelScriptName(const std::string& var1) {
      this.modelScriptName = StringUtils.discardNullOrWhitespace(var1);
   }

    std::string getTexture() {
      return this.texture;
   }

    void setTexture(const std::string& var1) {
      this.texture = StringUtils.discardNullOrWhitespace(var1);
   }

    std::string getAnimSet() {
      return this.animSet;
   }

    void setAnimSet(const std::string& var1) {
      this.animSet = StringUtils.discardNullOrWhitespace(var1);
   }

    std::string getAnimState() {
      return this.animState;
   }

    void setAnimState(const std::string& var1) {
      this.animState = StringUtils.discardNullOrWhitespace(var1);
   }

    std::string getPose() {
      return this.pose;
   }

    void setPose(const std::string& var1) {
      this.pose = StringUtils.discardNullOrWhitespace(var1);
   }

    std::string getOutfit() {
      return this.outfit;
   }

    void setOutfit(const std::string& var1) {
      this.outfit = StringUtils.discardNullOrWhitespace(var1);
   }

    void Load(const std::string& var1, const std::string& var2) {
      this.name = var1;
    Block var3 = ScriptParser.parse(var2);
      var3 = (Block)var3.children.get(0);

      for (Value var5 : var3.values) {
    std::string var6 = var5.getKey().trim();
    std::string var7 = var5.getValue().trim();
         if ("female".equalsIgnoreCase(var6)) {
            this.bFemale = StringUtils.tryParseBoolean(var7);
         } else if ("model".equalsIgnoreCase(var6)) {
            this.modelScriptName = StringUtils.discardNullOrWhitespace(var7);
         } else if ("texture".equalsIgnoreCase(var6)) {
            this.texture = StringUtils.discardNullOrWhitespace(var7);
         } else if ("animSet".equalsIgnoreCase(var6)) {
            this.animSet = StringUtils.discardNullOrWhitespace(var7);
         } else if ("animState".equalsIgnoreCase(var6)) {
            this.animState = StringUtils.discardNullOrWhitespace(var7);
         } else if ("pose".equalsIgnoreCase(var6)) {
            this.pose = StringUtils.discardNullOrWhitespace(var7);
         } else if ("outfit".equalsIgnoreCase(var6)) {
            this.outfit = StringUtils.discardNullOrWhitespace(var7);
         }
      }
   }

    void reset() {
      this.modelScriptName = nullptr;
      this.texture = nullptr;
      this.animSet = nullptr;
      this.animState = nullptr;
      this.pose = nullptr;
      this.outfit = nullptr;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
