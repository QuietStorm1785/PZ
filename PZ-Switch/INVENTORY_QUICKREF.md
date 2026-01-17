# 🎒 Inventory System - Quick Reference

## Status: ✅ COMPLETE

All inventory components are implemented and integrated.

---

## Quick Test

```bash
cd /workspaces/PZ/PZ-Switch/build
./test_inventory.sh      # Automated verification
./ProjectZomboidCpp      # In-game test
```

---

## Core Components

### Item Class
```cpp
Item* item = new Item("Axe", 2000);  // name, weight in grams
item->setType("weapon");
item->getDescription();  // Returns: "Axe (weight: 2000g)"
```

### InventoryManager
```cpp
auto* inv = player->getInventory();

// Add items
if (inv->canAddItem(item)) {
    inv->addItem(item);
}

// Remove items
inv->removeItem(item);

// Query
int weight = inv->getCurrentWeight();  // grams
int count = inv->getItemCount();
auto items = inv->getItemsByType("weapon");
```

### IsoContainer
```cpp
IsoContainer* container = new IsoContainer();

// Storage
container->addItem(item);
container->removeItem(item);
auto& items = container->getItems();

// Properties
int capacity = container->getMaxItems();  // 20 by default
bool locked = container->isLocked();
container->setLocked(true);
```

---

## Limits

- **Max Weight:** 100,000g (100kg)
- **Max Slots:** 40 items
- **Container Capacity:** 20 items (default)

---

## Integration

### IsoPlayer
```cpp
// Player has inventory automatically
IsoPlayer* player = new IsoPlayer();
auto* inv = player->getInventory();  // Created in constructor

// Inventory deleted automatically in destructor
delete player;  // Cleans up inventory
```

### Container Interaction
```cpp
// When player interacts with container
IsoContainer* container = ...; 
container->onInteract(player);

// Transfer items
ContainerInteractionSystem::transferItem(
    item, player->getInventory(), container);
```

---

## Weight System

**Calculation:**
```cpp
Item* axe = new Item("Axe", 2000);      // 2kg
Item* knife = new Item("Knife", 300);    // 300g
Item* food = new Item("Can", 500);       // 500g

// Total: 2800g (2.8kg)
```

**Limits:**
- Can carry up to 100kg total
- Weight checked in `canAddItem()`
- Automatically updated on add/remove

---

## Capacity System

```cpp
InventoryManager* inv = player->getInventory();

// Slot check
if (inv->getItemCount() < InventoryManager::MAX_SLOTS) {
    inv->addItem(item);  // OK
} else {
    // Inventory full!
}

// Weight check
if (inv->getCurrentWeight() + item->getWeight() <= InventoryManager::MAX_WEIGHT) {
    inv->addItem(item);  // OK
}

// Combined check
if (inv->canAddItem(item)) {
    inv->addItem(item);  // Checks both!
}
```

---

## Item Types

```cpp
item->setType("weapon");   // Weapons
item->setType("food");     // Consumables
item->setType("tool");     // Tools
item->setType("material"); // Resources
item->setType("misc");     // Default
```

**Finding by Type:**
```cpp
auto weapons = inv->getItemsByType("weapon");
for (auto* weapon : weapons) {
    std::cout << weapon->getName() << std::endl;
}
```

---

## Container System

**Properties:**
- Each container has maxItems (default 20)
- Can be locked/unlocked
- Plays "open" sound when accessed
- Shows item count on interact

**Usage:**
```cpp
IsoContainer* chest = new IsoContainer();
chest->setMaxItems(50);  // Large chest
chest->setLocked(false);

// Fill container
for (int i = 0; i < 10; i++) {
    Item* item = new Item("Item" + std::to_string(i), 100);
    chest->addItem(item);
}

// Check contents
std::cout << "Container has " << chest->getItemCount() 
          << " items" << std::endl;
```

---

## API Reference

### Item
```cpp
Item(const std::string& name, int weight = 100);
const std::string& getName() const;
int getWeight() const;
const std::string& getType() const;
void setType(const std::string& t);
std::string getDescription() const;
virtual void use(IsoPlayer* player);
virtual void onDrop();
virtual bool isMovable() const;
```

