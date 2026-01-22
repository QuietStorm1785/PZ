#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/inventory/CompressIdenticalItems$1.h"
#include "zombie/inventory/CompressIdenticalItems$PerCallData.h"
#include "zombie/inventory/CompressIdenticalItems$PerThreadData.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/core/ByteBuffer.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {


class CompressIdenticalItems {
public:
    static const int BLOCK_SIZE = 1024;
private:
    static thread_local std::shared_ptr<PerThreadData> perThreadVars;

    static int bufferSize(int var0) {
      return (var0 + 1024 - 1) / 1024 * 1024;
   }

    static std::shared_ptr<ByteBuffer> ensureCapacity(std::shared_ptr<ByteBuffer> buffer, int capacity) {
        if (buffer == nullptr || buffer->capacity() < capacity) {
            return ByteBuffer::allocate(bufferSize(capacity));
        }
        return buffer;
    }

    static std::shared_ptr<ByteBuffer> ensureCapacity(std::shared_ptr<ByteBuffer> buffer) {
        if (buffer == nullptr) {
            return ByteBuffer::allocate(1024);
        } else if (buffer->capacity() - buffer->position() < 1024) {
            auto newBuffer = ensureCapacity(nullptr, buffer->position() + 1024);
            newBuffer->put(buffer->array(), 0, buffer->position());
            newBuffer->position(buffer->position());
            return newBuffer;
        } else {
            auto newBuffer = ensureCapacity(nullptr, buffer->capacity() + 1024);
            newBuffer->put(buffer->array(), 0, buffer->position());
            newBuffer->position(buffer->position());
            return newBuffer;
        }
    }

    static bool setCompareItem(std::shared_ptr<PerThreadData> data, std::shared_ptr<InventoryItem> item) {
        auto buffer = data->itemCompareBuffer;
        buffer->clear();
        int originalId = item->id;
        item->id = 0;

        bool result = false;
        try {
            while (true) {
                try {
                    buffer->putInt(0);
                    item->save(buffer.get(), false);
                    int savedSize = buffer->position();
                    buffer->position(0);
                    buffer->putInt(savedSize);
                    buffer->position(savedSize);
                    result = true;
                    break;
                } catch (const std::out_of_range&) {
                    buffer = ensureCapacity(buffer);
                    buffer->clear();
                    data->itemCompareBuffer = buffer;
                }
            }
        } catch (...) {
            // Restore original ID on any exception
            item->id = originalId;
            throw;
        }
        item->id = originalId;
        return result;
    }

    static bool areItemsIdentical(std::shared_ptr<PerThreadData> data, std::shared_ptr<InventoryItem> item1, std::shared_ptr<InventoryItem> item2) {
        if (std::dynamic_pointer_cast<InventoryContainer>(item1) != nullptr) {
            auto container1 = std::dynamic_pointer_cast<InventoryContainer>(item1)->getItemContainer();
            auto container2 = std::dynamic_pointer_cast<InventoryContainer>(item2)->getItemContainer();
            if (!container1->getItems().empty() || !container2->getItems().empty()) {
                return false;
            }
        }

        auto byteData1 = item1->getByteData();
        auto byteData2 = item2->getByteData();
        if (byteData1 != nullptr) {
            if (byteData1->position() != 0) {
                return false;
            }
            if (byteData1 != byteData2) {
                return false;
            }
        } else if (byteData2 != nullptr) {
            return false;
        }

        std::shared_ptr<ByteBuffer> buffer = nullptr;
        int originalId = item2->id;
        item2->id = 0;

        bool result = false;
        try {
            while (true) {
                try {
                    buffer = data->itemCompareBuffer;
                    buffer->position(0);
                    int dataSize = buffer->getInt();
                    int dataStart = buffer->position();
                    buffer->position(dataSize);
                    int saveStart = buffer->position();
                    item2->save(buffer.get(), false);
                    int saveEnd = buffer->position();
                    if (saveEnd - saveStart != dataSize - dataStart) {
                        result = false;
                        break;
                    }

                    bool identical = true;
                    for (int i = 0; i < dataSize - dataStart; i++) {
                        if (buffer->array()[dataStart + i] != buffer->array()[saveStart + i]) {
                            identical = false;
                            break;
                        }
                    }
                    result = identical;
                    break;
                } catch (const std::out_of_range&) {
                    buffer = ensureCapacity(buffer);
                    buffer->clear();
                    data->itemCompareBuffer = buffer;
                    setCompareItem(data, item1);
                }
            }
        } catch (...) {
            item2->id = originalId;
            throw;
        }
        item2->id = originalId;
        return result;
    }

