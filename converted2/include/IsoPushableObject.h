#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoPushableObject.java
namespace zombie {
namespace iso {
#include <fstream>
#include <iostream>
#include "ByteBuffer.h"
#include <algorithm>
#include "NulledArrayList.h"
#include "ItemContainer.h"
#include "IsoWheelieBin.h"
#include "IsoSprite.h"
#include "IsoSpriteManager.h"
// Referenced classes of package zombie.iso:
//            IsoMovingObject, IsoCell, IsoGridSquare, IsoWorld
class IsoPushableObject : public IsoMovingObject {
public:
{
    public std::string getObjectName()
    {
        return "Pushable";
    }
    public IsoPushableObject(IsoCell cell)
    {
        super(cell);
        velx = 0.0F;
        vely = 0.0F;
        carryCapacity = 100;
        emptyWeight = 4.5F;
        connectList = nullptr;
        ox = 0.0F;
        oy = 0.0F;
        getCell().getPushableObjectList().add(this);
    }
    public IsoPushableObject(IsoCell cell, int x, int y, int z)
    {
        super(cell, true);
        velx = 0.0F;
        vely = 0.0F;
        carryCapacity = 100;
        emptyWeight = 4.5F;
        connectList = nullptr;
        ox = 0.0F;
        oy = 0.0F;
        getCell().getPushableObjectList().add(this);
    }
    public IsoPushableObject(IsoCell cell, IsoGridSquare square, IsoSprite spr)
    {
        super(cell, square, spr, true);
        velx = 0.0F;
        vely = 0.0F;
        carryCapacity = 100;
        emptyWeight = 4.5F;
        connectList = nullptr;
        ox = 0.0F;
        oy = 0.0F;
        setX((float)square.getX() + 0.5F);
        setY((float)square.getY() + 0.5F);
        setZ(square.getZ());
        ox = getX();
        oy = getY();
        setNx(getX());
        setNy(getNy());
        offsetX = -26F;
        offsetY = -258F;
        setWeight(6F);
        this.square = square;
        setCurrent(square);
        getCurrentSquare().getMovingObjects().add(this);
        Collidable = true;
        solid = true;
        shootable = false;
        width = 0.5F;
        alpha = 0.0F;
        targetAlpha = 0.0F;
        getCell().getPushableObjectList().add(this);
    }
    public void update()
    {
        float a = 0.0F;
        if(connectList != nullptr)
        {
            Iterator it = connectList.iterator();
            do
            {
                if(!it.hasNext())
                    break;
                IsoPushableObject p = (IsoPushableObject)it.next();
                if(p.alpha > a)
                    a = p.alpha;
            } while(true);
            alpha = a;
            targetAlpha = a;
        }
        seperate();
        super.update();
    }
    public void load(ByteBuffer input)
        throws IOException
    {
        super.load(input);
        if(!(this instanceof IsoWheelieBin))
            sprite = IsoWorld.instance.spriteManager.getSprite(input.getInt());
        if(input.get() == 1)
        {
            container = new ItemContainer();
            container.load(input);
        }
    }
    public void save(ByteBuffer output)
        throws IOException
    {
        super.save(output);
        if(!(this instanceof IsoWheelieBin))
            output.putInt(sprite.ID);
        if(container != nullptr)
        {
            output.put((byte)1);
            container.save(output);
        } else
        {
            output.put((byte)0);
        }
    }
    public float getWeight(float x, float y)
    {
        if(container == nullptr)
            return emptyWeight;
        float capacityDelta = (float)container.getWeight() / (float)carryCapacity;
        if(capacityDelta < 0.0F)
            capacityDelta = 0.0F;
        if(capacityDelta > 1.0F)
        {
            return getWeight() * 8F;
        } else
        {
            float weight = getWeight() * capacityDelta + emptyWeight;
            return weight;
        }
    }
    public bool Serialize()
    {
        return true;
    }
    public void DoCollideNorS()
    {
        if(connectList == nullptr)
        {
            super.DoCollideNorS();
            return;
        }
        Iterator it = connectList.iterator();
        do
        {
            if(!it.hasNext())
                break;
            IsoPushableObject p = (IsoPushableObject)it.next();
            if(p != this)
            {
                if(p.ox < ox)
                {
                    p.setNx(getNx() - 1.0F);
                    p.setX(getX() - 1.0F);
                } else
                if(p.ox > ox)
                {
                    p.setNx(getNx() + 1.0F);
                    p.setX(getX() + 1.0F);
                } else
                {
                    p.setNx(getNx());
                    p.setX(getX());
                }
                if(p.oy < oy)
                {
                    p.setNy(getNy() - 1.0F);
                    p.setY(getY() - 1.0F);
                } else
                if(p.oy > oy)
                {
                    p.setNy(getNy() + 1.0F);
                    p.setY(getY() + 1.0F);
                } else
                {
                    p.setNy(getNy());
                    p.setY(getY());
                }
                p.setImpulsex(getImpulsex());
                p.setImpulsey(getImpulsey());
            }
        } while(true);
    }
    public void DoCollideWorE()
    {
        if(connectList == nullptr)
        {
            super.DoCollideWorE();
            return;
        }
        Iterator it = connectList.iterator();
        do
        {
            if(!it.hasNext())
                break;
            IsoPushableObject p = (IsoPushableObject)it.next();
            if(p != this)
            {
                if(p.ox < ox)
                {
                    p.setNx(getNx() - 1.0F);
                    p.setX(getX() - 1.0F);
                } else
                if(p.ox > ox)
                {
                    p.setNx(getNx() + 1.0F);
                    p.setX(getX() + 1.0F);
                } else
                {
                    p.setNx(getNx());
                    p.setX(getX());
                }
                if(p.oy < oy)
                {
                    p.setNy(getNy() - 1.0F);
                    p.setY(getY() - 1.0F);
                } else
                if(p.oy > oy)
                {
                    p.setNy(getNy() + 1.0F);
                    p.setY(getY() + 1.0F);
                } else
                {
                    p.setNy(getNy());
                    p.setY(getY());
                }
                p.setImpulsex(getImpulsex());
                p.setImpulsey(getImpulsey());
            }
        } while(true);
    }
    float velx;
    float vely;
    public int carryCapacity;
    public float emptyWeight;
    public NulledArrayList connectList;
    public float ox;
    public float oy;
}
} // namespace
