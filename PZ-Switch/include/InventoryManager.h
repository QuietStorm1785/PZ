#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

// Forward declarations
class Item;
class IsoContainer;

// Use namespace-qualified forward declaration for IsoPlayer
namespace zombie { namespace characters { class IsoPlayer; } }

/**
 * InventoryManager - Enhanced inventory with container support
 * 
 * Extends basic inventory with container interaction, item transfer,
 * and UI integration capabilities.
 * 
 * Example:
 * auto inv = player->getInventory();
 * if (inv->canAddItem(item) {
 * inv->addItem(item);
 * }
 */
class InventoryManager {
public:
 static const int MAX_WEIGHT = 100000; // grams
 static const int MAX_SLOTS = 40;

 explicit InventoryManager(zombie::characters::IsoPlayer* owner);
 ~InventoryManager();

 /**
 * Add item to inventory
 * @param item - Item to add
 * @return true if item was added
 */
 bool addItem(Item* item);

 /**
 * Remove item from inventory
 * @param item - Item to remove
 * @return true if item was removed
 */
 bool removeItem(Item* item);

 /**
 * Check if item can be added (weight/space check)
 * @param item - Item to check
 * @return true if inventory has space for item
 */
 bool canAddItem(const Item* item) const;

 /**
 * Get current inventory weight in grams
 */
 int getCurrentWeight() const;

 /**
 * Get current number of items
 */
 int getItemCount() const;

 /**
 * Get all items of type
 */
 std::vector<Item*> getItemsByType(const std::string& type);

 /**
 * Find item by name
 */
 Item* findItem(const std::string& name);

 /**
 * Clear entire inventory
 */
 void clear();

 /**
 * Get all items
 */
 const std::vector<Item*>& getItems() const { return items; }

private:
 zombie::characters::IsoPlayer* owner;
 std::vector<Item*> items;
 int currentWeight;

 void updateWeight();
};

/**
 * ContainerInteractionSystem - Handle container operations
 * 
 * Manages opening/closing containers, item transfer, UI display.
 * Integrates with InventoryManager for item operations.
 */
class ContainerInteractionSystem {
public:
 /**
 * Open a container for interaction
 * @param container - Container to open
 * @param player - Player interacting
 * @return true if container opened successfully
 */
 static bool openContainer(IsoContainer* container, zombie::characters::IsoPlayer* player);

 /**
 * Close currently open container
 * @param player - Player closing container
 */
 static void closeContainer(zombie::characters::IsoPlayer* player);

 /**
 * Transfer item from container to player inventory
 * @param container - Source container
 * @param player - Destination player
 * @param item - Item to transfer
 * @return true if transfer successful
 */
 static bool transferToPlayer(IsoContainer* container, zombie::characters::IsoPlayer* player, Item* item);

 /**
 * Transfer item from player inventory to container
 * @param player - Source player
 * @param container - Destination container
 * @param item - Item to transfer
 * @return true if transfer successful
 */
 static bool transferToContainer(zombie::characters::IsoPlayer* player, IsoContainer* container, Item* item);

 /**
 * Check if player can open container (distance, locked state)
 */
 static bool canOpenContainer(zombie::characters::IsoPlayer* player, IsoContainer* container);

 /**
 * Get currently open container for player
 */
 static IsoContainer* getOpenContainer(zombie::characters::IsoPlayer* player);

private:
 // Map: player -> open container
 static std::unordered_map<zombie::characters::IsoPlayer*, IsoContainer*> openContainers;
};

/**
 * Item - Basic item class for inventory system
 * 
 * Represents an item that can be carried in inventory or stored in containers.
 */
class Item {
public:
 Item(const std::string& name, int weight = 100);
 virtual ~Item() = default;

 const std::string& getName() const { return name; }
 int getWeight() const { return weight; }
 const std::string& getType() const { return type; }

 /**
 * Set item type for categorization
 */
 void setType(const std::string& t) { type = t; }

 /**
 * Get item description for UI
 */
 virtual std::string getDescription() const;

 /**
 * Called when item is used
 */
 virtual void use(zombie::characters::IsoPlayer* /*player*/) {}

 /**
 * Called when item is dropped
 */
 virtual void onDrop() {}

 /**
 * Check if item can be moved/transferred
 */
 virtual bool isMovable() const { return true; }

protected:
 std::string name;
 std::string type; // "weapon", "food", "tool", etc.
 int weight; // in grams
};
