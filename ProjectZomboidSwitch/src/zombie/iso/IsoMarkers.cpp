// --- IsoMarker methods ---
// (Assumes IsoMarker is now a nested class in IsoMarkers.h)
namespace zombie { namespace iso {

int IsoMarkers::IsoMarker::getID() const { return ID; }
void IsoMarkers::IsoMarker::remove() { removed = true; }
bool IsoMarkers::IsoMarker::isRemoved() const { return removed; }
void IsoMarkers::IsoMarker::init(LuaTable* t1, LuaTable* t2, int px, int py, int pz, std::shared_ptr<IsoGridSquare> sq) { square = sq; setPos(px, py, pz); /* TODO: Fill textures/overlayTextures from LuaTable */ }
void IsoMarkers::IsoMarker::init(LuaTable* t1, LuaTable* t2, int px, int py, int pz, std::shared_ptr<IsoGridSquare> sq, bool temp) { square = sq; setPos(px, py, pz); /* TODO: Fill tempObjects from LuaTable if temp */ }
void IsoMarkers::IsoMarker::init(const std::string& name, int px, int py, int pz, std::shared_ptr<IsoGridSquare> sq, bool temp) { square = sq; setPos(px, py, pz); /* TODO: Fill tempObjects if temp */ }
bool IsoMarkers::IsoMarker::hasTempSquareObject() const { return !tempObjects.empty(); }
void IsoMarkers::IsoMarker::addTempSquareObject(std::shared_ptr<IsoObject> obj) { /* TODO: Add to square->localTemporaryObjects */ }
void IsoMarkers::IsoMarker::removeTempSquareObjects() { /* TODO: Remove from square->localTemporaryObjects */ }
float IsoMarkers::IsoMarker::getX() const { return x; }
float IsoMarkers::IsoMarker::getY() const { return y; }
float IsoMarkers::IsoMarker::getZ() const { return z; }
float IsoMarkers::IsoMarker::getR() const { return r; }
float IsoMarkers::IsoMarker::getG() const { return g; }
float IsoMarkers::IsoMarker::getB() const { return b; }
float IsoMarkers::IsoMarker::getA() const { return a; }
void IsoMarkers::IsoMarker::setR(float v) { r = v; }
void IsoMarkers::IsoMarker::setG(float v) { g = v; }
void IsoMarkers::IsoMarker::setB(float v) { b = v; }
void IsoMarkers::IsoMarker::setA(float v) { a = v; }
float IsoMarkers::IsoMarker::getAlpha() const { return alpha; }
void IsoMarkers::IsoMarker::setAlpha(float v) { alpha = v; }
float IsoMarkers::IsoMarker::getAlphaMax() const { return alphaMax; }
void IsoMarkers::IsoMarker::setAlphaMax(float v) { alphaMax = v; }
float IsoMarkers::IsoMarker::getAlphaMin() const { return alphaMin; }
void IsoMarkers::IsoMarker::setAlphaMin(float v) { alphaMin = v; }
bool IsoMarkers::IsoMarker::isDoAlpha() const { return doAlpha; }
void IsoMarkers::IsoMarker::setDoAlpha(bool v) { doAlpha = v; }
float IsoMarkers::IsoMarker::getFadeSpeed() const { return fadeSpeed; }
void IsoMarkers::IsoMarker::setFadeSpeed(float v) { fadeSpeed = v; }
std::shared_ptr<IsoGridSquare> IsoMarkers::IsoMarker::getSquare() const { return square; }
void IsoMarkers::IsoMarker::setSquare(std::shared_ptr<IsoGridSquare> sq) { square = sq; }
void IsoMarkers::IsoMarker::setPos(int px, int py, int pz) { x = px + 0.5f; y = py + 0.5f; z = pz; }
bool IsoMarkers::IsoMarker::isActive() const { return active; }
void IsoMarkers::IsoMarker::setActive(bool v) { active = v; }

// --- CircleIsoMarker methods ---
int IsoMarkers::CircleIsoMarker::getID() const { return ID; }
void IsoMarkers::CircleIsoMarker::remove() { removed = true; }
bool IsoMarkers::CircleIsoMarker::isRemoved() const { return removed; }
void IsoMarkers::CircleIsoMarker::init(int px, int py, int pz, std::shared_ptr<IsoGridSquare> sq) { square = sq; setPos(px, py, pz); }
float IsoMarkers::CircleIsoMarker::getX() const { return x; }
float IsoMarkers::CircleIsoMarker::getY() const { return y; }
float IsoMarkers::CircleIsoMarker::getZ() const { return z; }
float IsoMarkers::CircleIsoMarker::getR() const { return r; }
float IsoMarkers::CircleIsoMarker::getG() const { return g; }
float IsoMarkers::CircleIsoMarker::getB() const { return b; }
float IsoMarkers::CircleIsoMarker::getA() const { return a; }
void IsoMarkers::CircleIsoMarker::setR(float v) { r = v; }
void IsoMarkers::CircleIsoMarker::setG(float v) { g = v; }
void IsoMarkers::CircleIsoMarker::setB(float v) { b = v; }
void IsoMarkers::CircleIsoMarker::setA(float v) { a = v; }
float IsoMarkers::CircleIsoMarker::getSize() const { return size; }
void IsoMarkers::CircleIsoMarker::setSize(float v) { size = v; }
float IsoMarkers::CircleIsoMarker::getAlpha() const { return alpha; }
void IsoMarkers::CircleIsoMarker::setAlpha(float v) { alpha = v; }
float IsoMarkers::CircleIsoMarker::getAlphaMax() const { return alphaMax; }
void IsoMarkers::CircleIsoMarker::setAlphaMax(float v) { alphaMax = v; }
float IsoMarkers::CircleIsoMarker::getAlphaMin() const { return alphaMin; }
void IsoMarkers::CircleIsoMarker::setAlphaMin(float v) { alphaMin = v; }
bool IsoMarkers::CircleIsoMarker::isDoAlpha() const { return doAlpha; }
void IsoMarkers::CircleIsoMarker::setDoAlpha(bool v) { doAlpha = v; }
float IsoMarkers::CircleIsoMarker::getFadeSpeed() const { return fadeSpeed; }
void IsoMarkers::CircleIsoMarker::setFadeSpeed(float v) { fadeSpeed = v; }
std::shared_ptr<IsoGridSquare> IsoMarkers::CircleIsoMarker::getSquare() const { return square; }
void IsoMarkers::CircleIsoMarker::setSquare(std::shared_ptr<IsoGridSquare> sq) { square = sq; }
void IsoMarkers::CircleIsoMarker::setPos(int px, int py, int pz) { x = px; y = py; z = pz; }
bool IsoMarkers::CircleIsoMarker::isActive() const { return active; }
void IsoMarkers::CircleIsoMarker::setActive(bool v) { active = v; }

} // namespace iso } // namespace zombie

#include <string>
#include "zombie/iso/IsoMarkers.h"

namespace zombie {
namespace iso {

IsoMarkers::IsoMarkers() {}

void IsoMarkers::init() {}

void IsoMarkers::reset() {
    markers.clear();
    circlemarkers.clear();
}

void IsoMarkers::update() {
    if (!GameServer::bServer) {
        updateIsoMarkers();
        updateCircleIsoMarkers();
    }
}

void IsoMarkers::updateIsoMarkers() {
    if (IsoCamera::frameState.playerIndex == 0) {
        if (!markers.empty()) {
            for (int i = static_cast<int>(markers.size()) - 1; i >= 0; --i) {
                if (markers[i]->isRemoved()) {
                    if (markers[i]->hasTempSquareObject()) {
                        markers[i]->removeTempSquareObjects();
                    }
                    markers.erase(markers.begin() + i);
                }
            }
            for (auto& marker : markers) {
                if (marker->alphaInc) {
                    marker->alpha += GameTime::getInstance()->getMultiplier() * marker->fadeSpeed;
                    if (marker->alpha > marker->alphaMax) {
                        marker->alphaInc = false;
                        marker->alpha = marker->alphaMax;
                    }
                } else {
                    marker->alpha -= GameTime::getInstance()->getMultiplier() * marker->fadeSpeed;
                    if (marker->alpha < marker->alphaMin) {
                        marker->alphaInc = true;
                        marker->alpha = 0.3f;
                    }
                }
            }
        }
    }
}

bool IsoMarkers::removeIsoMarker(std::shared_ptr<IsoMarker> marker) {
    return removeIsoMarker(marker->getID());
}

bool IsoMarkers::removeIsoMarker(int id) {
    for (int i = static_cast<int>(markers.size()) - 1; i >= 0; --i) {
        if (markers[i]->getID() == id) {
            markers[i]->remove();
            markers.erase(markers.begin() + i);
            return true;
        }
    }
    return false;
}

std::shared_ptr<IsoMarker> IsoMarkers::getIsoMarker(int id) {
    for (auto& marker : markers) {
        if (marker->getID() == id) return marker;
    }
    return nullptr;
}

std::shared_ptr<IsoMarker> IsoMarkers::addIsoMarker(const std::string& name, std::shared_ptr<IsoGridSquare> sq, float r, float g, float b, bool doAlpha, bool temp) {
    if (GameServer::bServer) return nullptr;
    auto marker = std::make_shared<IsoMarker>();
    marker->setSquare(sq);
    marker->init(name, sq->x, sq->y, sq->z, sq, temp);
    marker->setR(r);
    marker->setG(g);
    marker->setB(b);
    marker->setA(1.0f);
    marker->setDoAlpha(doAlpha);
    marker->setFadeSpeed(0.006f);
    marker->setAlpha(1.0f);
    marker->setAlphaMin(0.3f);
    marker->setAlphaMax(1.0f);
    markers.push_back(marker);
    return marker;
}

std::shared_ptr<IsoMarker> IsoMarkers::addIsoMarker(/*LuaTable*/void* t1, /*LuaTable*/void* t2, std::shared_ptr<IsoGridSquare> sq, float r, float g, float b, bool doAlpha, bool temp) {
    // LuaTable types are placeholders; replace with your LuaTable wrapper if needed
    return addIsoMarker(t1, t2, sq, r, g, b, doAlpha, temp, 0.006f, 0.3f, 1.0f);
}

std::shared_ptr<IsoMarker> IsoMarkers::addIsoMarker(/*LuaTable*/void* t1, /*LuaTable*/void* t2, std::shared_ptr<IsoGridSquare> sq, float r, float g, float b, bool doAlpha, bool temp, float fadeSpeed, float alphaMin, float alphaMax) {
    if (GameServer::bServer) return nullptr;
    auto marker = std::make_shared<IsoMarker>();
    marker->init(t1, t2, sq->x, sq->y, sq->z, sq, temp);
    marker->setSquare(sq);
    marker->setR(r);
    marker->setG(g);
    marker->setB(b);
    marker->setA(1.0f);
    marker->setDoAlpha(doAlpha);
    marker->setFadeSpeed(fadeSpeed);
    marker->setAlpha(0.0f);
    marker->setAlphaMin(alphaMin);
    marker->setAlphaMax(alphaMax);
    markers.push_back(marker);
    return marker;
}

void IsoMarkers::renderIsoMarkers(std::shared_ptr<PerPlayerRender> render, int z, int playerIdx) {
    if (!GameServer::bServer && !markers.empty()) {
        auto player = IsoPlayer::players[playerIdx];
        if (player) {
            for (auto& marker : markers) {
                if (marker->z == z && marker->z == player->getZ() && marker->active) {
                    for (auto& tex : marker->textures) {
                        float sx = IsoUtils::XToScreen(marker->x, marker->y, marker->z, 0) - IsoCamera::cameras[playerIdx]->getOffX() - tex->getWidth() / 2.0f;
                        float sy = IsoUtils::YToScreen(marker->x, marker->y, marker->z, 0) - IsoCamera::cameras[playerIdx]->getOffY() - tex->getHeight();
                        SpriteRenderer::instance->render(tex, sx, sy, tex->getWidth(), tex->getHeight(), marker->r, marker->g, marker->b, marker->alpha, nullptr);
                    }
                }
            }
        }
    }
}

void IsoMarkers::renderIsoMarkersDeferred(std::shared_ptr<PerPlayerRender> render, int z, int playerIdx) {
    if (!GameServer::bServer && !markers.empty()) {
        auto player = IsoPlayer::players[playerIdx];
        if (player) {
            for (auto& marker : markers) {
                if (marker->z == z && marker->z == player->getZ() && marker->active) {
                    for (auto& tex : marker->overlayTextures) {
                        float sx = IsoUtils::XToScreen(marker->x, marker->y, marker->z, 0) - IsoCamera::cameras[playerIdx]->getOffX() - tex->getWidth() / 2.0f;
                        float sy = IsoUtils::YToScreen(marker->x, marker->y, marker->z, 0) - IsoCamera::cameras[playerIdx]->getOffY() - tex->getHeight();
                        SpriteRenderer::instance->render(tex, sx, sy, tex->getWidth(), tex->getHeight(), marker->r, marker->g, marker->b, marker->alpha, nullptr);
                    }
                }
            }
        }
    }
}

// Add updateCircleIsoMarkers and renderIsoMarkersOnSquare as needed for completeness

} // namespace iso
} // namespace zombie


namespace zombie {
namespace iso {

void IsoMarkers::renderIsoMarkersOnSquare(std::shared_ptr<PerPlayerRender> render, int z, int playerIdx) {
    if (!GameServer::bServer && !markers.empty()) {
        auto player = IsoPlayer::players[playerIdx];
        if (player) {
            for (auto& marker : markers) {
                if (marker->z == z && marker->z == player->getZ() && marker->active) {
                    for (auto& tex : marker->overlayTextures) {
                        float sx = IsoUtils::XToScreen(marker->x, marker->y, marker->z, 0) - IsoCamera::cameras[playerIdx]->getOffX() - tex->getWidth() / 2.0f;
                        float sy = IsoUtils::YToScreen(marker->x, marker->y, marker->z, 0) - IsoCamera::cameras[playerIdx]->getOffY() - tex->getHeight();
                        SpriteRenderer::instance->render(tex, sx, sy, tex->getWidth(), tex->getHeight(), marker->r, marker->g, marker->b, marker->alpha, nullptr);
                    }
                }
            }
        }
    }
}

void IsoMarkers::updateCircleIsoMarkers() {
    if (IsoCamera::frameState.playerIndex == 0) {
        if (!circlemarkers.empty()) {
            for (int i = static_cast<int>(circlemarkers.size()) - 1; i >= 0; --i) {
                if (circlemarkers[i]->isRemoved()) {
                    circlemarkers.erase(circlemarkers.begin() + i);
                }
            }
            for (auto& marker : circlemarkers) {
                if (marker->alphaInc) {
                    marker->alpha += GameTime::getInstance()->getMultiplier() * marker->fadeSpeed;
                    if (marker->alpha > marker->alphaMax) {
                        marker->alphaInc = false;
                        marker->alpha = marker->alphaMax;
                    }
                } else {
                    marker->alpha -= GameTime::getInstance()->getMultiplier() * marker->fadeSpeed;
                    if (marker->alpha < marker->alphaMin) {
                        marker->alphaInc = true;
                        marker->alpha = 0.3f;
                    }
                }
            }
        }
    }
}

bool IsoMarkers::removeCircleIsoMarker(std::shared_ptr<CircleIsoMarker> marker) {
    for (int i = static_cast<int>(circlemarkers.size()) - 1; i >= 0; --i) {
        if (circlemarkers[i] == marker) {
            circlemarkers.erase(circlemarkers.begin() + i);
            return true;
        }
    }
    return false;
}

bool IsoMarkers::removeCircleIsoMarker(int id) {
    for (int i = static_cast<int>(circlemarkers.size()) - 1; i >= 0; --i) {
        if (circlemarkers[i]->getID() == id) {
            circlemarkers.erase(circlemarkers.begin() + i);
            return true;
        }
    }
    return false;
}

std::shared_ptr<CircleIsoMarker> IsoMarkers::getCircleIsoMarker(int id) {
    for (auto& marker : circlemarkers) {
        if (marker->getID() == id) return marker;
    }
    return nullptr;
}

std::shared_ptr<CircleIsoMarker> IsoMarkers::addCircleIsoMarker(std::shared_ptr<IsoGridSquare> sq, float r, float g, float b, float a) {
    if (GameServer::bServer) return nullptr;
    auto marker = std::make_shared<CircleIsoMarker>();
    marker->setSquare(sq);
    marker->setR(r);
    marker->setG(g);
    marker->setB(b);
    marker->setA(a);
    marker->setFadeSpeed(0.006f);
    marker->setAlpha(1.0f);
    marker->setAlphaMin(0.3f);
    marker->setAlphaMax(1.0f);
    circlemarkers.push_back(marker);
    return marker;
}

void IsoMarkers::renderCircleIsoMarkers(std::shared_ptr<PerPlayerRender> render, int z, int playerIdx) {
    if (!GameServer::bServer && !circlemarkers.empty()) {
        auto player = IsoPlayer::players[playerIdx];
        if (player) {
            for (auto& marker : circlemarkers) {
                if (marker->z == z && marker->z == player->getZ() && marker->active) {
                    for (auto& tex : marker->textures) {
                        float sx = IsoUtils::XToScreen(marker->x, marker->y, marker->z, 0) - IsoCamera::cameras[playerIdx]->getOffX() - tex->getWidth() / 2.0f;
                        float sy = IsoUtils::YToScreen(marker->x, marker->y, marker->z, 0) - IsoCamera::cameras[playerIdx]->getOffY() - tex->getHeight();
                        SpriteRenderer::instance->render(tex, sx, sy, tex->getWidth(), tex->getHeight(), marker->r, marker->g, marker->b, marker->alpha, nullptr);
                    }
                }
            }
        }
    }
}

void IsoMarkers::render() {
    if (GameServer::bServer) return;
    int numPlayers = static_cast<int>(IsoPlayer::players.size());
    for (int playerIdx = 0; playerIdx < numPlayers; ++playerIdx) {
        auto player = IsoPlayer::players[playerIdx];
        if (!player) continue;
        int z = player->getZ();
        auto render = IsoCamera::cameras[playerIdx];
        // Render standard markers
        renderIsoMarkers(render, z, playerIdx);
        // Render deferred/overlay markers
        renderIsoMarkersDeferred(render, z, playerIdx);
        // Render markers on square (if needed)
        renderIsoMarkersOnSquare(render, z, playerIdx);
        // Render circle markers
        renderCircleIsoMarkers(render, z, playerIdx);
    }
}

} // namespace iso
} // namespace zombie

