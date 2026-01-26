#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/ContainerOverlays$ContainerOverlayEntry.h"
#include "zombie/iso/ContainerOverlays$ContainerOverlay.h"

namespace zombie {
namespace iso {

class ContainerOverlays {
public:
    static std::shared_ptr<ContainerOverlays> instance;
    static std::vector<std::shared_ptr<ContainerOverlayEntry>> tempEntries;

    ContainerOverlays();
    ~ContainerOverlays();

    void Reset();
    void addOverlays(lua_State* L, int tableIndex);
    std::vector<std::string> getUnderlyingSpriteNames(const std::string& name);
    bool hasOverlays(const std::shared_ptr<IsoObject>& obj) const;
    void updateContainerOverlaySprite(const std::shared_ptr<IsoObject>& obj);

    // Internal overlay map
    std::unordered_map<std::string, std::shared_ptr<ContainerOverlay>> overlayMap;
    std::unordered_map<std::string, std::vector<std::string>> overlayNameToUnderlyingName;

private:
    void parseContainerOverlayMapV0(lua_State* L, int tableIndex);
    void parseContainerOverlayMapV1(lua_State* L, int tableIndex);
};

} // namespace iso
} // namespace zombie
