#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/MapGroups.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace modding {


class ActiveMods {
public:
   private static final ArrayList<ActiveMods> s_activeMods = std::make_unique<ArrayList<>>();
    static const ActiveMods s_loaded = new ActiveMods("loaded");
    const std::string id;
   private final ArrayList<String> mods = std::make_unique<ArrayList<>>();
   private final ArrayList<String> mapOrder = std::make_unique<ArrayList<>>();

    static int count() {
      return s_activeMods.size();
   }

    static ActiveMods getByIndex(int var0) {
      return s_activeMods.get(var0);
   }

    static ActiveMods getById(const std::string& var0) {
    int var1 = indexOf(var0);
    return var1 = = -1 ? create(var0) : s_activeMods.get(var1);
   }

    static int indexOf(const std::string& var0) {
      var0 = var0.trim();
      requireValidId(var0);

      for (int var1 = 0; var1 < s_activeMods.size(); var1++) {
    ActiveMods var2 = s_activeMods.get(var1);
         if (var2.id.equalsIgnoreCase(var0)) {
    return var1;
         }
      }

      return -1;
   }

    static ActiveMods create(const std::string& var0) {
      requireValidId(var0);
      if (indexOf(var0) != -1) {
         throw new IllegalStateException("id \"" + var0 + "\" exists");
      } else {
    ActiveMods var1 = new ActiveMods(var0);
         s_activeMods.add(var1);
    return var1;
      }
   }

    static void requireValidId(const std::string& var0) {
      if (StringUtils.isNullOrWhitespace(var0)) {
         throw new IllegalArgumentException("id is nullptr or whitespace");
      }
   }

    static void setLoadedMods(ActiveMods var0) {
      if (var0 != nullptr) {
         s_loaded.copyFrom(var0);
      }
   }

    static bool requiresResetLua(ActiveMods var0) {
      Objects.requireNonNull(var0);
      return !s_loaded.mods == var0.mods);
   }

    static void renderUI() {
      if (DebugOptions.instance.ModRenderLoaded.getValue()) {
         if (!GameWindow.DrawReloadingLua) {
    UIFont var0 = UIFont.DebugConsole;
    int var1 = TextManager.instance.getFontHeight(var0);
    std::string var2 = "Active Mods:";
    int var3 = TextManager.instance.MeasureStringX(var0, var2);

            for (int var4 = 0; var4 < s_loaded.mods.size(); var4++) {
    std::string var5 = s_loaded.mods.get(var4);
    int var6 = TextManager.instance.MeasureStringX(var0, var5);
               var3 = Math.max(var3, var6);
            }

    uint8_t var11 = 10;
            var3 += var11 * 2;
    int var12 = Core.width - 20 - var3;
    uint8_t var13 = 20;
    int var7 = (1 + s_loaded.mods.size()) * var1 + var11 * 2;
            SpriteRenderer.instance.renderi(nullptr, var12, var13, var3, var7, 0.0F, 0.5F, 0.75F, 1.0F, nullptr);
    int var14;
            TextManager.instance.DrawString(var0, var12 + var11, var14 = var13 + var11, var2, 1.0, 1.0, 1.0, 1.0);

            for (int var8 = 0; var8 < s_loaded.mods.size(); var8++) {
    std::string var9 = s_loaded.mods.get(var8);
               TextManager.instance.DrawString(var0, var12 + var11, var14 += var1, var9, 1.0, 1.0, 1.0, 1.0);
            }
         }
      }
   }

    static void Reset() {
      s_loaded.clear();
   }

    public ActiveMods(const std::string& var1) {
      requireValidId(var1);
      this.id = var1;
   }

    void clear() {
      this.mods.clear();
      this.mapOrder.clear();
   }

   public ArrayList<String> getMods() {
      return this.mods;
   }

   public ArrayList<String> getMapOrder() {
      return this.mapOrder;
   }

    void copyFrom(ActiveMods var1) {
      this.mods.clear();
      this.mapOrder.clear();
      this.mods.addAll(var1.mods);
      this.mapOrder.addAll(var1.mapOrder);
   }

    void setModActive(const std::string& var1, bool var2) {
      var1 = var1.trim();
      if (!StringUtils.isNullOrWhitespace(var1)) {
         if (var2) {
            if (!this.mods.contains(var1)) {
               this.mods.add(var1);
            }
         } else {
            this.mods.remove(var1);
         }
      }
   }

    bool isModActive(const std::string& var1) {
      var1 = var1.trim();
      return StringUtils.isNullOrWhitespace(var1) ? false : this.mods.contains(var1);
   }

    void removeMod(const std::string& var1) {
      var1 = var1.trim();
      this.mods.remove(var1);
   }

    void removeMapOrder(const std::string& var1) {
      this.mapOrder.remove(var1);
   }

    void checkMissingMods() {
      if (!this.mods.isEmpty()) {
         for (int var1 = this.mods.size() - 1; var1 >= 0; var1--) {
    std::string var2 = this.mods.get(var1);
            if (ChooseGameInfo.getAvailableModDetails(var2) == nullptr) {
               this.mods.remove(var1);
            }
         }
      }
   }

    void checkMissingMaps() {
      if (!this.mapOrder.isEmpty()) {
    MapGroups var1 = new MapGroups();
         var1.createGroups(this, false);
         if (var1.checkMapConflicts()) {
    std::vector var2 = var1.getAllMapsInOrder();

            for (int var3 = this.mapOrder.size() - 1; var3 >= 0; var3--) {
    std::string var4 = this.mapOrder.get(var3);
               if (!var2.contains(var4)) {
                  this.mapOrder.remove(var3);
               }
            }
         } else {
            this.mapOrder.clear();
         }
      }
   }
}
} // namespace modding
} // namespace zombie
