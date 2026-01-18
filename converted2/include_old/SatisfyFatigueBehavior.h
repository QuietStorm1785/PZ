#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   SatisfyFatigueBehavior.java
namespace zombie {
namespace behaviors {
namespace survivor {
#include <algorithm>
#include <vector>
#include "Behavior.h"
#include "DecisionPath.h"
#include "PathFindBehavior.h"
#include "IsoGameCharacter.h"
#include "NulledArrayList.h"
#include "IsoGridSquare.h"
#include "IsoBuilding.h"
#include "IsoRoom.h"
class SatisfyFatigueBehavior : public Behavior {
public:
{
    public SatisfyFatigueBehavior()
    {
        pathFind = new PathFindBehavior("Fatigue");
    }
    public zombie.behaviors.Behavior.BehaviorResult process(DecisionPath path, IsoGameCharacter character)
    {
        IsoGridSquare bed = nullptr;
        zombie.behaviors.Behavior.BehaviorResult res = zombie.behaviors.Behavior.BehaviorResult.Failed;
        if(character.getCurrentSquare().getRoom() != nullptr)
        {
            if(character.getCurrentSquare().getRoom().Beds.size() > 0)
            {
                bed = (IsoGridSquare)character.getCurrentSquare().getRoom().Beds.get(0);
                if(bed.getMovingObjects().size() > 0 && bed.getMovingObjects().get(0) != character)
                    bed = nullptr;
            } else
            {
                Iterator i$ = character.getCurrentSquare().getRoom().building.Rooms.iterator();
                do
                {
                    if(!i$.hasNext())
                        break;
                    IsoRoom room = (IsoRoom)i$.next();
                    if(room.Beds.size() > 0)
                    {
                        bed = (IsoGridSquare)room.Beds.get(0);
                        if(bed.getMovingObjects().size() > 0 && bed.getMovingObjects().get(0) != character)
                            bed = nullptr;
                    }
                } while(bed == nullptr);
            }
            if(bed != nullptr)
            {
                if(!pathFind.running(character))
                {
                    pathFind.sx = (int)character.getX();
                    pathFind.sy = (int)character.getY();
                    pathFind.sz = (int)character.getZ();
                }
                pathFind.tx = bed.getX();
                pathFind.ty = bed.getY();
                pathFind.tz = bed.getZ();
                res = pathFind.process(path, character);
                if(res == zombie.behaviors.Behavior.BehaviorResult.Succeeded)
                    character.setAsleep(true);
            }
        }
        return res;
    }
    public void reset()
    {
    }
    public bool valid()
    {
        return true;
    }
    PathFindBehavior pathFind;
}
} // namespace
