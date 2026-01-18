#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   PlayerUpdateData.java
namespace zombie {
namespace network {
#include "IsoSurvivor.h"
#include "NulledArrayList.h"
#include "iso.h"
class PlayerUpdateData {
public:
{
    public PlayerUpdateData()
    {
        ping = 0;
    }
    void unspool()
    {
        for(int n = 0; n < IsoWorld.instance.CurrentCell.getRemoteSurvivorList().size(); n++)
        {
            IsoSurvivor obj = (IsoSurvivor)IsoWorld.instance.CurrentCell.getRemoteSurvivorList().get(n);
            if(obj.getRemoteID() == ID)
            {
                obj.setX(x);
                obj.setY(y);
                obj.setZ(z);
                obj.dir = IsoDirections.fromIndex(dir);
                obj.SetAnim(animID);
                obj.ping = ping;
            }
        }
    }
    public int ID;
    public float x;
    public float y;
    public float z;
    public int dir;
    public int animID;
    public int animDelay;
    public int ping;
}
} // namespace
