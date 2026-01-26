
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/characters/IsoPlayer.h"
#include <cmath>

namespace zombie {
namespace iso {

void IsoLightSource::update() {
    // Full logic based on Java/C++ base, expanded for completeness
    // Power and electricity checks
    IsoWorld* world = IsoWorld::getInstance();
    if (!bHydroPowered || (world && world->isHydroPowerOn())) {
        if (bActive) {
            // Color/ambient update if attached to a building
            if (localToBuilding) {
                float ambient = core::opengl::RenderSettings::getInstance().getAmbientForPlayer(characters::IsoPlayer::getPlayerIndex()) * 0.7f;
                r = g = b = ambient;
            }
            // Life decrement
            if (life > 0) {
                --life;
            }
            // Color/ambient update with grid square mods if attached to a building and grid square
            IsoGridSquare* sq = world ? world->getCurrentCell()->getGridSquare(x, y, z) : nullptr;
            if (localToBuilding && sq) {
                float ambient = core::opengl::RenderSettings::getInstance().getAmbientForPlayer(characters::IsoPlayer::getPlayerIndex()) * 0.8f;
                r = ambient * IsoGridSquare::rmod * 0.7f;
                g = ambient * IsoGridSquare::gmod * 0.7f;
                b = ambient * IsoGridSquare::bmod * 0.7f;
            }
            // Influence nearby grid squares
            for (int ix = x - radius; ix < x + radius; ++ix) {
                for (int iy = y - radius; iy < y + radius; ++iy) {
                    for (int iz = 0; iz < 8; ++iz) {
                        IsoGridSquare* sq2 = world ? world->getCurrentCell()->getGridSquare(ix, iy, iz) : nullptr;
                        if (sq2 && (!localToBuilding || localToBuilding == sq2->getBuilding())) {
                            // Implement LOS check using LosUtil::lineClear
                            bool lineClear = false;
                            if (sq2->getX() == x && sq2->getY() == y && sq2->getZ() == z) {
                                lineClear = true;
                            } else {
                                // Get the current cell from the world
                                IsoCell* cell = world ? world->getCurrentCell() : nullptr;
                                if (cell) {
                                    auto result = LosUtil::lineClear(
                                        *cell,
                                        x, y, z,
                                        sq2->getX(), sq2->getY(), sq2->getZ(),
                                        false // ignore doors/windows for lighting
                                    );
                                    lineClear = (result != TestResults::Blocked);
                                }
                            }
                            if (lineClear) {
                                float dist = 0.0f;
                                if (std::abs(sq2->getZ() - z) <= 1)
                                    dist = IsoUtils::DistanceTo((float)x, (float)y, 0.0f, (float)sq2->getX(), (float)sq2->getY(), 0.0f);
                                else
                                    dist = IsoUtils::DistanceTo((float)x, (float)y, (float)z, (float)sq2->getX(), (float)sq2->getY(), (float)sq2->getZ());
                                if (!(dist > radius)) {
                                    float factor = 1.0f - (dist / (float)radius);
                                    factor *= factor;
                                    if (life > -1 && startlife > 0) {
                                        factor *= (float)life / (float)startlife;
                                    }
                                    float addR = factor * r * 2.0f;
                                    float addG = factor * g * 2.0f;
                                    float addB = factor * b * 2.0f;
                                    sq2->setLampostTotalR(sq2->getLampostTotalR() + addR);
                                    sq2->setLampostTotalG(sq2->getLampostTotalG() + addG);
                                    sq2->setLampostTotalB(sq2->getLampostTotalB() + addB);
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        bActive = false;
    }
}

void IsoLightSource::clearInfluence() {
    // Remove this light's influence from the world (reverse of update logic)
    IsoWorld* world = IsoWorld::getInstance();
    if (!bHydroPowered || (world && world->isHydroPowerOn())) {
        if (bActive) {
            for (int ix = x - radius; ix < x + radius; ++ix) {
                for (int iy = y - radius; iy < y + radius; ++iy) {
                    for (int iz = 0; iz < 8; ++iz) {
                        IsoGridSquare* sq2 = world ? world->getCurrentCell()->getGridSquare(ix, iy, iz) : nullptr;
                        if (sq2 && (!localToBuilding || localToBuilding == sq2->getBuilding())) {
                            bool lineClear = false;
                            if (sq2->getX() == x && sq2->getY() == y && sq2->getZ() == z) {
                                lineClear = true;
                            } else {
                                IsoCell* cell = world ? world->getCurrentCell() : nullptr;
                                if (cell) {
                                    auto result = LosUtil::lineClear(
                                        *cell,
                                        x, y, z,
                                        sq2->getX(), sq2->getY(), sq2->getZ(),
                                        false
                                    );
                                    lineClear = (result != TestResults::Blocked);
                                }
                            }
                            if (lineClear) {
                                float dist = 0.0f;
                                if (std::abs(sq2->getZ() - z) <= 1)
                                    dist = IsoUtils::DistanceTo((float)x, (float)y, 0.0f, (float)sq2->getX(), (float)sq2->getY(), 0.0f);
                                else
                                    dist = IsoUtils::DistanceTo((float)x, (float)y, (float)z, (float)sq2->getX(), (float)sq2->getY(), (float)sq2->getZ());
                                if (!(dist > radius)) {
                                    float factor = 1.0f - (dist / (float)radius);
                                    factor *= factor;
                                    if (life > -1 && startlife > 0) {
                                        factor *= (float)life / (float)startlife;
                                    }
                                    float subR = factor * r * 2.0f;
                                    float subG = factor * g * 2.0f;
                                    float subB = factor * b * 2.0f;
                                    sq2->setLampostTotalR(sq2->getLampostTotalR() - subR);
                                    sq2->setLampostTotalG(sq2->getLampostTotalG() - subG);
                                    sq2->setLampostTotalB(sq2->getLampostTotalB() - subB);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool IsoLightSource::isInBounds() const {
    // Check if the light is within the current cell's bounds
    const IsoWorld* world = IsoWorld::getInstance();
    const IsoCell* cell = world ? world->getCurrentCell() : nullptr;
    if (!cell) return false;
    int minX = cell->getMinX();
    int maxX = cell->getMaxX();
    int minY = cell->getMinY();
    int maxY = cell->getMaxY();
    int minZ = cell->getMinZ();
    int maxZ = cell->getMaxZ();
    return (x >= minX && x <= maxX &&
            y >= minY && y <= maxY &&
            z >= minZ && z <= maxZ);
}

// All other methods are implemented inline in the header

} // namespace iso
} // namespace zombie
