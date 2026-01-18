#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoMolotovCocktail.java
namespace zombie {
namespace iso {
namespace objects {
#include "SoundManager.h"
#include "NulledArrayList.h"
#include "Rand.h"
#include "iso.h"
#include "IsoSprite.h"
// Referenced classes of package zombie.iso.objects:
//            IsoFireManager
class IsoMolotovCocktail : public IsoPhysicsObject {
public:
{
    public std::string getObjectName()
    {
        return "MolotovCocktail";
    }
    public IsoMolotovCocktail(IsoCell cell)
    {
        super(cell);
    }
    public IsoMolotovCocktail(IsoCell cell, float x, float y, float z, float xvel, float yvel)
    {
        super(cell);
        velX = xvel;
        velY = yvel;
        float randX = (float)Rand.Next(4000) / 10000F;
        float randY = (float)Rand.Next(4000) / 10000F;
        randX -= 0.2F;
        randY -= 0.2F;
        velX += randX;
        velY += randY;
        this.x = x;
        this.y = y;
        this.z = z;
        nx = x;
        ny = y;
        offsetX = -26F;
        offsetY = -242F;
        sprite.LoadFramesNoDir("inventory/world/WItem_Molotov", "00", 1);
        speedMod = 0.2F;
    }
    public void collideCharacter()
    {
        Explode();
    }
    public void collideGround()
    {
        Explode();
    }
    public void collideWall()
    {
        Explode();
    }
    public void update()
    {
        super.update();
        if(isCollidedThisFrame())
            Explode();
    }
    void Explode()
    {
        setDestroyed(true);
        IsoFireManager.MolotovSmash(getCell(), getCurrentSquare());
        getCurrentSquare().getMovingObjects().remove(this);
        getCell().Remove(this);
        SoundManager.instance.PlayWorldSound("bottlesmash", getCurrentSquare(), 0.5F, 10F, 0.3F, false);
    }
}
} // namespace
