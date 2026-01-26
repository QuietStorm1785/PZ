#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/objects/IsoLightSwitch.h"

namespace zombie {
namespace iso {


class IsoLightSource {
public:
    static int NextID;
    int ID;
    int x, y, z;
    float r, g, b;
    float rJNI, gJNI, bJNI;
    int radius;
    bool bActive, bWasActive, bActiveJNI;
    int life, startlife;
    zombie::iso::areas::IsoBuilding* localToBuilding;
    bool bHydroPowered;
    std::vector<zombie::iso::objects::IsoLightSwitch*> switches;
    zombie::iso::IsoChunk* chunk;
    void* lightMap;

    IsoLightSource(int x_, int y_, int z_, float r_, float g_, float b_, int radius_)
        : ID(NextID++), x(x_), y(y_), z(z_), r(r_), g(g_), b(b_), rJNI(0), gJNI(0), bJNI(0),
          radius(radius_), bActive(true), bWasActive(false), bActiveJNI(false),
          life(-1), startlife(-1), localToBuilding(nullptr), bHydroPowered(false), chunk(nullptr), lightMap(nullptr) {}

    IsoLightSource(int x_, int y_, int z_, float r_, float g_, float b_, int radius_, zombie::iso::areas::IsoBuilding* building)
        : ID(NextID++), x(x_), y(y_), z(z_), r(r_), g(g_), b(b_), rJNI(0), gJNI(0), bJNI(0),
          radius(radius_), bActive(true), bWasActive(false), bActiveJNI(false),
          life(-1), startlife(-1), localToBuilding(building), bHydroPowered(false), chunk(nullptr), lightMap(nullptr) {}

    IsoLightSource(int x_, int y_, int z_, float r_, float g_, float b_, int radius_, int life_)
        : ID(NextID++), x(x_), y(y_), z(z_), r(r_), g(g_), b(b_), rJNI(0), gJNI(0), bJNI(0),
          radius(radius_), bActive(true), bWasActive(false), bActiveJNI(false),
          life(life_), startlife(life_), localToBuilding(nullptr), bHydroPowered(false), chunk(nullptr), lightMap(nullptr) {}

    void update();
    int getX() const { return x; }
    void setX(int v) { x = v; }
    int getY() const { return y; }
    void setY(int v) { y = v; }
    int getZ() const { return z; }
    void setZ(int v) { z = v; }
    float getR() const { return r; }
    void setR(float v) { r = v; }
    float getG() const { return g; }
    void setG(float v) { g = v; }
    float getB() const { return b; }
    void setB(float v) { b = v; }
    int getRadius() const { return radius; }
    void setRadius(int v) { radius = v; }
    bool isActive() const { return bActive; }
    void setActive(bool v) { bActive = v; }
    bool wasActive() const { return bWasActive; }
    void setWasActive(bool v) { bWasActive = v; }
    std::vector<zombie::iso::objects::IsoLightSwitch*>& getSwitches() { return switches; }
    void setSwitches(const std::vector<zombie::iso::objects::IsoLightSwitch*>& v) { switches = v; }
    void clearInfluence();
    bool isInBounds(int x0, int y0, int x1, int y1) const { return x >= x0 && x < x1 && y >= y0 && y < y1; }
    bool isInBounds() const; // Implementation in .cpp
    bool isHydroPowered() const { return bHydroPowered; }
    zombie::iso::areas::IsoBuilding* getLocalToBuilding() const { return localToBuilding; }
};

// Initialize static member
inline int IsoLightSource::NextID = 1;
} // namespace iso
} // namespace zombie
