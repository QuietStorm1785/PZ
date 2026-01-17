#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoRoom.java
namespace zombie {
namespace iso {
namespace areas {
#include "Rectangle.h"
#include <algorithm>
#include <vector>
#include "NulledArrayList.h"
#include "Rand.h"
#include "PropertyContainer.h"
#include "ItemContainer.h"
#include "iso.h"
#include "IsoFlagType.h"
#include "IsoSprite.h"
#include "IsoSpriteManager.h"
// Referenced classes of package zombie.iso.areas:
//            IsoBuilding, IsoRoomExit
class IsoRoom {
public:
{
    public IsoRoom()
    {
        Beds = new Vector();
        building = nullptr;
        Containers = new Vector();
        Exits = new Vector();
        RoomDef = "none";
        TileList = new Vector();
        x = 0;
        y = 0;
        width = 0;
        height = 0;
        transparentWalls = 0;
        lit = false;
        lightSwitches = new NulledArrayList();
        WaterSources = new NulledArrayList();
    }
    public IsoBuilding CreateBuilding(IsoCell cell)
    {
        IsoBuilding building = new IsoBuilding(cell);
        AddToBuilding(building);
        return building;
    }
    public void CutWalls()
    {
        for(int n = 0; n < TileList.size(); n++)
        {
            IsoGridSquare sq = (IsoGridSquare)TileList.get(n);
            for(int m = 0; m < sq.getObjects().size(); m++)
            {
                IsoObject obj = (IsoObject)sq.getObjects().get(m);
                if(obj.sprite.getProperties().Is(IsoFlagType.collideW) || obj.sprite.getProperties().Is(IsoFlagType.collideN))
                {
                    IsoSprite _tmp = obj.sprite;
                    obj.sprite = obj.getCell().SpriteManager.getSprite(IsoSprite.spriteID + 576);
                }
            }
        }
    }
    public IsoGridSquare getFreeTile()
    {
        bool bDone = false;
        IsoGridSquare tile = nullptr;
        int nCount = 100;
        do
        {
            if(bDone || nCount <= 0)
                break;
            nCount--;
            bDone = true;
            if(TileList.isEmpty())
                return nullptr;
            tile = (IsoGridSquare)TileList.get(Rand.Next(TileList.size()));
            for(int m = 0; m < Exits.size(); m++)
                if(tile.getX() == ((IsoRoomExit)Exits.get(m)).x && tile.getY() == ((IsoRoomExit)Exits.get(m)).y)
                    bDone = false;
            if(bDone && !tile.isFree(true))
                bDone = false;
        } while(true);
        if(nCount < 0)
            return nullptr;
        else
            return tile;
    }
    public void UnCutWalls()
    {
        for(int n = 0; n < TileList.size(); n++)
        {
            IsoGridSquare sq = (IsoGridSquare)TileList.get(n);
            for(int m = 0; m < sq.getObjects().size(); m++)
            {
                IsoObject obj = (IsoObject)sq.getObjects().get(m);
                if(obj.sprite.getProperties().Is(IsoFlagType.collideW) || obj.sprite.getProperties().Is(IsoFlagType.collideN))
                {
                    IsoSprite _tmp = obj.sprite;
                    obj.sprite = obj.getCell().SpriteManager.getSprite(IsoSprite.spriteID - 576);
                }
            }
        }
    }
    void AddToBuilding(IsoBuilding building)
    {
        this.building = building;
        building.AddRoom(this);
        Iterator i$ = Exits.iterator();
        do
        {
            if(!i$.hasNext())
                break;
            IsoRoomExit exit = (IsoRoomExit)i$.next();
            if(exit.To.From != nullptr && exit.To.From.building == nullptr)
                exit.To.From.AddToBuilding(building);
        } while(true);
    }
    public NulledArrayList getWaterSources()
    {
        return WaterSources;
    }
    public void setWaterSources(NulledArrayList WaterSources)
    {
        this.WaterSources = WaterSources;
    }
    public bool hasWater()
    {
        if(WaterSources.isEmpty())
            return false;
        for(Iterator it = WaterSources.iterator(); it != nullptr && it.hasNext();)
        {
            IsoObject o = (IsoObject)it.next();
            if(o.hasWater())
                return true;
        }
        return false;
    }
    public void useWater()
    {
        if(WaterSources.isEmpty())
            return;
        Iterator it = WaterSources.iterator();
        do
        {
            if(it == nullptr || !it.hasNext())
                break;
            IsoObject o = (IsoObject)it.next();
            if(!o.hasWater())
                continue;
            o.useWater(1);
            break;
        } while(true);
    }
    public Vector Beds;
    public Rectangle bounds;
    public IsoBuilding building;
    public Vector<ItemContainer> Containers;
    public Vector<IsoRoomExit> Exits;
    public int layer;
    public std::string RoomDef;
    public Vector TileList;
    public int x;
    public int y;
    public int width;
    public int height;
    public int transparentWalls;
    public bool lit;
    public NulledArrayList lightSwitches;
    public NulledArrayList WaterSources;
}
} // namespace
