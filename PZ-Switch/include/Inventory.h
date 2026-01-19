#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <string_view>

namespace zombie {
namespace inventory {

enum class ItemType {
 WEAPON,
 AMMO,
 FOOD,
 MEDICINE,
 CLOTHING,
 TOOL,
 MISC,
 UNKNOWN
};

class InventoryItem {
public:
 InventoryItem(std::string_view name, ItemType type, float weight = 0.5f);
 
 std::string getName() const { return name; }
 ItemType getType() const { return type; }
 float getWeight() const { return weight; }
 int getCount() const noexcept { return count; }
 void setCount(int c) { count = c; }
 
 bool isStackable() const { return stackable; }
 void setStackable(bool s) { stackable = s; }
 
private:
 std::string name;
 ItemType type;
 float weight;
 int count;
 bool stackable;
};

class InventorySlot {
public:
 InventorySlot(int maxStack = 1);
 
 bool addItem(std::shared_ptr<InventoryItem> item);
 bool removeItem(int count);
 std::shared_ptr<InventoryItem> getItem() const { return item; }
 int getCount() const noexcept { return (item ? item->getCount() : 0); }
 bool isEmpty() const { return !item; }
 
private:
 std::shared_ptr<InventoryItem> item;
 int maxStackSize;
};

class Inventory {
public:
 Inventory(int slotCount = 20);
 ~Inventory() = default;
 
 bool addItem(std::shared_ptr<InventoryItem> item);
 bool removeItem(int slotIndex, int count);
 std::shared_ptr<InventoryItem> getItem(int slotIndex);
 
 float getTotalWeight() const;
 float getMaxWeight() const { return maxWeight; }
 int getSlotCount() const noexcept { return slots.size(); }
 int getUsedSlots() const;
 
 void clear();
 bool isFull() const;
 
private:
 std::vector<InventorySlot> slots;
 float maxWeight;
 float currentWeight;
};

} // namespace inventory
} // namespace zombie