### InventoryManager
```cpp
// Constants
static const int MAX_WEIGHT = 100000;  // grams
static const int MAX_SLOTS = 40;

// Methods
bool addItem(Item* item);
bool removeItem(Item* item);
bool canAddItem(const Item* item) const;
int getCurrentWeight() const;
int getItemCount() const;
std::vector<Item*> getItemsByType(const std::string& type);
Item* findItem(const std::string& name);
void clear();
const std::vector<Item*>& getItems() const;
```

### IsoContainer
```cpp
bool addItem(Item* item);
bool removeItem(Item* item);
const std::vector<Item*>& getItems() const;
int getItemCount() const;
int getMaxItems() const;
bool isLocked() const;
void setLocked(bool l);
void onInteract(IsoPlayer* player) override;
```

---

## Example: Complete Item Lifecycle

```cpp
// 1. Create item
Item* axe = new Item("Wood Axe", 2500);  // 2.5kg
axe->setType("weapon");

// 2. Add to player inventory
IsoPlayer* player = new IsoPlayer();
auto* inv = player->getInventory();

if (inv->canAddItem(axe)) {
    inv->addItem(axe);
    std::cout << "Picked up axe!" << std::endl;
} else {
    std::cout << "Inventory full or too heavy!" << std::endl;
}

// 3. Transfer to container
IsoContainer* chest = new IsoContainer();
if (chest->addItem(axe)) {
    inv->removeItem(axe);
    std::cout << "Stored in chest" << std::endl;
}

// 4. Query inventory
std::cout << "Weight: " << inv->getCurrentWeight() << "g" << std::endl;
std::cout << "Items: " << inv->getItemCount() << "/" 
          << InventoryManager::MAX_SLOTS << std::endl;

// 5. Find items by type
auto weapons = inv->getItemsByType("weapon");
std::cout << "You have " << weapons.size() << " weapons" << std::endl;
```

---

## What's Integrated

✅ Item class (name, weight, type, description)  
✅ InventoryManager (add/remove, weight/slot limits)  
✅ IsoContainer (storage, capacity, locking)  
✅ IsoPlayer integration (lifecycle management)  
✅ ContainerInteractionSystem (transfer logic)  
✅ Weight tracking (automatic updates)  
✅ Capacity checking (canAddItem)  
✅ Type categorization (getItemsByType)  
✅ Audio integration (container sounds)  
✅ Namespace safety (fully-qualified types)

---

## Testing Checklist

- [ ] Create player and verify inventory exists
- [ ] Add items and check weight increases
- [ ] Try to add item when full (should fail)
- [ ] Try to add item when too heavy (should fail)
- [ ] Remove items and check weight decreases
- [ ] Transfer items to/from containers
- [ ] Test locked containers (should block access)
- [ ] Query items by type
- [ ] Verify inventory destroyed with player

---

## Performance

**Memory:**
- Item: ~100 bytes (name + metadata)
- InventoryManager: ~1KB (40 items max)
- IsoContainer: ~800 bytes (20 items default)

**Operations:**
- addItem(): O(1)
- removeItem(): O(n) - linear search
- canAddItem(): O(1)
- getItemsByType(): O(n) - filter by type
- findItem(): O(n) - linear search

---

## Files Reference

- **Headers:** include/InventoryManager.h, include/WorldContent.h
- **Implementation:** src/InventoryManager.cpp, src/WorldContent.cpp
- **Integration:** src/IsoPlayer.cpp (constructor/destructor)
- **Tests:** build/test_inventory.sh

---

## Phase 3: ✅ DONE

**Estimated:** 6-8 hours  
**Actual:** Complete (pre-built)  
**Next Phase:** Multi-threaded Pathfinding (8-10 hours)

---

## Quick Commands

```bash
# Test inventory system
./build/test_inventory.sh

# Compile game
cd build && make -j4

# Run game
./build/ProjectZomboidCpp
```
