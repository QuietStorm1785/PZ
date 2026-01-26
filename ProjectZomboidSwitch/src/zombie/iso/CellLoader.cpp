
#include "zombie/iso/CellLoader.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoTree.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/IsoObjectType.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoPushableObject.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoLightSource.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoBarbecue.h"
#include "zombie/iso/objects/IsoFireplace.h"
#include "zombie/iso/objects/IsoCombinationWasherDryer.h"
#include "zombie/iso/objects/IsoClothingDryer.h"
#include "zombie/iso/objects/IsoClothingWasher.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/iso/objects/IsoJukebox.h"
#include "zombie/iso/objects/IsoRadio.h"
#include "zombie/iso/objects/IsoTelevision.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/iso/IsoLot.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/WorldStreamer.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/DebugLog.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Core.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>

namespace zombie {
namespace iso {

// Static field definitions
std::vector<std::shared_ptr<IsoObject>> CellLoader::isoObjectCache;
std::vector<std::shared_ptr<IsoTree>> CellLoader::isoTreeCache;
int CellLoader::wanderX = 0;
int CellLoader::wanderY = 0;
std::shared_ptr<IsoRoom> CellLoader::wanderRoom = nullptr;
std::unordered_set<std::string> CellLoader::missingTiles;
std::unordered_map<std::shared_ptr<IsoSprite>, std::shared_ptr<IsoSprite>> CellLoader::smashedWindowSpriteMap;

void CellLoader::DoTileObjectCreation(std::shared_ptr<IsoSprite> sprite, IsoObjectType type, std::shared_ptr<IsoGridSquare> square, std::shared_ptr<IsoCell> cell, int x, int y, int z, const std::string& name) {
    // Full port of Java logic
    std::shared_ptr<IsoObject> obj = nullptr;
    if (!square) return;
    bool smashed = false;
    auto it = smashedWindowSpriteMap.find(sprite);
    if (it != smashedWindowSpriteMap.end()) {
        sprite = it->second;
        type = sprite->getType();
        smashed = true;
    }
    auto& props = sprite->getProperties();
    if (sprite->solidfloor && props.Is(IsoFlagType::diamondFloor) && !props.Is(IsoFlagType::transparentFloor)) {
        auto floor = square->getFloor();
        if (floor && floor->getProperties().Is(IsoFlagType::diamondFloor)) {
            floor->clearAttachedAnimSprite();
            floor->setSprite(sprite);
            return;
        }
    }
    // Door logic
    if (type == IsoObjectType::doorW || type == IsoObjectType::doorN) {
        auto door = std::make_shared<IsoDoor>(cell, square, sprite, type == IsoObjectType::doorN);
        obj = door;
        AddSpecialObject(square, door);
        if (props.Is("DoubleDoor")) {
            door->Locked = false;
            door->lockedByKey = false;
        }
        if (props.Is("GarageDoor")) {
            door->Locked = !door->IsOpen();
            door->lockedByKey = false;
        }
        GameClient::instance->objectSyncReq.putRequest(square, door);
    } else if (type == IsoObjectType::lightswitch) {
        obj = std::make_shared<IsoLightSwitch>(cell, square, sprite, square->getRoomID());
        AddObject(square, obj);
        GameClient::instance->objectSyncReq.putRequest(square, obj);
        if (obj->sprite->getProperties().Is("lightR")) {
            float r = std::stof(obj->sprite->getProperties().Val("lightR")) / 255.0f;
            float g = std::stof(obj->sprite->getProperties().Val("lightG")) / 255.0f;
            float b = std::stof(obj->sprite->getProperties().Val("lightB")) / 255.0f;
            int radius = 10;
            if (obj->sprite->getProperties().Is("LightRadius") && std::stoi(obj->sprite->getProperties().Val("LightRadius")) > 0) {
                radius = std::stoi(obj->sprite->getProperties().Val("LightRadius"));
            }
            auto light = std::make_shared<IsoLightSource>(obj->square->getX(), obj->square->getY(), obj->square->getZ(), r, g, b, radius);
            light->bActive = true;
            light->bHydroPowered = true;
            light->switches.push_back(std::static_pointer_cast<IsoLightSwitch>(obj));
            std::static_pointer_cast<IsoLightSwitch>(obj)->lights.push_back(light);
        } else {
            std::static_pointer_cast<IsoLightSwitch>(obj)->lightRoom = true;
        }
    } else if (type != IsoObjectType::curtainN && type != IsoObjectType::curtainS && type != IsoObjectType::curtainE && type != IsoObjectType::curtainW) {
        if (props.Is(IsoFlagType::windowW) || props.Is(IsoFlagType::windowN)) {
            obj = std::make_shared<IsoWindow>(cell, square, sprite, props.Is(IsoFlagType::windowN));
            if (smashed) {
                std::static_pointer_cast<IsoWindow>(obj)->setSmashed(true);
            }
            AddSpecialObject(square, obj);
            GameClient::instance->objectSyncReq.putRequest(square, obj);
        } else if (props.Is(IsoFlagType::container) && props.Val("container") == "barbecue") {
            obj = std::make_shared<IsoBarbecue>(cell, square, sprite);
            AddObject(square, obj);
        } else if (props.Is(IsoFlagType::container) && props.Val("container") == "fireplace") {
            obj = std::make_shared<IsoFireplace>(cell, square, sprite);
            AddObject(square, obj);
        } else if (props.Val("IsoType") == "IsoCombinationWasherDryer") {
            obj = std::make_shared<IsoCombinationWasherDryer>(cell, square, sprite);
            AddObject(square, obj);
        } else if (props.Is(IsoFlagType::container) && props.Val("container") == "clothingdryer") {
            obj = std::make_shared<IsoClothingDryer>(cell, square, sprite);
            AddObject(square, obj);
        } else if (props.Is(IsoFlagType::container) && props.Val("container") == "clothingwasher") {
            obj = std::make_shared<IsoClothingWasher>(cell, square, sprite);
            AddObject(square, obj);
        } else if (props.Is(IsoFlagType::container) && props.Val("container") == "woodstove") {
            obj = std::make_shared<IsoFireplace>(cell, square, sprite);
            AddObject(square, obj);
        } else if (!props.Is(IsoFlagType::container) || (props.Val("container") != "stove" && props.Val("container") != "microwave")) {
            if (type == IsoObjectType::jukebox) {
                obj = std::make_shared<IsoJukebox>(cell, square, sprite);
                obj->OutlineOnMouseover = true;
                AddObject(square, obj);
            } else if (type == IsoObjectType::radio) {
                obj = std::make_shared<IsoRadio>(cell, square, sprite);
                AddObject(square, obj);
            } else if (props.Is("signal")) {
                std::string signal = props.Val("signal");
                if (signal == "radio") {
                    obj = std::make_shared<IsoRadio>(cell, square, sprite);
                } else if (signal == "tv") {
                    obj = std::make_shared<IsoTelevision>(cell, square, sprite);
                }
                AddObject(square, obj);
            } else {
                if (props.Is(IsoFlagType::WallOverlay)) {
                    std::shared_ptr<IsoObject> wallObj = nullptr;
                    if (props.Is(IsoFlagType::attachedSE)) wallObj = square->getWallSE();
                    else if (props.Is(IsoFlagType::attachedW)) wallObj = square->getWall(false);
                    else if (props.Is(IsoFlagType::attachedN)) wallObj = square->getWall(true);
                    else {
                        for (int i = square->getObjects().size() - 1; i >= 0; --i) {
                            auto candidate = square->getObjects()[i];
                            if (candidate->sprite->getProperties().Is(IsoFlagType::cutW) || candidate->sprite->getProperties().Is(IsoFlagType::cutN)) {
                                wallObj = candidate;
                                break;
                            }
                        }
                    }
                    if (wallObj) {
                        if (!wallObj->AttachedAnimSprite) wallObj->AttachedAnimSprite = std::make_shared<std::vector<std::shared_ptr<IsoSpriteInstance>>>();
                        wallObj->AttachedAnimSprite->push_back(IsoSpriteInstance::get(sprite));
                    } else {
                        obj = IsoObject::getNew();
                        obj->sx = 0.0f;
                        obj->sprite = sprite;
                        obj->square = square;
                        AddObject(square, obj);
                    }
                    return;
                }
                if (props.Is(IsoFlagType::FloorOverlay)) {
                    auto floorObj = square->getFloor();
                    if (floorObj) {
                        if (!floorObj->AttachedAnimSprite) floorObj->AttachedAnimSprite = std::make_shared<std::vector<std::shared_ptr<IsoSpriteInstance>>>();
                        floorObj->AttachedAnimSprite->push_back(IsoSpriteInstance::get(sprite));
                    }
                } else if (IsoMannequin::isMannequinSprite(sprite)) {
                    obj = std::make_shared<IsoMannequin>(cell, square, sprite);
                    AddObject(square, obj);
                } else if (type == IsoObjectType::tree) {
                    if (sprite->getName() && sprite->getName().find("vegetation_trees") == 0) {
                        auto floorObj = square->getFloor();
                        if (!floorObj || !floorObj->getSprite() || !floorObj->getSprite()->getName() || floorObj->getSprite()->getName().find("blends_natural") != 0) {
                            DebugLog::log("ERROR: removed tree at " + std::to_string(square->x) + "," + std::to_string(square->y) + "," + std::to_string(square->z) + " because floor is not blends_natural");
                            return;
                        }
                    }
                    obj = IsoTree::getNew();
                    obj->sprite = sprite;
                    obj->square = square;
                    obj->sx = 0.0f;
                    std::static_pointer_cast<IsoTree>(obj)->initTree();
                    for (size_t i = 0; i < square->getObjects().size(); ++i) {
                        auto candidate = square->getObjects()[i];
                        if (std::dynamic_pointer_cast<IsoTree>(candidate)) {
                            square->getObjects().erase(square->getObjects().begin() + i);
                            candidate->reset();
                            isoTreeCache.push_back(std::static_pointer_cast<IsoTree>(candidate));
                            break;
                        }
                    }
                    AddObject(square, obj);
                } else {
                    // Handle missing tiles
                    if ((sprite->CurrentAnim.Frames.empty() || !sprite->CurrentAnim.Frames[0]->getTexture(IsoDirections::N)) && !GameServer::bServer) {
                        if (missingTiles.find(name) == missingTiles.end()) {
                            if (Core::bDebug) DebugLog::General::error("CellLoader> missing tile " + name);
                            missingTiles.insert(name);
                        }
                        sprite->LoadFramesNoDirPageSimple(Core::bDebug ? "media/ui/missing-tile-debug.png" : "media/ui/missing-tile.png");
                        if (sprite->CurrentAnim.Frames.empty() || !sprite->CurrentAnim.Frames[0]->getTexture(IsoDirections::N)) return;
                    }
                    std::string texName = GameServer::bServer ? std::string() : sprite->CurrentAnim.Frames[0]->getTexture(IsoDirections::N)->getName();
                    bool normalObj = true;
                    if (!GameServer::bServer && texName.find("TileObjectsExt") != std::string::npos && (texName.find("_5") != std::string::npos || texName.find("_6") != std::string::npos || texName.find("_7") != std::string::npos || texName.find("_8") != std::string::npos)) {
                        obj = std::make_shared<IsoWheelieBin>(cell, x, y, z);
                        if (texName.find("_5") != std::string::npos) obj->dir = IsoDirections::S;
                        if (texName.find("_6") != std::string::npos) obj->dir = IsoDirections::W;
                        if (texName.find("_7") != std::string::npos) obj->dir = IsoDirections::N;
                        if (texName.find("_8") != std::string::npos) obj->dir = IsoDirections::E;
                        normalObj = false;
                    }
                    if (normalObj) {
                        obj = IsoObject::getNew();
                        obj->sx = 0.0f;
                        obj->sprite = sprite;
                        obj->square = square;
                        AddObject(square, obj);
                        if (obj->sprite->getProperties().Is("lightR")) {
                            float r = std::stof(obj->sprite->getProperties().Val("lightR"));
                            float g = std::stof(obj->sprite->getProperties().Val("lightG"));
                            float b = std::stof(obj->sprite->getProperties().Val("lightB"));
                            cell->getLamppostPositions().push_back(std::make_shared<IsoLightSource>(obj->square->getX(), obj->square->getY(), obj->square->getZ(), r, g, b, 8));
                        }
                    }
                }
            }
        } else {
            obj = std::make_shared<IsoStove>(cell, square, sprite);
            AddObject(square, obj);
            GameClient::instance->objectSyncReq.putRequest(square, obj);
        }
    } else {
        bool curtainDir = std::stoi(name.substr(name.find_last_of('_') + 1)) % 8 <= 3;
        obj = std::make_shared<IsoCurtain>(cell, square, sprite, type == IsoObjectType::curtainN || type == IsoObjectType::curtainS, curtainDir);
        AddSpecialObject(square, obj);
        GameClient::instance->objectSyncReq.putRequest(square, obj);
    }
    if (obj) {
        obj->tile = name;
        obj->createContainersFromSpriteProperties();
        if (obj->sprite->getProperties().Is(IsoFlagType::vegitation)) {
            obj->tintr = 0.7f + Rand::Next(30) / 100.0f;
            obj->tintg = 0.7f + Rand::Next(30) / 100.0f;
            obj->tintb = 0.7f + Rand::Next(30) / 100.0f;
        }
    }
}

bool CellLoader::LoadCellBinaryChunk(std::shared_ptr<IsoCell> cell, int x, int y, std::shared_ptr<IsoChunk> chunk) {
    std::string lotName = "world_" + std::to_string(x / 30) + "_" + std::to_string(y / 30) + ".lotpack";
    auto it = IsoLot::InfoFileNames.find(lotName);
    if (it == IsoLot::InfoFileNames.end()) {
        DebugLog::log("LoadCellBinaryChunk: NO SUCH LOT " + lotName);
        return false;
    }
    std::string lotFilePath = it->second;
    std::ifstream lotFile(lotFilePath);
    if (!lotFile.good()) {
        DebugLog::log("LoadCellBinaryChunk: NO SUCH LOT FILE " + lotFilePath);
        return false;
    }
    std::shared_ptr<IsoLot> lot = nullptr;
    try {
        lot = IsoLot::get(x / 30, y / 30, x, y, chunk);
        cell->PlaceLot(lot, 0, 0, 0, chunk, x, y);
    } catch (...) {
        DebugLog::log("LoadCellBinaryChunk: Exception during lot loading");
        return false;
    }
    if (lot) {
        IsoLot::put(lot);
    }
    return true;
}

std::shared_ptr<IsoCell> CellLoader::LoadCellBinaryChunk(std::shared_ptr<IsoSpriteManager> spriteManager, int x, int y) {
    wanderX = 0;
    wanderY = 0;
    wanderRoom = nullptr;
    auto cell = std::make_shared<IsoCell>(300, 300);
    int numPlayers = IsoPlayer::numPlayers;
    uint8_t chunkMapCount = 1; // Java uses 1 unless multiplayer
    if (!GameServer::bServer) {
        if (GameClient::bClient) {
            WorldStreamer::instance->requestLargeAreaZip(x, y, IsoChunkMap::ChunkGridWidth / 2 + 2);
            IsoChunk::bDoServerRequests = false;
        }
        for (int playerIdx = 0; playerIdx < chunkMapCount; ++playerIdx) {
            cell->ChunkMap[playerIdx].setInitialPos(x, y);
            IsoPlayer::assumedPlayer = playerIdx;
            int startX = x - IsoChunkMap::ChunkGridWidth / 2;
            int startY = y - IsoChunkMap::ChunkGridWidth / 2;
            int endX = x + IsoChunkMap::ChunkGridWidth / 2 + 1;
            int endY = y + IsoChunkMap::ChunkGridWidth / 2 + 1;
            for (int cx = startX; cx < endX; ++cx) {
                for (int cy = startY; cy < endY; ++cy) {
                    if (IsoWorld::instance->getMetaGrid()->isValidChunk(cx, cy)) {
                        cell->ChunkMap[playerIdx].LoadChunk(cx, cy, cx - startX, cy - startY);
                    }
                }
            }
        }
    }
    IsoPlayer::assumedPlayer = 0;
    LuaEventManager::triggerEvent("OnPostMapLoad", cell, x, y);
    ConnectMultitileObjects(cell);
    return cell;
}

void CellLoader::RecurseMultitileObjects(std::shared_ptr<IsoCell> cell, std::shared_ptr<IsoGridSquare> sq1, std::shared_ptr<IsoGridSquare> sq2, std::vector<std::shared_ptr<IsoPushableObject>>& list) {
    if (!sq2) return;
    std::shared_ptr<IsoPushableObject> found = nullptr;
    bool connectY = false;
    for (const auto& movingObj : sq2->getMovingObjects()) {
        auto pushObj = std::dynamic_pointer_cast<IsoPushableObject>(movingObj);
        if (pushObj) {
            int dx = sq1->getX() - sq2->getX();
            int dy = sq1->getY() - sq2->getY();
            if (dy != 0 && pushObj->sprite->getProperties().Is("connectY")) {
                int connectVal = std::stoi(pushObj->sprite->getProperties().Val("connectY"));
                if (connectVal == dy) {
                    pushObj->connectList = list;
                    list.push_back(pushObj);
                    found = pushObj;
                    connectY = false;
                    break;
                }
            }
            if (dx != 0 && pushObj->sprite->getProperties().Is("connectX")) {
                int connectVal = std::stoi(pushObj->sprite->getProperties().Val("connectX"));
                if (connectVal == dx) {
                    pushObj->connectList = list;
                    list.push_back(pushObj);
                    found = pushObj;
                    connectY = true;
                    break;
                }
            }
        }
    }
    if (found) {
        if (found->sprite->getProperties().Is("connectY") && connectY) {
            int connectVal = std::stoi(found->sprite->getProperties().Val("connectY"));
            auto nextSq = cell->getGridSquare(found->getCurrentSquare()->getX(), found->getCurrentSquare()->getY() + connectVal, found->getCurrentSquare()->getZ());
            RecurseMultitileObjects(cell, found->getCurrentSquare(), nextSq, found->connectList);
        }
        if (found->sprite->getProperties().Is("connectX") && !connectY) {
            int connectVal = std::stoi(found->sprite->getProperties().Val("connectX"));
            auto nextSq = cell->getGridSquare(found->getCurrentSquare()->getX() + connectVal, found->getCurrentSquare()->getY(), found->getCurrentSquare()->getZ());
            RecurseMultitileObjects(cell, found->getCurrentSquare(), nextSq, found->connectList);
        }
    }
}

void CellLoader::ConnectMultitileObjects(std::shared_ptr<IsoCell> cell) {
    if (!cell) return;
    for (const auto& obj : cell->getObjectList()) {
        auto pushObj = std::dynamic_pointer_cast<IsoPushableObject>(obj);
        if (pushObj && (pushObj->sprite->getProperties().Is("connectY") || pushObj->sprite->getProperties().Is("connectX")) && !pushObj->connectList) {
            pushObj->connectList = std::make_shared<std::vector<std::shared_ptr<IsoPushableObject>>>();
            pushObj->connectList->push_back(pushObj);
            if (pushObj->sprite->getProperties().Is("connectY")) {
                int connectVal = std::stoi(pushObj->sprite->getProperties().Val("connectY"));
                auto nextSq = cell->getGridSquare(pushObj->getCurrentSquare()->getX(), pushObj->getCurrentSquare()->getY() + connectVal, pushObj->getCurrentSquare()->getZ());
                if (nextSq) {
                    RecurseMultitileObjects(cell, pushObj->getCurrentSquare(), nextSq, *pushObj->connectList);
                }
            }
            if (pushObj->sprite->getProperties().Is("connectX")) {
                int connectVal = std::stoi(pushObj->sprite->getProperties().Val("connectX"));
                auto nextSq = cell->getGridSquare(pushObj->getCurrentSquare()->getX() + connectVal, pushObj->getCurrentSquare()->getY(), pushObj->getCurrentSquare()->getZ());
                if (nextSq) {
                    RecurseMultitileObjects(cell, pushObj->getCurrentSquare(), nextSq, *pushObj->connectList);
                }
            }
        }
    }
}

void CellLoader::AddObject(std::shared_ptr<IsoGridSquare> square, std::shared_ptr<IsoObject> obj) {
    int idx = square->placeWallAndDoorCheck(obj, square->getObjects().size());
    if (idx != square->getObjects().size() && idx >= 0 && idx <= square->getObjects().size()) {
        square->getObjects().insert(square->getObjects().begin() + idx, obj);
    } else {
        square->getObjects().push_back(obj);
    }
}

void CellLoader::AddSpecialObject(std::shared_ptr<IsoGridSquare> square, std::shared_ptr<IsoObject> obj) {
    int idx = square->placeWallAndDoorCheck(obj, square->getObjects().size());
    if (idx != square->getObjects().size() && idx >= 0 && idx <= square->getObjects().size()) {
        square->getObjects().insert(square->getObjects().begin() + idx, obj);
    } else {
        square->getObjects().push_back(obj);
        square->getSpecialObjects().push_back(obj);
    }
}

} // namespace iso
} // namespace zombie
