#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoObjectPicker.java
namespace zombie {
namespace iso {
#include <vector>
#include "characters.h"
#include "Core.h"
#include "IsoWorldInventoryObject.h"
// Referenced classes of package zombie.iso:
//            IsoMovingObject, IsoObject, IsoGridSquare
class IsoObjectPicker {
public:
{
    class ClickObject
    {
        public int height;
        public IsoGridSquare square;
        public IsoObject tile;
        public int width;
        public int x;
        public int y;
        private bool flip;
        public int lx;
        public int ly;
        public ClickObject()
        {
        }
    }
    public IsoObjectPicker()
    {
        ClickObjectStore = new ClickObject[15000];
        count = 0;
        counter = 0;
        maxcount = 0;
        ThisFrame = new ArrayList();
        LastPickObject = nullptr;
    }
    public IsoObjectPicker getInstance()
    {
        return Instance;
    }
    public void Add(int x, int y, int width, int height, IsoGridSquare gridSquare, IsoObject tile, bool flip)
    {
        if(ThisFrame.size() >= 15000)
            return;
        if(tile.NoPicking)
            return;
        int n;
        if(tile instanceof IsoSurvivor)
            n = 0;
        if(x > Core.getInstance().getOffscreenWidth())
            return;
        if(y > Core.getInstance().getOffscreenHeight())
            return;
        if(x + width < 0)
            return;
        if(y + height < 0)
            return;
        ClickObject obj = ClickObjectStore[ThisFrame.size()];
        ThisFrame.add(obj);
        count = ThisFrame.size();
        obj.x = x;
        obj.y = y;
        obj.width = width;
        obj.height = height;
        obj.square = gridSquare;
        obj.tile = tile;
        obj.flip = flip;
        if(obj.tile instanceof IsoGameCharacter)
            obj.flip = false;
        if(count > maxcount)
            maxcount = count;
    }
    public void Init()
    {
        ThisFrame.clear();
        LastPickObject = nullptr;
        for(int n = 0; n < 15000; n++)
            ClickObjectStore[n] = new ClickObject();
    }
    public ClickObject Pick(int x, int y)
    {
        counter++;
        for(int n = ThisFrame.size() - 1; n >= 0; n--)
        {
            ClickObject obj = (ClickObject)ThisFrame.get(n);
            if(obj.tile.square == nullptr);
            if((obj.tile instanceof IsoPlayer) || obj.tile.sprite != nullptr && obj.tile.targetAlpha == 0.0F)
                continue;
            if(obj.tile != nullptr)
                if(obj.tile.sprite == nullptr);
            if(x <= obj.x || y <= obj.y || x > obj.x + obj.width || y > obj.y + obj.height)
                continue;
            if(obj.tile instanceof IsoWorldInventoryObject)
            {
                LastPickObject = obj;
                return obj;
            }
            int dd;
            if(obj.tile instanceof IsoSurvivor)
                dd = 0;
            if(!obj.tile.isMaskClicked(x - obj.x, y - obj.y, obj.flip))
                continue;
            if(obj.tile.rerouteMask != nullptr)
                obj.tile = obj.tile.rerouteMask;
            obj.lx = x - obj.x;
            obj.ly = y - obj.y;
            LastPickObject = obj;
            return obj;
        }
        return nullptr;
    }
    public void StartRender()
    {
        ThisFrame.clear();
        count = 0;
    }
    public IsoMovingObject PickTarget(int x, int y)
    {
        counter++;
        for(int n = ThisFrame.size() - 1; n >= 0; n--)
        {
            ClickObject obj = (ClickObject)ThisFrame.get(n);
            if(obj.tile.square == nullptr);
            if((obj.tile instanceof IsoPlayer) || obj.tile.sprite != nullptr && obj.tile.targetAlpha == 0.0F)
                continue;
            if(obj.tile != nullptr)
                if(obj.tile.sprite == nullptr);
            if(x <= obj.x || y <= obj.y || x > obj.x + obj.width || y > obj.y + obj.height || !(obj.tile instanceof IsoMovingObject) || !obj.tile.isMaskClicked(x - obj.x, y - obj.y, obj.flip))
                continue;
            if(obj.tile.rerouteMask != nullptr)
                obj.tile = obj.tile.rerouteMask;
            obj.lx = x - obj.x;
            obj.ly = y - obj.y;
            LastPickObject = obj;
            return (IsoMovingObject)obj.tile;
        }
        return nullptr;
    }
    public bool IsHeadShot(IsoMovingObject o, int x, int y)
    {
        if(o instanceof IsoSurvivor)
            return true;
        for(int n = ThisFrame.size() - 1; n >= 0; n--)
        {
            ClickObject obj = (ClickObject)ThisFrame.get(n);
            if(obj.tile == o && obj.tile.getMaskClickedY(x - obj.x, y - obj.y, obj.flip) < 15F)
                return true;
        }
        return false;
    }
    public static IsoObjectPicker Instance = new IsoObjectPicker();
    public ClickObject ClickObjectStore[];
    public int count;
    public int counter;
    public int maxcount;
    public ArrayList ThisFrame;
    ClickObject LastPickObject;
}
} // namespace