    // Saves items to a byte buffer, compressing identical items
    static std::vector<std::shared_ptr<InventoryItem>> save(std::shared_ptr<ByteBuffer> buffer, const std::vector<std::shared_ptr<InventoryItem>>& items, std::shared_ptr<IsoGameCharacter> character) {
        auto threadData = perThreadVars;
        if (!threadData) {
            threadData = std::make_shared<PerThreadData>();
            perThreadVars = threadData;
        }
        auto callData = threadData->allocSaveVars();
        auto& typeToItems = callData->typeToItems;
        auto& types = callData->types;

        try {
            for (size_t i = 0; i < items.size(); i++) {
                std::string fullType = items[i]->getFullType();
                if (typeToItems.find(fullType) == typeToItems.end()) {
                    typeToItems[fullType] = callData->allocItemList();
                    types.push_back(fullType);
                }
                typeToItems[fullType]->push_back(items[i]);
            }

            int startPos = buffer->position();
            buffer->putShort(0);
            int itemCount = 0;

            for (size_t typeIndex = 0; typeIndex < types.size(); typeIndex++) {
                auto& itemList = *typeToItems[types[typeIndex]];

                for (size_t itemIndex = 0; itemIndex < itemList.size(); itemIndex++) {
                    auto item = itemList[itemIndex];
                    callData->savedItems.push_back(item);
                    int count = 1;
                    size_t startIndex = itemIndex + 1;
                    if (character == nullptr || !character->isEquipped(item)) {
                        setCompareItem(threadData, item);

                        while (itemIndex + 1 < itemList.size() && areItemsIdentical(threadData, item, itemList[itemIndex + 1])) {
                            callData->savedItems.push_back(itemList[itemIndex + 1]);
                            itemIndex++;
                            count++;
                        }
                    }

                    buffer->putInt(count);
                    item->saveWithSize(buffer.get(), false);
                    if (count > 1) {
                        for (size_t j = startIndex; j <= itemIndex; j++) {
                            buffer->putInt(itemList[j]->id);
                        }
                    }

                    itemCount += count;
                }
            }

            int endPos = buffer->position();
            buffer->position(startPos);
            buffer->putShort(static_cast<int16_t>(itemCount));
            buffer->position(endPos);

            return callData->savedItems;
        } catch (...) {
            // Restore callData to pool on exception
            callData->next = threadData->saveVars;
            threadData->saveVars = callData;
            throw;
        }
        // Restore callData to pool
        callData->next = threadData->saveVars;
        threadData->saveVars = callData;
    }

    // Loads items from a byte buffer, decompressing identical items
    static std::vector<std::shared_ptr<InventoryItem>> load(std::shared_ptr<ByteBuffer> buffer, int version, std::vector<std::shared_ptr<InventoryItem>>& items, std::vector<std::shared_ptr<InventoryItem>>& obsoleteItems) {
        auto threadData = perThreadVars;
        if (!threadData) {
            threadData = std::make_shared<PerThreadData>();
            perThreadVars = threadData;
        }
        auto callData = threadData->allocSaveVars();
        if (!items.empty()) {
            items.clear();
        }

        if (!obsoleteItems.empty()) {
            obsoleteItems.clear();
        }

        try {
            int16_t itemCount = buffer->getShort();

            for (int i = 0; i < itemCount; i++) {
                int count = 1;
                if (version >= 149) {
                    count = buffer->getInt();
                } else if (version >= 128) {
                    count = buffer->getShort();
                }

                int startPos = buffer->position();
                auto item = InventoryItem::loadItem(buffer.get(), version);
                if (item == nullptr) {
                    int skipBytes = count > 1 ? (count - 1) * 4 : 0;
                    buffer->position(buffer->position() + skipBytes);

                    for (int j = 0; j < count; j++) {
                        obsoleteItems.push_back(nullptr);
                        callData->savedItems.push_back(nullptr);
                    }
                } else {
                    for (int j = 0; j < count; j++) {
                        if (j > 0) {
                            buffer->position(startPos);
                            item = InventoryItem::loadItem(buffer.get(), version);
                        }

                        if (!items.empty()) {
                            items.push_back(item);
                        }

                        if (!obsoleteItems.empty()) {
                            obsoleteItems.push_back(item);
                        }

                        callData->savedItems.push_back(item);
                    }

                    if (version >= 128) {
                        for (int j = 1; j < count; j++) {
                            int id = buffer->getInt();
                            auto existingItem = callData->savedItems[callData->savedItems.size() - count + j];
                            if (existingItem != nullptr) {
                                existingItem->id = id;
                            }
                        }
                    }
                }
            }

            return callData->savedItems;
        } catch (...) {
            // Restore callData to pool on exception
            callData->next = threadData->saveVars;
            threadData->saveVars = callData;
            throw;
        }
        // Restore callData to pool
        callData->next = threadData->saveVars;
        threadData->saveVars = callData;
    }

    // Saves a single item to a byte buffer
    static void save(std::shared_ptr<ByteBuffer> buffer, std::shared_ptr<InventoryItem> item) {
        buffer->putShort(1);
        buffer->putInt(1);
        item->saveWithSize(buffer.get(), false);
    }
};

// Define the thread-local variable
thread_local std::shared_ptr<PerThreadData> CompressIdenticalItems::perThreadVars = nullptr;

} // namespace inventory
} // namespace zombie
