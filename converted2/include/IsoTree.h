#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoTree.java
namespace zombie {
namespace iso {
namespace objects {
#include <fstream>
#include <iostream>
#include "ByteBuffer.h"
#include "SoundManager.h"
#include "WorldSoundManager.h"
#include "IsoGameCharacter.h"
#include "NulledArrayList.h"
#include "Rand.h"
#include "PropertyContainer.h"
#include "InventoryItem.h"
#include "HandWeapon.h"
#include "iso.h"
#include "IsoFlagType.h"
#include "IsoObjectType.h"
#include "IsoSprite.h"
class IsoTree : public IsoObject {
public:
{
    public IsoTree(IsoCell cell)
    {
        super(cell);
        LogYield = 1;
        damage = 500;
    }
    public void save(ByteBuffer output)
        throws IOException
    {
        super.save(output);
        output.putInt(LogYield);
    }
    public void load(ByteBuffer input)
        throws IOException
    {
        super.load(input);
        LogYield = input.getInt();
    }
    public IsoTree(IsoGridSquare sq, std::string gid)
    {
        super(sq, gid, false);
        LogYield = 1;
        damage = 500;
        sprite.getProperties().Set(IsoFlagType.solid);
        setType(IsoObjectType.tree);
    }
    public IsoTree(IsoGridSquare sq, IsoSprite gid)
    {
        super(sq.getCell(), sq, gid);
        LogYield = 1;
        damage = 500;
        sprite.getProperties().Set(IsoFlagType.solid);
        setType(IsoObjectType.tree);
        LogYield = Integer.parseInt(sprite.getProperties().Val("tree"));
        damage = LogYield * 100;
    }
    public std::string getObjectName()
    {
        return "Tree";
    }
    public void WeaponHit(IsoGameCharacter owner, HandWeapon weapon)
    {
        if(weapon.getDoorHitSound() != nullptr)
            SoundManager.instance.PlayWorldSound(weapon.getDoorHitSound(), square, 0.2F, 20F, 1.0F, true);
        WorldSoundManager.instance.addSound(nullptr, square.getX(), square.getY(), square.getZ(), 20, 20, true, 4F, 15F);
        damage -= weapon.getDoorDamage();
        if(damage <= 0)
        {
            square.getObjects().remove(this);
            square.getProperties().Clear();
            for(int n = 0; n < square.getObjects().size(); n++)
            {
                IsoObject obj = (IsoObject)square.getObjects().get(n);
                if(obj != this)
                    square.getProperties().AddProperties(obj.sprite.getProperties());
            }
            for(int x = square.getX() - 1; x <= square.getX() + 1; x++)
            {
                for(int y = square.getY() - 1; y <= square.getY() + 1; y++)
                {
                    IsoGridSquare sq = getCell().getGridSquare(x, y, square.getZ());
                    if(sq != nullptr)
                    {
                        sq.ReCalculateCollide(square);
                        sq.ReCalculatePathFind(square);
                        sq.ReCalculateVisionBlocked(square);
                        square.ReCalculateCollide(sq);
                        square.ReCalculatePathFind(sq);
                        square.ReCalculateVisionBlocked(sq);
                    }
                }
            }
            int NumPlanks = 1;
            for(int i = 0; i < NumPlanks; i++)
            {
                InventoryItem item = square.AddWorldInventoryItem("Base.Log", Rand.Next(-1F, 1.0F), Rand.Next(-1F, 1.0F), 0.0F);
                item.setUses(LogYield);
            }
        }
    }
    public int LogYield;
    public int damage;
}
} // namespace
