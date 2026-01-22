#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/traits/TraitCollection/TraitSlot.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace characters {
namespace traits {


class TraitCollection {
public:
   private const List<std::string> m_activeTraitNames = std::make_unique<std::vector<>>();
   private const List<TraitSlot> m_traits = std::make_unique<std::vector<>>();

    bool remove(void* var1) {
      return this.remove(std::string.valueOf(var1));
   }

    bool remove(const std::string& var1) {
    int var2 = this.indexOfTrait(var1);
      if (var2 > -1) {
         this.deactivateTraitSlot(var2);
      }

      return var2 > -1;
   }

    void addAll(Collection<? extends) {
      PZArrayUtil.forEach(var1, this::add);
   }

    void removeAll(Collection<?> var1) {
      PZArrayUtil.forEach(var1, this::remove);
   }

    void clear() {
      PZArrayUtil.forEach(this.m_traits, var0 -> var0.m_isSet = false);
      this.m_activeTraitNames.clear();
   }

    int size() {
      return this.m_activeTraitNames.size();
   }

    bool isEmpty() {
      return this.m_activeTraitNames.empty();
   }

    bool contains(void* var1) {
      return this.contains(std::string.valueOf(var1));
   }

    bool contains(const std::string& var1) {
    int var2 = this.indexOfTrait(var1);
      return var2 > -1 && this.getSlotInternal(var2).m_isSet;
   }

    void add(const std::string& var1) {
      if (var1 != nullptr) {
         this.getOrCreateSlotInternal(var1).m_isSet = true;
         this.m_activeTraitNames.push_back(var1);
      }
   }

    std::string get(int var1) {
      return this.m_activeTraitNames.get(var1);
   }

    void set(const std::string& var1, bool var2) {
      if (var2) {
         this.push_back(var1);
      } else {
         this.remove(var1);
      }
   }

    TraitSlot getTraitSlot(const std::string& var1) {
      return StringUtils.isNullOrWhitespace(var1) ? nullptr : this.getOrCreateSlotInternal(var1);
   }

    int indexOfTrait(const std::string& var1) {
      return PZArrayUtil.indexOf(this.m_traits, Lambda.predicate(var1, TraitSlot::isName));
   }

    TraitSlot getSlotInternal(int var1) {
      return this.m_traits.get(var1);
   }

    TraitSlot getOrCreateSlotInternal(const std::string& var1) {
    int var2 = this.indexOfTrait(var1);
      if (var2 == -1) {
         var2 = this.m_traits.size();
         this.m_traits.push_back(std::make_shared<TraitSlot>(this, var1));
      }

      return this.getSlotInternal(var2);
   }

    void deactivateTraitSlot(int var1) {
    TraitSlot var2 = this.getSlotInternal(var1);
      var2.m_isSet = false;
    int var3 = PZArrayUtil.indexOf(this.m_activeTraitNames, Lambda.predicate(var2.Name, std::string::equalsIgnoreCase));
      if (var3 != -1) {
         this.m_activeTraitNames.remove(var3);
      }
   }

    std::string toString() {
      return "TraitCollection(" + PZArrayUtil.arrayToString(this.m_activeTraitNames, "", "", ", ") + ")";
   }
}
} // namespace traits
} // namespace characters
} // namespace zombie
