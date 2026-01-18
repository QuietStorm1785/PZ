#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/set/hash/TIntHashSet.h"
#include "zombie/GameTime.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace meta {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Meta {
public:
 static const Meta instance = new Meta();
 ArrayList<IsoGridSquare> SquaresProcessing = std::make_unique<ArrayList<>>();
 private ArrayList<IsoGridSquare> SquaresSeen = new ArrayList<>(2000);
 const TIntHashSet SquaresSeenSet = new TIntHashSet();

 void dealWithSquareSeen(IsoGridSquare square) {
 if (!GameClient.bClient) {
 if (square.hourLastSeen != (int)GameTime.getInstance().getWorldAgeHours()) {
 synchronized (this->SquaresSeen) {
 if (!this->SquaresSeenSet.contains(square.getID())) {
 this->SquaresSeen.add(square);
 this->SquaresSeenSet.add(square.getID());
 }
 }
 }
 }
 }

 void dealWithSquareSeenActual(IsoGridSquare square) {
 if (!GameClient.bClient) {
 IsoMetaGrid.Zone zone = square.zone;
 if (zone != nullptr) {
 zone.setHourSeenToCurrent();
 }

 if (GameServer.bServer) {
 SafeHouse safeHouse = SafeHouse.getSafeHouse(square);
 if (safeHouse != nullptr) {
 safeHouse.updateSafehouse(nullptr);
 }
 }

 square.setHourSeenToCurrent();
 }
 }

 void update() {
 if (!GameClient.bClient) {
 this->SquaresProcessing.clear();
 synchronized (this->SquaresSeen) {
 this->SquaresProcessing.addAll(this->SquaresSeen);
 this->SquaresSeen.clear();
 this->SquaresSeenSet.clear();
 }

 for (int int0 = 0; int0 < this->SquaresProcessing.size(); int0++) {
 this->dealWithSquareSeenActual(this->SquaresProcessing.get(int0);
 }

 this->SquaresProcessing.clear();
 }
 }
}
} // namespace meta
} // namespace zombie
