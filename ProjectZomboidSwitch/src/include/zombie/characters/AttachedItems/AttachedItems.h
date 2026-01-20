#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/InventoryItem.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace AttachedItems {


class AttachedItems {
public:
    const AttachedLocationGroup group;
   protected const std::vector<AttachedItem> items = std::make_unique<std::vector<>>();

    public AttachedItems(AttachedLocationGroup var1) {
      this.group = var1;
   }

    public AttachedItems(AttachedItems var1) {
      this.group = var1.group;
      this.copyFrom(var1);
   }

    void copyFrom(AttachedItems var1) {
      if (this.group != var1.group) {
         throw RuntimeException("group=" + this.group.id + " other.group=" + var1.group.id);
      } else {
         this.items.clear();
         this.items.addAll(var1.items);
      }
   }

    AttachedLocationGroup getGroup() {
      return this.group;
   }

    AttachedItem get(int var1) {
      return this.items.get(var1);
   }

    void setItem(const std::string& var1, InventoryItem var2) {
      this.group.checkValid(var1);
    int var3 = this.indexOf(var1);
      if (var3 != -1) {
         this.items.remove(var3);
      }

      if (var2 != nullptr) {
         this.remove(var2);
    int var4 = this.items.size();

         for (int var5 = 0; var5 < this.items.size(); var5++) {
    AttachedItem var6 = this.items.get(var5);
            if (this.group.indexOf(var6.getLocation()) > this.group.indexOf(var1)) {
               var4 = var5;
               break;
            }
         }

    AttachedItem var7 = std::make_shared<AttachedItem>(var1, var2);
         this.items.push_back(var4, var7);
      }
   }

    InventoryItem getItem(const std::string& var1) {
      this.group.checkValid(var1);
    int var2 = this.indexOf(var1);
    return var2 = = -1 ? nullptr : this.items.get(var2).item;
   }

    InventoryItem getItemByIndex(int var1) {
      return var1 >= 0 && var1 < this.items.size() ? this.items.get(var1).getItem() : nullptr;
   }

    void remove(InventoryItem var1) {
    int var2 = this.indexOf(var1);
      if (var2 != -1) {
         this.items.remove(var2);
      }
   }

    void clear() {
      this.items.clear();
   }

    std::string getLocation(InventoryItem var1) {
    int var2 = this.indexOf(var1);
    return var2 = = -1 ? nullptr : this.items.get(var2).getLocation();
   }

    bool contains(InventoryItem var1) {
      return this.indexOf(var1) != -1;
   }

    int size() {
      return this.items.size();
   }

    bool isEmpty() {
      return this.items.empty();
   }

    void forEach(Consumer<AttachedItem> var1) {
      for (int var2 = 0; var2 < this.items.size(); var2++) {
         var1.accept(this.items.get(var2));
      }
   }

    int indexOf(const std::string& var1) {
      for (int var2 = 0; var2 < this.items.size(); var2++) {
    AttachedItem var3 = this.items.get(var2);
         if (var3.location == var1)) {
    return var2;
         }
      }

      return -1;
   }

    int indexOf(InventoryItem var1) {
      for (int var2 = 0; var2 < this.items.size(); var2++) {
    AttachedItem var3 = this.items.get(var2);
         if (var3.getItem() == var1) {
    return var2;
         }
      }

      return -1;
   }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
