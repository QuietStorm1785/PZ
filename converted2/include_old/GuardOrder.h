#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GuardOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include "Behavior.h"
#include "PathFindBehavior.h"
#include "IsoGameCharacter.h"
#include "IsoSurvivor.h"
#include "IsoGridSquare.h"
#include "Vector2.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            Order
class GuardOrder : public Order {
public:
{
    public GuardOrder(IsoSurvivor chr, IsoGridSquare GuardStand, IsoGridSquare GuardFace)
    {
        super(chr);
        Range = 6;
        StayInRoom = true;
        PathFind = new PathFindBehavior("Guard");
        this.GuardFace = nullptr;
        vec = new Vector2();
        this.GuardFace = GuardFace;
        this.GuardStand = GuardStand;
        PathFind.sx = character.getCurrentSquare().getX();
        PathFind.sy = character.getCurrentSquare().getY();
        PathFind.sz = character.getCurrentSquare().getZ();
        PathFind.tx = GuardStand.getX();
        PathFind.ty = GuardStand.getY();
        PathFind.tz = GuardStand.getZ();
    }
    GuardOrder(IsoGameCharacter chr)
    {
        super(chr);
        Range = 6;
        StayInRoom = true;
        PathFind = new PathFindBehavior("Guard");
        GuardFace = nullptr;
        vec = new Vector2();
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        if(GuardFace == nullptr)
            return zombie.behaviors.Behavior.BehaviorResult.Working;
        if(character.getCurrentSquare() != GuardStand)
        {
            PathFind.tx = GuardStand.getX();
            PathFind.ty = GuardStand.getY();
            PathFind.tz = GuardStand.getZ();
            PathFind.process(nullptr, character);
        } else
        {
            vec.x = (float)GuardFace.getX() + 0.5F;
            vec.y = (float)GuardFace.getY() + 0.5F;
            vec.x -= character.getX();
            vec.y -= character.getY();
            vec.normalize();
            character.DirectionFromVector(vec);
        }
        return zombie.behaviors.Behavior.BehaviorResult.Working;
    }
    public bool complete()
    {
        return false;
    }
    public void update()
    {
    }
    public float getPriority(IsoGameCharacter character)
    {
        return 200F;
    }
    public int Range;
    public bool StayInRoom;
    PathFindBehavior PathFind;
    IsoGridSquare GuardStand;
    IsoGridSquare GuardFace;
    Vector2 vec;
}
} // namespace
