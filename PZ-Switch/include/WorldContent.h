#pragma once
#include "IsoObject.h"
#include <string>
#include <vector>

class Item;

// Simple world object variants used for populating grid squares
class IsoTree : public IsoObject {
public:
 IsoTree();
 void onInteract(zombie::characters::IsoPlayer* player) override;
};

class IsoFurniture : public IsoObject {
public:
 IsoFurniture();
 void onInteract(zombie::characters::IsoPlayer* player) override;
};

class IsoContainer : public IsoObject {
public:
 IsoContainer();
 void onInteract(zombie::characters::IsoPlayer* player) override;
 
 // Container storage
 bool addItem(Item* item);
 bool removeItem(Item* item);
 const std::vector<Item*>& getItems() const { return items; }
 int getItemCount() const { return items.size(); }
 int getMaxItems() const { return maxItems; }
 
 bool isLocked() const { return locked; }
 void setLocked(bool l) { locked = l; }
 
private:
 std::vector<Item*> items;
 int maxItems;
 bool locked;
};

// Factory for creating objects by type string
class IsoWorldObjectFactory {
public:
 static IsoObject* create(const std::string& type, bool forceSolid = false);
};
