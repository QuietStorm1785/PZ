#include "Inventory.h"

namespace zombie {
namespace inventory {

InventoryItem::InventoryItem(const std::string& name, ItemType type, float weight)
    : name(name), type(type), weight(weight), count(1), stackable(false) {
}

InventorySlot::InventorySlot(int maxStack)
    : maxStackSize(maxStack) {
}

bool InventorySlot::addItem(std::shared_ptr<InventoryItem> item) {
    if (!item) return false;
    
    if (item->isStackable() && this->item && this->item->getName() == item->getName()) {
        if (this->item->getCount() < maxStackSize) {
            this->item->setCount(this->item->getCount() + item->getCount());
            return true;
        }
        return false;
    }
    
    if (!this->item) {
        this->item = item;
        return true;
    }
    return false;
}

bool InventorySlot::removeItem(int count) {
    if (!item || count < 0) return false;
    
    int currentCount = item->getCount();
    if (count >= currentCount) {
        item = nullptr;
        return true;
    }
    
    item->setCount(currentCount - count);
    return true;
}

Inventory::Inventory(int slotCount)
    : maxWeight(50.0f), currentWeight(0.0f) {
    for (int i = 0; i < slotCount; ++i) {
        slots.emplace_back(1);
    }
}

bool Inventory::addItem(std::shared_ptr<InventoryItem> item) {
    if (!item) return false;
    
    float itemWeight = item->getWeight() * item->getCount();
    if (currentWeight + itemWeight > maxWeight) return false;
    
    for (auto& slot : slots) {
        if (slot.addItem(item)) {
            currentWeight += itemWeight;
            return true;
        }
    }
    return false;
}

bool Inventory::removeItem(int slotIndex, int count) {
    if (slotIndex < 0 || slotIndex >= (int)slots.size()) return false;
    
    if (slots[slotIndex].removeItem(count)) {
        if (auto item = slots[slotIndex].getItem()) {
            currentWeight -= item->getWeight() * count;
        }
        return true;
    }
    return false;
}

std::shared_ptr<InventoryItem> Inventory::getItem(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= (int)slots.size()) return nullptr;
    return slots[slotIndex].getItem();
}

float Inventory::getTotalWeight() const {
    return currentWeight;
}

int Inventory::getUsedSlots() const {
    int count = 0;
    for (const auto& slot : slots) {
        if (!slot.isEmpty()) count++;
    }
    return count;
}

void Inventory::clear() {
    for (auto& slot : slots) {
        slot.removeItem(999);
    }
    currentWeight = 0.0f;
}

bool Inventory::isFull() const {
    for (const auto& slot : slots) {
        if (slot.isEmpty()) return false;
    }
    return true;
}

} // namespace inventory
} // namespace zombie
