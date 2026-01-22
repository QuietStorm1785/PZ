#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <deque>

namespace zombie {
namespace inventory {

class PerCallData {
public:
    std::vector<std::string> types;
    std::unordered_map<std::string, std::vector<std::shared_ptr<InventoryItem>>> typeToItems;
    std::deque<std::vector<std::shared_ptr<InventoryItem>>> itemLists;
    std::vector<std::shared_ptr<InventoryItem>> savedItems;
    std::shared_ptr<PerCallData> next;

    PerCallData() = default;

    void reset() {
        for (const auto& type : types) {
            auto& itemList = typeToItems[type];
            itemList.clear();
            itemLists.push_back(std::move(itemList));
        }
        types.clear();
        typeToItems.clear();
        savedItems.clear();
    }

    std::vector<std::shared_ptr<InventoryItem>> allocItemList() {
        if (itemLists.empty()) {
            return {};
        } else {
            auto list = std::move(itemLists.front());
            itemLists.pop_front();
            return list;
        }
    }
};

} // namespace inventory
} // namespace zombie
