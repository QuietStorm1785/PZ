#include "zombie/ai/MapKnowledge.h"

namespace zombie {
namespace ai {

KnownBlockedEdges* MapKnowledge::getKnownBlockedEdges(int var1, int var2, int var3) {
    for (auto& edge : knownBlockedEdges) {
        if (edge.x == var1 && edge.y == var2 && edge.z == var3) {
            return &edge;
        }
    }
    return nullptr;
}

KnownBlockedEdges* MapKnowledge::createKnownBlockedEdges(int var1, int var2, int var3) {
    assert(getKnownBlockedEdges(var1, var2, var3) == nullptr);
    KnownBlockedEdges edge = KnownBlockedEdges::alloc();
    edge.init(var1, var2, var3);
    knownBlockedEdges.push_back(edge);
    return &knownBlockedEdges.back();
}

KnownBlockedEdges* MapKnowledge::getOrCreateKnownBlockedEdges(int var1, int var2, int var3) {
    KnownBlockedEdges* edge = getKnownBlockedEdges(var1, var2, var3);
    if (edge == nullptr) {
        edge = createKnownBlockedEdges(var1, var2, var3);
    }
    return edge;
}

void MapKnowledge::releaseIfEmpty(KnownBlockedEdges* var1) {
    if (!var1->n && !var1->w) {
        auto it = std::find_if(knownBlockedEdges.begin(), knownBlockedEdges.end(), [&](const KnownBlockedEdges& edge) { return &edge == var1; });
        if (it != knownBlockedEdges.end()) {
            knownBlockedEdges.erase(it);
            var1->release();
        }
    }
}

void MapKnowledge::setKnownBlockedEdgeW(int var1, int var2, int var3, bool var4) {
    KnownBlockedEdges* edge = getOrCreateKnownBlockedEdges(var1, var2, var3);
    edge->w = var4;
    releaseIfEmpty(edge);
}

void MapKnowledge::setKnownBlockedEdgeN(int var1, int var2, int var3, bool var4) {
    KnownBlockedEdges* edge = getOrCreateKnownBlockedEdges(var1, var2, var3);
    edge->n = var4;
    releaseIfEmpty(edge);
}

void MapKnowledge::setKnownBlockedDoor(IsoDoor* var1, bool var2) {
    IsoGridSquare* square = var1->getSquare();
    if (var1->getNorth()) {
        setKnownBlockedEdgeN(square->x, square->y, square->z, var2);
    } else {
        setKnownBlockedEdgeW(square->x, square->y, square->z, var2);
    }
}

void MapKnowledge::setKnownBlockedDoor(IsoThumpable* var1, bool var2) {
    if (var1->isDoor()) {
        IsoGridSquare* square = var1->getSquare();
        if (var1->getNorth()) {
            setKnownBlockedEdgeN(square->x, square->y, square->z, var2);
        } else {
            setKnownBlockedEdgeW(square->x, square->y, square->z, var2);
        }
    }
}

void MapKnowledge::setKnownBlockedWindow(IsoWindow* var1, bool var2) {
    IsoGridSquare* square = var1->getSquare();
    if (var1->getNorth()) {
        setKnownBlockedEdgeN(square->x, square->y, square->z, var2);
    } else {
        setKnownBlockedEdgeW(square->x, square->y, square->z, var2);
    }
}

void MapKnowledge::setKnownBlockedWindowFrame(IsoObject* var1, bool var2) {
    IsoGridSquare* square = var1->getSquare();
    if (IsoWindowFrame::isWindowFrame(var1, true)) {
        setKnownBlockedEdgeN(square->x, square->y, square->z, var2);
    } else if (IsoWindowFrame::isWindowFrame(var1, false)) {
        setKnownBlockedEdgeW(square->x, square->y, square->z, var2);
    }
}

void MapKnowledge::forget() {
    KnownBlockedEdges::releaseAll(knownBlockedEdges);
    knownBlockedEdges.clear();
}

} // namespace ai
} // namespace zombie
