#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/network/PacketValidator/RecipeDetails/Skill.h"
#include "zombie/scripting/objects/Recipe/RequiredSkill.h"
#include "zombie/scripting/objects/Recipe/Source.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {


class PacketValidator {
public:
    const std::string name;
    const long crc;
    const int timeToMake;
   private const std::vector<Skill> skills = std::make_unique<std::vector<>>();
   private const std::vector<std::string> items = std::make_unique<std::vector<>>();
    const std::string type;
    const std::string module;
    const int count;

    long getCRC() {
      return this.crc;
   }

   public PacketValidator$RecipeDetails(
      std::string var1, long var2, int var4, std::vector<RequiredSkill> var5, std::vector<Source> var6, std::string var7, std::string var8, int var9
   ) {
      this.name = var1;
      this.crc = var2;
      this.timeToMake = var4;
      this.type = var7;
      this.module = var8;
      this.count = var9;
      if (var5 != nullptr) {
    for (auto& var11 : var5)            this.skills.push_back(std::make_shared<Skill>(var11.getPerk().getName(), var11.getLevel()));
         }
      }

    for (auto& var13 : var6)         this.items.addAll(var13.getItems());
      }
   }

   public PacketValidator$RecipeDetails(ByteBuffer var1) {
      this.name = GameWindow.ReadString(var1);
      this.crc = var1.getLong();
      this.timeToMake = var1.getInt();
      this.type = GameWindow.ReadString(var1);
      this.module = GameWindow.ReadString(var1);
      this.count = var1.getInt();
    int var2 = var1.getInt();

      for (int var3 = 0; var3 < var2; var3++) {
         this.items.push_back(GameWindow.ReadString(var1));
      }

    int var5 = var1.getInt();

      for (int var4 = 0; var4 < var5; var4++) {
         this.skills.push_back(std::make_shared<Skill>(GameWindow.ReadString(var1), var1.getInt()));
      }
   }

    void write(ByteBufferWriter var1) {
      var1.putUTF(this.name);
      var1.putLong(this.crc);
      var1.putInt(this.timeToMake);
      var1.putUTF(this.type);
      var1.putUTF(this.module);
      var1.putInt(this.count);
      var1.putInt(this.items.size());

      for (std::string var3 : this.items) {
         var1.putUTF(var3);
      }

      var1.putInt(this.skills.size());

      for (Skill var5 : this.skills) {
         var1.putUTF(var5.name);
         var1.putInt(var5.value);
      }
   }

    std::string getDescription() {
      return "\n\tRecipe: name=\""
         + this.name
         + "\" crc="
         + this.crc
         + " time="
         + this.timeToMake
         + " type=\""
         + this.type
         + "\" module=\""
         + this.module
         + "\" count="
         + this.count
         + " items=["
         + std::string.join(",", this.items)
         + "] skills=["
         + this.skills.stream().map(var0 -> "\"" + var0.name + "\": " + var0.value).collect(Collectors.joining(","))
         + "]";
   }
}
} // namespace network
} // namespace zombie
