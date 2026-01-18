#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoRainSplash.java
namespace zombie {
namespace iso {
namespace objects {
#include "NulledArrayList.h"
#include "Rand.h"
#include "PropertyContainer.h"
#include "ColorInfo.h"
#include "iso.h"
#include "IsoFlagType.h"
// Referenced classes of package zombie.iso.objects:
//            RainManager
class IsoRainSplash : public IsoObject {
public:
{
    public bool Serialize()
    {
        return false;
    }
    public IsoRainSplash(IsoCell cell, IsoGridSquare gridSquare)
    {
        if(gridSquare == nullptr)
            return;
        if(gridSquare.getProperties().Is(IsoFlagType.HasRainSplashes))
            return;
        Age = 0;
        square = gridSquare;
        int NumRainSplashParticles = 1 + Rand.Next(2);
        for(int i = 0; i < NumRainSplashParticles; i++)
            AttachAnim("Rain", "00", 4, RainManager.RainSplashAnimDelay, -16 + (-16 + Rand.Next(32)), (-85 + (-16 + Rand.Next(32))) - 32, true, 0, false, 0.7F, RainManager.RainSplashTintMod);
        gridSquare.getProperties().Set(IsoFlagType.HasRainSplashes, "Has Rain Splashes");
        RainManager.AddRainSplash(this);
    }
    public bool HasTooltip()
    {
        return false;
    }
    public bool TestCollide(IsoMovingObject obj, IsoGridSquare PassedObjectSquare)
    {
        return square == PassedObjectSquare;
    }
    public zombie.iso.IsoObject.VisionResult TestVision(IsoGridSquare from, IsoGridSquare to)
    {
        return zombie.iso.IsoObject.VisionResult.NoEffect;
    }
    public void ChangeTintMod(ColorInfo NewTintMod)
    {
        if(AttachedAnimSprite != nullptr)
        {
            for(int i = 0; i < AttachedAnimSprite.size(); i++);
        }
    }
    public void update()
    {
        Age++;
        if(AttachedAnimSprite != nullptr)
        {
            for(int i = 0; i < AttachedAnimSprite.size(); i++)
            {
                Integer NewX = Integer.valueOf(-16 + (-16 + Rand.Next(32)));
                Integer NewY = Integer.valueOf((-85 + (-16 + Rand.Next(32))) - 32);
            }
        }
    }
    void Reset(IsoGridSquare gridSquare)
    {
        if(gridSquare == nullptr)
            return;
        if(gridSquare.getProperties().Is(IsoFlagType.HasRainSplashes))
            return;
        Age = 0;
        square = gridSquare;
        int NumRainSplashParticles = 1 + Rand.Next(2);
        if(AttachedAnimSprite != nullptr)
        {
            for(int i = 0; i < AttachedAnimSprite.size(); i++);
        }
        gridSquare.getProperties().Set(IsoFlagType.HasRainSplashes, "Has Rain Splashes");
        RainManager.AddRainSplash(this);
    }
    public int Age;
}
} // namespace
