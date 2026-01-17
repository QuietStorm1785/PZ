#pragma once
#include <string>
#include <glm/glm.hpp>

namespace zombie { namespace characters { class IsoPlayer; } }

class IsoGridSquare;

/**
 * IsoObject - Base class for all objects in the world (trees, furniture, etc.)
 */
class IsoObject {
public:
    IsoObject();
    virtual ~IsoObject();

    // Position
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    void setX(float nx) { x = nx; }
    void setY(float ny) { y = ny; }
    void setZ(float nz) { z = nz; }

    // Square reference
    IsoGridSquare* getSquare() const { return square; }
    void setSquare(IsoGridSquare* sq) { square = sq; }

    // Rendering
    virtual void render();

    // Interaction hook (override in subclasses)
    virtual void onInteract(class zombie::characters::IsoPlayer* player);

    // Properties
    bool isSolid() const { return solid; }
    void setSolid(bool s) { solid = s; }

    const std::string& getType() const { return type; }
    void setType(const std::string& t) { type = t; }

    // Update
    virtual void update();

protected:
    float x, y, z;
    IsoGridSquare* square;
    bool solid;
    std::string type;  // Object type for audio/interaction
};
