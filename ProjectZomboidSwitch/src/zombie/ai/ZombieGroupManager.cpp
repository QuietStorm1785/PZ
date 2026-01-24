#include "zombie/ai/ZombieGroupManager.h"

namespace zombie {
namespace ai {

void ZombieGroupManager::preupdate() {
    tickCount += GameTime::getInstance().getMultiplier() / 1.6f;
    if (tickCount >= 30.0f) {
        tickCount = 0.0f;
    }
    int rallyGroupSize = SandboxOptions::instance.zombieConfig.RallyGroupSize.getValue();
    for (size_t i = 0; i < groups.size(); ++i) {
        ZombieGroup* group = groups[i];
        group->update();
        if (group->isEmpty()) {
            freeGroups.push_back(group);
            groups.erase(groups.begin() + i);
            --i;
        }
    }
}

void ZombieGroupManager::Reset() {
    freeGroups.insert(freeGroups.end(), groups.begin(), groups.end());
    groups.clear();
}

bool ZombieGroupManager::shouldBeInGroup(IsoZombie var1) {
    if (var1 == nullptr) return false;
    if (SandboxOptions::instance.zombieConfig.RallyGroupSize.getValue() <= 1) return false;
    if (!Core::getInstance().isZombieGroupSound()) return false;
    if (var1->isUseless()) return false;
    if (var1->isDead() || var1->isFakeDead()) return false;
    if (var1->isSitAgainstWall()) return false;
    if (var1->target != nullptr) return false;
    if (var1->getCurrentBuilding() != nullptr) return false;
    if (VirtualZombieManager::instance.isReused(var1)) return false;
    IsoGridSquare* square = var1->getSquare();
    Zone* zone = square == nullptr ? nullptr : square->getZone();
    return zone == nullptr || (zone->getType() != "Forest" && zone->getType() != "DeepForest");
}

void ZombieGroupManager::update(IsoZombie var1) {
    // NOTE: This implementation assumes all referenced types and methods exist and are ported.
    if (!GameClient::bClient || !var1->isRemoteZombie()) {
        if (!shouldBeInGroup(var1)) {
            if (var1->group != nullptr) {
                var1->group->remove(var1);
            }
        } else if (tickCount == 0.0f) {
            if (var1->group == nullptr) {
                ZombieGroup* group = findNearestGroup(var1->getX(), var1->getY(), var1->getZ());
                if (group == nullptr) {
                    group = freeGroups.empty() ? new ZombieGroup() : freeGroups.back()->reset();
                    if (!freeGroups.empty()) freeGroups.pop_back();
                    group->add(var1);
                    groups.push_back(group);
                    return;
                }
                group->add(var1);
            }
            // Leader logic and pathfinding
            if (var1->getCurrentState() == ZombieIdleState::instance()) {
                if (var1 == var1->group->getLeader()) {
                    float worldAge = GameTime::getInstance().getWorldAgeHours();
                    var1->group->lastSpreadOutTime = std::min(var1->group->lastSpreadOutTime, worldAge);
                    if (!(var1->group->lastSpreadOutTime + 0.083333336f > worldAge)) {
                        var1->group->lastSpreadOutTime = worldAge;
                        int separation = SandboxOptions::instance.zombieConfig.RallyGroupSeparation.getValue();
                        Vector2 tempVec2(0.0f, 0.0f);
                        for (size_t i = 0; i < groups.size(); ++i) {
                            ZombieGroup* otherGroup = groups[i];
                            if (otherGroup->getLeader() != nullptr && otherGroup != var1->group && (int)otherGroup->getLeader()->getZ() == (int)var1->getZ()) {
                                float ox = otherGroup->getLeader()->getX();
                                float oy = otherGroup->getLeader()->getY();
                                float distSq = IsoUtils::DistanceToSquared(var1->x, var1->y, ox, oy);
                                if (!(distSq > separation * separation)) {
                                    tempVec2.x -= ox - var1->x;
                                    tempVec2.y -= oy - var1->y;
                                }
                            }
                        }
                        Vector3 tempVec3;
                        int clearCount = lineClearCollideCount(
                            var1,
                            var1->getCell(),
                            (int)(var1->x + tempVec2.x),
                            (int)(var1->y + tempVec2.y),
                            (int)var1->z,
                            (int)var1->x,
                            (int)var1->y,
                            (int)var1->z,
                            10,
                            tempVec3
                        );
                        if (clearCount >= 1) {
                            if (GameClient::bClient || GameServer::bServer || !(IsoPlayer::getInstance()->getHoursSurvived() < 2.0)) {
                                if (!(tempVec3.x < 0.0f) && !(tempVec3.y < 0.0f) && IsoWorld::instance.MetaGrid.isValidChunk((int)tempVec3.x / 10, (int)tempVec3.y / 10)) {
                                    var1->pathToLocation((int)(tempVec3.x + 0.5f), (int)(tempVec3.y + 0.5f), (int)tempVec3.z);
                                    if (var1->getCurrentState() == PathFindState::instance() || var1->getCurrentState() == WalkTowardState::instance()) {
                                        var1->setLastHeardSound(var1->getPathTargetX(), var1->getPathTargetY(), var1->getPathTargetZ());
                                        var1->AllowRepathDelay = 400.0f;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

ZombieGroup ZombieGroupManager::findNearestGroup(float var1, float var2, float var3) {
    ZombieGroup* nearest = nullptr;
    float minDist = std::numeric_limits<float>::max();
    int travelDist = SandboxOptions::instance.zombieConfig.RallyTravelDistance.getValue();
    for (size_t i = 0; i < groups.size(); ++i) {
        ZombieGroup* group = groups[i];
        if (group->isEmpty()) {
            groups.erase(groups.begin() + i);
            --i;
        } else if ((int)group->getLeader()->getZ() == (int)var3 && group->size() < SandboxOptions::instance.zombieConfig.RallyGroupSize.getValue()) {
            float dist = IsoUtils::DistanceToSquared(var1, var2, group->getLeader()->getX(), group->getLeader()->getY());
            if (dist < travelDist * travelDist && dist < minDist) {
                minDist = dist;
                nearest = group;
            }
        }
    }
    return nearest;
}

int ZombieGroupManager::lineClearCollideCount(IsoMovingObject var1, IsoCell var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, Vector3 var10) {
    int count = 0;
    int dx = var4 - var7;
    int dy = var3 - var6;
    int dz = var5 - var8;
    float fx = 0.5f;
    float fy = 0.5f;
    IsoGridSquare* lastSquare = var2->getGridSquare(var6, var7, var8);
    var10.set(var6, var7, var8);
    if (std::abs(dy) > std::abs(dx) && std::abs(dy) > std::abs(dz)) {
        float stepX = (float)dx / dy;
        float stepZ = (float)dz / dy;
        fx += var6;
        fy += var8;
        dy = dy < 0 ? -1 : 1;
        stepX *= dy;
        stepZ *= dy;
        while (var7 != var4) {
            var7 += dy;
            fx += stepX;
            fy += stepZ;
            IsoGridSquare* square = var2->getGridSquare((int)fx, var7, (int)fy);
            if (square && lastSquare) {
                if (square->testCollideAdjacent(var1, lastSquare->getX() - square->getX(), lastSquare->getY() - square->getY(), lastSquare->getZ() - square->getZ())) {
                    return count;
                }
            }
            lastSquare = square;
            int tx = (int)fx;
            int tz = (int)fy;
            var10.set(tx, var7, tz);
            if (++count >= var9) return count;
        }
    } else if (std::abs(dx) >= std::abs(dy) && std::abs(dx) > std::abs(dz)) {
        float stepY = (float)dy / dx;
        float stepZ = (float)dz / dx;
        fy += var8;
        fx += var7;
        dx = dx < 0 ? -1 : 1;
        stepY *= dx;
        stepZ *= dx;
        while (var6 != var3) {
            var6 += dx;
            fy += stepY;
            fx += stepZ;
            IsoGridSquare* square = var2->getGridSquare(var6, (int)fy, (int)fx);
            if (square && lastSquare) {
                if (square->testCollideAdjacent(var1, lastSquare->getX() - square->getX(), lastSquare->getY() - square->getY(), lastSquare->getZ() - square->getZ())) {
                    return count;
                }
            }
            lastSquare = square;
            int ty = (int)fy;
            int tz = (int)fx;
            var10.set(var6, ty, tz);
            if (++count >= var9) return count;
        }
    } else {
        float stepX = (float)dx / dz;
        float stepY = (float)dy / dz;
        fx += var6;
        fy += var7;
        dz = dz < 0 ? -1 : 1;
        stepX *= dz;
        stepY *= dz;
        while (var8 != var5) {
            var8 += dz;
            fx += stepX;
            fy += stepY;
            IsoGridSquare* square = var2->getGridSquare((int)fx, (int)fy, var8);
            if (square && lastSquare) {
                if (square->testCollideAdjacent(var1, lastSquare->getX() - square->getX(), lastSquare->getY() - square->getY(), lastSquare->getZ() - square->getZ())) {
                    return count;
                }
            }
            lastSquare = square;
            int tx = (int)fx;
            int ty = (int)fy;
            var10.set(tx, ty, var8);
            if (++count >= var9) return count;
        }
    }
    return count;
}

} // namespace ai
} // namespace zombie
