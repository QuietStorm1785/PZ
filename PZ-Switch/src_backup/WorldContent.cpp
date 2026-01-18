#include "WorldContent.h"
#include "IsoPlayer.h"
#include "AudioInteractionSystem.h"
#include "InventoryManager.h"
#include <iostream>
#include <algorithm>

IsoTree::IsoTree() {
    setSolid(false);
    setType("tree");
}

void IsoTree::onInteract(zombie::characters::IsoPlayer* player) {
    IsoObject::onInteract(player);  // Plays tree sound
    std::cout << "You rustle the tree leaves." << std::endl;
}

IsoFurniture::IsoFurniture() {
    setSolid(true); // blocks movement by default
    setType("furniture");
}

void IsoFurniture::onInteract(zombie::characters::IsoPlayer* player) {
    IsoObject::onInteract(player);  // Plays furniture sound
    std::cout << "You bump into the furniture." << std::endl;
}

IsoContainer::IsoContainer() {
    setSolid(true);
    setType("container");
    maxItems = 20;
    locked = false;
}

void IsoContainer::onInteract(zombie::characters::IsoPlayer* player) {
    (void)player;
    
    if (locked) {
        std::cout << "The container is locked." << std::endl;
        return;
    }
    
    // Play container open sound specifically
    auto audio = AudioInteractionSystem::getInstance();
    audio->playObjectSound("container", "open", getX(), getY());
    
    if (items.empty()) {
        std::cout << "You check the container. It's empty." << std::endl;
    } else {
        std::cout << "Container contains " << items.size() << " items." << std::endl;
        for (const auto* item : items) {
            if (item) {
                std::cout << "  - " << item->getName() << std::endl;
            }
        }
    }
}

bool IsoContainer::addItem(Item* item) {
    if (!item) return false;
    if (items.size() >= static_cast<size_t>(maxItems)) return false;
    
    items.push_back(item);
    return true;
}

bool IsoContainer::removeItem(Item* item) {
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
        return true;
    }
    return false;
}

IsoObject* IsoWorldObjectFactory::create(const std::string& type, bool forceSolid) {
    std::string t = type;
    // lowercase normalize
    for (auto& c : t) c = static_cast<char>(::tolower(c));

    IsoObject* obj = nullptr;
    if (t == "tree") {
        obj = new IsoTree();
    } else if (t == "furniture") {
        obj = new IsoFurniture();
    } else if (t == "container" || t == "crate" || t == "locker") {
        obj = new IsoContainer();
    }

    if (obj && forceSolid) {
        obj->setSolid(true);
    }
    return obj;
}
