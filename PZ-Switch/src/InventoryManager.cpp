#include "InventoryManager.h"
#include "IsoPlayer.h"
#include <algorithm>

// Item Implementation
Item::Item(const std::string& name, int weight)
 : name(name), type("misc"), weight(weight) {}

std::string Item::getDescription() const {
 return name + " (weight: " + std::to_string(weight) + "g)";
}

// InventoryManager Implementation
InventoryManager::InventoryManager(zombie::characters::IsoPlayer* owner)
 : owner(owner), currentWeight(0) {}

InventoryManager::~InventoryManager() {
 clear();
}

bool InventoryManager::addItem(Item* item) {
 if (!item || !canAddItem(item)) {
 return false;
 }
 
 items.push_back(item);
 updateWeight();
 return true;
}

bool InventoryManager::removeItem(Item* item) {
 auto it = std::find(items.begin(), items.end(), item);
 if (it != items.end()) {
 items.erase(it);
 updateWeight();
 return true;
 }
 return false;
}

bool InventoryManager::canAddItem(const Item* item) const {
 if (!item) return false;
 if (items.size() >= MAX_SLOTS) return false;
 if (!item->isMovable()) return false;
 
 int weightAfterAdd = currentWeight + item->getWeight();
 return weightAfterAdd <= MAX_WEIGHT;
}

int InventoryManager::getCurrentWeight() const {
 return currentWeight;
}

int InventoryManager::getItemCount() const {
 return items.size();
}

std::vector<Item*> InventoryManager::getItemsByType(const std::string& type) {
 std::vector<Item*> result;
 for (auto item : items) {
 if (item->getType() == type) {
 result.push_back(item);
 }
 }
 return result;
}

Item* InventoryManager::findItem(const std::string& name) {
 for (auto item : items) {
 if (item->getName() == name) {
 return item;
 }
 }
 return nullptr;
}

void InventoryManager::clear() {
 // Note: In a real implementation, we'd need to handle proper cleanup
 // For now, just clear the vector (assuming items are managed elsewhere)
 items.clear();
 currentWeight = 0;
}

void InventoryManager::updateWeight() {
 currentWeight = 0;
 for (auto item : items) {
 if (item) {
 currentWeight += item->getWeight();
 }
 }
}

// ContainerInteractionSystem Implementation
std::unordered_map<zombie::characters::IsoPlayer*, IsoContainer*> ContainerInteractionSystem::openContainers;

bool ContainerInteractionSystem::openContainer(IsoContainer* container, zombie::characters::IsoPlayer* player) {
 if (!canOpenContainer(player, container)) {
 return false;
 }
 
 openContainers[player] = container;
 // TODO: Show container UI
 return true;
}

void ContainerInteractionSystem::closeContainer(zombie::characters::IsoPlayer* player) {
 auto it = openContainers.find(player);
 if (it != openContainers.end()) {
 openContainers.erase(it);
 // TODO: Hide container UI
 }
}

bool ContainerInteractionSystem::transferToPlayer(IsoContainer* container, zombie::characters::IsoPlayer* player, Item* item) {
 if (!container || !player || !item) return false;
 
 // TODO: Get player inventory
 // auto inventory = player->getInventory();
 // if (!inventory) return false;
 
 // if (inventory->canAddItem(item)) {
 // // TODO: Remove item from container
 // inventory->addItem(item);
 // return true;
 // }
 
 return false;
}

bool ContainerInteractionSystem::transferToContainer(zombie::characters::IsoPlayer* player, IsoContainer* container, Item* item) {
 if (!player || !container || !item) return false;
 
 // TODO: Get player inventory
 // auto inventory = player->getInventory();
 // if (!inventory) return false;
 
 // if (inventory->removeItem(item)) {
 // // TODO: Add item to container
 // return true;
 // }
 
 return false;
}

bool ContainerInteractionSystem::canOpenContainer(zombie::characters::IsoPlayer* player, IsoContainer* container) {
 if (!player || !container) return false;
 
 // TODO: Check distance to container
 // TODO: Check if container is locked
 // TODO: Check if container is accessible
 
 return true;
}

IsoContainer* ContainerInteractionSystem::getOpenContainer(zombie::characters::IsoPlayer* player) {
 auto it = openContainers.find(player);
 if (it != openContainers.end()) {
 return it->second;
 }
 return nullptr;
}
