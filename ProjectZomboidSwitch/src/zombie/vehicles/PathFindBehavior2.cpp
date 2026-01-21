#include <string>
#include <vector>
#include "zombie/vehicles/PathFindBehavior2.h"

namespace zombie {
namespace vehicles {

public PathFindBehavior2::PathFindBehavior2(IsoGameCharacter var1) {
    // TODO: Implement PathFindBehavior2
    return nullptr;
}

bool PathFindBehavior2::isGoalNone() {
    // TODO: Implement isGoalNone
    return false;
}

bool PathFindBehavior2::isGoalCharacter() {
    // TODO: Implement isGoalCharacter
    return false;
}

bool PathFindBehavior2::isGoalLocation() {
    // TODO: Implement isGoalLocation
    return false;
}

bool PathFindBehavior2::isGoalSound() {
    // TODO: Implement isGoalSound
    return false;
}

bool PathFindBehavior2::isGoalVehicleAdjacent() {
    // TODO: Implement isGoalVehicleAdjacent
    return false;
}

bool PathFindBehavior2::isGoalVehicleArea() {
    // TODO: Implement isGoalVehicleArea
    return false;
}

bool PathFindBehavior2::isGoalVehicleSeat() {
    // TODO: Implement isGoalVehicleSeat
    return false;
}

void PathFindBehavior2::reset() {
    // TODO: Implement reset
}

void PathFindBehavior2::pathToCharacter(IsoGameCharacter var1) {
    // TODO: Implement pathToCharacter
}

void PathFindBehavior2::pathToLocation(int var1, int var2, int var3) {
    // TODO: Implement pathToLocation
}

void PathFindBehavior2::pathToLocationF(float var1, float var2, float var3) {
    // TODO: Implement pathToLocationF
}

void PathFindBehavior2::pathToSound(int var1, int var2, int var3) {
    // TODO: Implement pathToSound
}

void PathFindBehavior2::pathToNearest(std::vector<float>& var1) {
    // TODO: Implement pathToNearest
}

void PathFindBehavior2::pathToNearestTable(KahluaTable var1) {
    // TODO: Implement pathToNearestTable
}

void PathFindBehavior2::pathToVehicleAdjacent(BaseVehicle var1) {
    // TODO: Implement pathToVehicleAdjacent
}

void PathFindBehavior2::pathToVehicleArea(BaseVehicle var1, const std::string& var2) {
    // TODO: Implement pathToVehicleArea
}

void PathFindBehavior2::pathToVehicleSeat(BaseVehicle var1, int var2) {
    // TODO: Implement pathToVehicleSeat
}

void PathFindBehavior2::cancel() {
    // TODO: Implement cancel
}

bool PathFindBehavior2::getIsCancelled() {
    // TODO: Implement getIsCancelled
    return false;
}

void PathFindBehavior2::setData(float var1, float var2, float var3) {
    // TODO: Implement setData
}

float PathFindBehavior2::getTargetX() {
    // TODO: Implement getTargetX
    return 0;
}

float PathFindBehavior2::getTargetY() {
    // TODO: Implement getTargetY
    return 0;
}

float PathFindBehavior2::getTargetZ() {
    // TODO: Implement getTargetZ
    return 0;
}

float PathFindBehavior2::getPathLength() {
    // TODO: Implement getPathLength
    return 0;
}

IsoGameCharacter PathFindBehavior2::getTargetChar() {
    // TODO: Implement getTargetChar
    return nullptr;
}

bool PathFindBehavior2::isTargetLocation(float var1, float var2, float var3) {
    // TODO: Implement isTargetLocation
    return false;
}

BehaviorResult PathFindBehavior2::update() {
    // TODO: Implement update
    return nullptr;
}

void PathFindBehavior2::updateWhileRunningPathfind() {
    // TODO: Implement updateWhileRunningPathfind
}

void PathFindBehavior2::moveToPoint(float var1, float var2, float var3) {
    // TODO: Implement moveToPoint
}

void PathFindBehavior2::moveToDir(IsoMovingObject var1, float var2) {
    // TODO: Implement moveToDir
}

bool PathFindBehavior2::checkDoorHoppableWindow(float var1, float var2, float var3) {
    // TODO: Implement checkDoorHoppableWindow
    return false;
}

void PathFindBehavior2::checkCrawlingTransition(PathNode var1, PathNode var2, float var3) {
    // TODO: Implement checkCrawlingTransition
}

bool PathFindBehavior2::shouldGetUpFromCrawl() {
    // TODO: Implement shouldGetUpFromCrawl
    return false;
}

bool PathFindBehavior2::isStrafing() {
    // TODO: Implement isStrafing
    return false;
}

void PathFindBehavior2::closestPointOnPath(float var0, float var1, float var2, IsoMovingObject var3, Path var4, PointOnPath var5) {
    // TODO: Implement closestPointOnPath
}

void PathFindBehavior2::advanceAlongPath(float var1, float var2, float var3, float var4, PointOnPath var5) {
    // TODO: Implement advanceAlongPath
}

void PathFindBehavior2::render() {
    // TODO: Implement render
}

void PathFindBehavior2::Succeeded(Path var1, Mover var2) {
    // TODO: Implement Succeeded
}

void PathFindBehavior2::Failed(Mover var1) {
    // TODO: Implement Failed
}

bool PathFindBehavior2::isMovingUsingPathFind() {
    // TODO: Implement isMovingUsingPathFind
    return false;
}

} // namespace vehicles
} // namespace zombie
