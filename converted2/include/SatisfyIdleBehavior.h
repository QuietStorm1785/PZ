#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   SatisfyIdleBehavior.java
namespace zombie {
namespace behaviors {
namespace survivor {
#include "Behavior.h"
#include "DecisionPath.h"
#include "PathFindBehavior.h"
#include "characters.h"
#include "Rand.h"
#include "PropertyContainer.h"
#include "IsoGridSquare.h"
#include "IsoUtils.h"
#include "IsoFlagType.h"
#include "Vector2.h"
#include "IsoBuilding.h"
#include "IsoRoom.h"
#include "TextManager.h"
#include "UIFont.h"
// Referenced classes of package zombie.behaviors.survivor:
//            TravelLocationFinder
class SatisfyIdleBehavior : public Behavior {
public:
{
    public SatisfyIdleBehavior()
    {
        Started = false;
        OtherRoom = false;
        pathFind = new PathFindBehavior("Idle");
        sq = nullptr;
        timeout = 0;
    }
    public zombie.behaviors.Behavior.BehaviorResult process(DecisionPath path, IsoGameCharacter character)
    {
        zombie.behaviors.Behavior.BehaviorResult res = zombie.behaviors.Behavior.BehaviorResult.Failed;
        this.timeout--;
        if(!Started && this.timeout <= 0)
        {
            this.timeout = 150 + Rand.Next(40);
            Started = true;
            OtherRoom = false;
            if(character.getCurrentSquare().getRoom() != nullptr)
            {
                if(Rand.Next(2) == 0)
                    OtherRoom = true;
                IsoRoom room = character.getCurrentSquare().getRoom();
                if(OtherRoom)
                    room = character.getCurrentSquare().getRoom().building.getRandomRoom();
                bool bDone = false;
                sq = room.getFreeTile();
                bDone = true;
                if(sq == nullptr)
                {
                    this.timeout = 600;
                    reset();
                }
                if(sq != nullptr && !pathFind.running(character))
                {
                    pathFind.sx = (int)character.getX();
                    pathFind.sy = (int)character.getY();
                    pathFind.sz = (int)character.getZ();
                    pathFind.tx = sq.getX();
                    pathFind.ty = sq.getY();
                    pathFind.tz = sq.getZ();
                }
            } else
            {
                bool bDone = false;
                int timeout = 100;
                do
                {
                    if(bDone || timeout <= 0)
                        break;
                    timeout--;
                    sq = TravelLocationFinder.FindLocation(character.getDescriptor(), character.getX() - 5F, character.getY() - 5F, character.getX() + 5F, character.getY() + 5F, 10);
                    if(sq != nullptr && !sq.getProperties().Is(IsoFlagType.solidtrans) && !sq.getProperties().Is(IsoFlagType.solid))
                        bDone = true;
                    if(sq != nullptr && !InDistanceOfPlayer(character, sq.getX(), sq.getY()))
                        bDone = false;
                } while(true);
                if(sq != nullptr && !pathFind.running(character))
                {
                    pathFind.sx = (int)character.getX();
                    pathFind.sy = (int)character.getY();
                    pathFind.sz = (int)character.getZ();
                    pathFind.tx = sq.getX();
                    pathFind.ty = sq.getY();
                    pathFind.tz = sq.getZ();
                }
            }
        }
        if(!Started && Rand.Next(200) == 0)
        {
            Vector2 vec = new Vector2(character.getAngle().x, character.getAngle().y);
            vec.x += (float)Rand.Next(-500, 500) / 2000F;
            vec.y += (float)Rand.Next(-500, 500) / 2000F;
            vec.normalize();
            character.DirectionFromVector(vec);
        }
        if(sq != nullptr)
        {
            res = pathFind.process(path, character);
            if(res == zombie.behaviors.Behavior.BehaviorResult.Failed)
            {
                this.timeout = 600;
                reset();
            }
            if(res == zombie.behaviors.Behavior.BehaviorResult.Succeeded)
            {
                this.timeout = 600;
                character.getStats().idleboredom = 0.0F;
                reset();
            }
        }
        return res;
    }
    public void reset()
    {
        Started = false;
        sq = nullptr;
        pathFind.reset();
    }
    public bool valid()
    {
        return true;
    }
    private bool InDistanceOfPlayer(IsoGameCharacter chr, int x, int y)
    {
        if(chr.getDescriptor().getGroup().Leader == chr.getDescriptor())
            return true;
        if(chr.getDescriptor().getGroup().Leader.getInstance().getCurrentSquare().getRoom() != nullptr && chr.getCurrentSquare().getRoom() == nullptr)
            return false;
        if(chr.getDescriptor().getGroup().Leader.getInstance().getCurrentSquare().getRoom() == nullptr && chr.getCurrentSquare().getRoom() != nullptr)
            return false;
        if(chr.getDescriptor().getGroup().Leader.getInstance().getCurrentSquare().getRoom() != nullptr && chr.getCurrentSquare().getRoom() != nullptr && chr.getCurrentSquare().getRoom().building == chr.getDescriptor().getGroup().Leader.getInstance().getCurrentSquare().getRoom().building && chr.getThreatLevel() == 0)
            return true;
        else
            return IsoUtils.DistanceManhatten(x, y, (int)chr.getDescriptor().getGroup().Leader.getInstance().getX(), (int)chr.getDescriptor().getGroup().Leader.getInstance().getY()) < chr.getPersonality().getPlayerDistanceComfort();
    }
    public float getPriority(IsoGameCharacter character)
    {
        float score = 1.0F;
        if(character.getThreatLevel() > 0)
            score -= 1000000F;
        if(character.getTimeSinceZombieAttack() < 30)
            score = -1000000F;
        return score;
    }
    public int renderDebug(int y)
    {
        int x = 50;
        TextManager.instance.DrawString(UIFont.Small, x, y, "SatisfyIdleBehaviour", 1.0F, 1.0F, 1.0F, 1.0F);
        return y += 30;
    }
    public bool Started;
    bool OtherRoom;
    PathFindBehavior pathFind;
    IsoGridSquare sq;
    int timeout;
}
} // namespace
