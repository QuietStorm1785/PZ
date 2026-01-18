#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoLightSwitch.java
namespace zombie {
namespace iso {
namespace objects {
#include <fstream>
#include <iostream>
#include "ByteBuffer.h"
#include <vector>
#include "SoundManager.h"
#include "IsoPlayer.h"
#include "iso.h"
#include "IsoSprite.h"
class IsoLightSwitch : public IsoObject {
public:
{
    public std::string getObjectName()
    {
        return "LightSwitch";
    }
    public IsoLightSwitch(IsoCell cell)
    {
        super(cell);
        Activated = false;
        lights = new ArrayList();
        lightRoom = false;
    }
    public IsoLightSwitch(IsoCell cell, IsoGridSquare sq, IsoSprite gid)
    {
        super(cell, sq, gid);
        Activated = false;
        lights = new ArrayList();
        lightRoom = false;
    }
    public void load(ByteBuffer input)
        throws IOException
    {
        super.load(input);
        lightRoom = input.get() == 1;
    }
    public void save(ByteBuffer output)
        throws IOException
    {
        super.save(output);
        output.put(((byte)(lightRoom ? 1 : 0)));
    }
    public bool onMouseLeftClick(int x, int y)
    {
        if(IsoPlayer.getInstance() == nullptr)
            return false;
        if(IsoPlayer.getInstance().getCurrentSquare() == nullptr)
            return false;
        float DistRatioFromSource = 0.0F;
        int Dist = Math.abs(square.getX() - IsoPlayer.getInstance().getCurrentSquare().getX()) + Math.abs((square.getY() - IsoPlayer.getInstance().getCurrentSquare().getY()) + Math.abs(square.getZ() - IsoPlayer.getInstance().getCurrentSquare().getZ()));
        if(Dist < 4 && square.getRoom() != nullptr)
        {
            SoundManager.instance.PlayWorldSoundWav("lightswitch", square, 0.0F, 10F, 1.0F, true);
            for(int n = 0; n < lights.size(); n++)
            {
                IsoLightSource s = (IsoLightSource)lights.get(n);
                s.bActive = !s.bActive;
                s.update();
            }
            return true;
        } else
        {
            return false;
        }
    }
    public void update()
    {
    }
    bool Activated;
    public ArrayList lights;
    public bool lightRoom;
}
} // namespace
