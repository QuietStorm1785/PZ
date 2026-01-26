#include "zombie/iso/BentFences.h"

namespace zombie {
namespace iso {

BentFences& BentFences::getInstance() {
    static BentFences instance;
    return instance;
}

BentFences::BentFences() = default;

void BentFences::tableToTiles(KahluaTableImpl* table, std::vector<std::string>& out) {
    if (table) {
        KahluaTableIterator it = table->iterator();
        while (it.advance()) {
            out.push_back(it.getValue().toString());
        }
    }
}

void BentFences::tableToTiles(KahluaTable* table, std::vector<std::string>& out, const std::string& key) {
    tableToTiles(static_cast<KahluaTableImpl*>(table->rawget(key)), out);
}

void BentFences::addFenceTiles(int version, KahluaTableImpl* tiles) {
    KahluaTableIterator it = tiles->iterator();
    while (it.advance()) {
        KahluaTableImpl* entryTable = static_cast<KahluaTableImpl*>(it.getValue());
        Entry entry;
        entry.dir = IsoDirectionsFromString(entryTable->rawgetStr("dir"));
        tableToTiles(entryTable, entry.unbent, "unbent");
        tableToTiles(entryTable, entry.bent, "bent");
        if (!entry.unbent.empty() && entry.unbent.size() == entry.bent.size()) {
            m_entries.push_back(entry);
            Entry* entryPtr = &m_entries.back();
            for (const auto& name : entry.unbent) {
                m_unbentMap[name].push_back(entryPtr);
            }
            for (const auto& name : entry.bent) {
                m_bentMap[name].push_back(entryPtr);
            }
        }
    }
}

bool BentFences::isBentObject(IsoObject* obj) const {
    return getEntryForObject(obj, IsoDirections::Invalid) != nullptr;
}

bool BentFences::isUnbentObject(IsoObject* obj) const {
    return getEntryForObject(obj, IsoDirections::Max) != nullptr;
}

BentFences::Entry* BentFences::getEntryForObject(IsoObject* obj, IsoDirections dir) const {
    if (obj && obj->sprite && !obj->sprite->name.empty()) {
        bool unbent = (dir != IsoDirections::Invalid);
        const auto& map = unbent ? m_unbentMap : m_bentMap;
        auto it = map.find(obj->sprite->name);
        if (it != map.end()) {
            for (Entry* entry : it->second) {
                if ((!unbent || dir == IsoDirections::Max || dir == entry->dir) && isValidObject(obj, entry, unbent)) {
                    return entry;
                }
            }
        }
    }
    return nullptr;
}

bool BentFences::isValidObject(IsoObject* obj, const Entry* entry, bool unbent) const {
    IsoCell* cell = IsoWorld::instance->CurrentCell;
    const auto& tiles = unbent ? entry->unbent : entry->bent;
    int idx = (tiles[2] == obj->sprite->name) ? 2 : (tiles[3] == obj->sprite->name ? 3 : -1);
    if (idx == -1) return false;
    for (size_t i = 0; i < tiles.size(); ++i) {
        int x = obj->square->x + (entry->isNorth() ? int(i) - idx : 0);
        int y = obj->square->y + (entry->isNorth() ? 0 : int(i) - idx);
        IsoGridSquare* sq = cell->getGridSquare(x, y, obj->square->z);
        if (!sq) return false;
        if (int(i) != idx && !getObjectForEntry(sq, tiles, int(i))) return false;
    }
    return true;
}

IsoObject* BentFences::getObjectForEntry(IsoGridSquare* sq, const std::vector<std::string>& tiles, int idx) const {
    for (auto* obj : sq->getObjects()) {
        if (obj->sprite && obj->sprite->name == tiles[idx]) {
            return obj;
        }
    }
    return nullptr;
}

void BentFences::swapTiles(IsoObject* obj, IsoDirections dir) {
    bool unbent = (dir != IsoDirections::Invalid);
    Entry* entry = getEntryForObject(obj, dir);
    if (entry) {
        if (unbent) {
            if (entry->isNorth() && dir != IsoDirections::N && dir != IsoDirections::S) return;
            if (!entry->isNorth() && dir != IsoDirections::W && dir != IsoDirections::E) return;
        }
        IsoCell* cell = IsoWorld::instance->CurrentCell;
        const auto& tiles = unbent ? entry->unbent : entry->bent;
        int idx = (tiles[2] == obj->sprite->name) ? 2 : (tiles[3] == obj->sprite->name ? 3 : -1);
        for (size_t i = 0; i < tiles.size(); ++i) {
            int x = obj->square->x + (entry->isNorth() ? int(i) - idx : 0);
            int y = obj->square->y + (entry->isNorth() ? 0 : int(i) - idx);
            IsoGridSquare* sq = cell->getGridSquare(x, y, obj->square->z);
            if (sq) {
                IsoObject* o = getObjectForEntry(sq, tiles, int(i));
                if (o) {
                    const std::string& name = unbent ? entry->bent[i] : entry->unbent[i];
                    IsoSprite* sprite = IsoSpriteManager::instance->getSprite(name);
                    sprite->name = name;
                    o->setSprite(sprite);
                    o->transmitUpdatedSprite();
                    sq->RecalcAllWithNeighbours(true);
                    MapCollisionData::instance->squareChanged(sq);
                    PolygonalMap2::instance->squareChanged(sq);
                    IsoRegions::squareChanged(sq);
                }
            }
        }
    }
}

void BentFences::bendFence(IsoObject* obj, IsoDirections dir) {
    swapTiles(obj, dir);
}

void BentFences::unbendFence(IsoObject* obj) {
    swapTiles(obj, IsoDirections::Invalid);
}

void BentFences::Reset() {
    m_entries.clear();
    m_bentMap.clear();
    m_unbentMap.clear();
    m_collapsedTiles.clear();
    m_debrisTiles.clear();
    m_fenceMap.clear();
}

bool BentFences::Entry::isNorth() const {
    return dir == IsoDirections::N || dir == IsoDirections::S;
}

// ... (stubs for all other methods as needed)

} // namespace iso
} // namespace zombie
