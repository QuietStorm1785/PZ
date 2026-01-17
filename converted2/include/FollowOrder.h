#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   FollowOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include "Behavior.h"
#include "PathFindBehavior.h"
#include "characters.h"
#include "NulledArrayList.h"
#include "IsoCamera.h"
#include "IsoGridSquare.h"
#include "IsoAnim.h"
#include "IsoSprite.h"
#include "TextManager.h"
#include "UIFont.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            Order
class FollowOrder : public Order {
public:
{
    public FollowOrder(IsoGameCharacter chr, IsoGameCharacter target, int range)
    {
        super(chr);
        Range = 1;
        pathfindtimer = 60;
        bStrict = false;
        PathFind = new PathFindBehavior();
        rangelast = 0.0F;
        lastDist = 0.0F;
        currentDist = 0.0F;
        this.target = target;
        Range = range;
        PathFind.reset();
        PathFind.name = "FollowOrder";
    }
    public FollowOrder(IsoGameCharacter chr)
    {
        super(chr);
        Range = 1;
        pathfindtimer = 60;
        bStrict = false;
        PathFind = new PathFindBehavior();
        rangelast = 0.0F;
        lastDist = 0.0F;
        currentDist = 0.0F;
    }
    public FollowOrder(IsoGameCharacter chr, IsoGameCharacter target, int range, bool b)
    {
        super(chr);
        Range = 1;
        pathfindtimer = 60;
        bStrict = false;
        PathFind = new PathFindBehavior();
        rangelast = 0.0F;
        lastDist = 0.0F;
        currentDist = 0.0F;
        this.target = target;
        Range = range;
        PathFind.reset();
        PathFind.name = "FollowOrder";
        bStrict = true;
    }
    private bool InDistanceOfPlayer(IsoGameCharacter chr, int x, int y)
    {
        if(target.getCurrentSquare().getRoom() != nullptr && chr.getCurrentSquare().getRoom() != target.getCurrentSquare().getRoom())
            return false;
        if(chr.getCurrentSquare().getRoom() != nullptr && target.getCurrentSquare().getRoom() == nullptr)
        {
            return false;
        } else
        {
            rangelast = currentDist;
            return rangelast < (float)Range;
        }
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        int n;
        if(character == IsoCamera.CamCharacter)
            n = 0;
        lastDist = currentDist;
        currentDist = character.DistTo(target);
        pathfindtimer--;
        bool inDist = InDistanceOfPlayer(character, (int)character.getX(), (int)character.getY());
        if(!inDist && pathfindtimer < 0 && currentDist > (float)(Range * 2))
        {
            PathFind.reset();
            PathFind.sx = (int)character.getX();
            PathFind.sy = (int)character.getY();
            PathFind.sz = (int)character.getZ();
            PathFind.tx = (int)target.getX();
            PathFind.ty = (int)target.getY();
            PathFind.tz = (int)target.getZ();
            pathfindtimer = 120;
        }
        zombie.behaviors.Behavior.BehaviorResult res = PathFind.process(nullptr, character);
        if(res != zombie.behaviors.Behavior.BehaviorResult.Working)
            pathfindtimer = -1;
        return res;
    }
    public bool isCancelledOnAttack()
    {
        return false;
    }
    public float getPriority(IsoGameCharacter character)
    {
        float score = 0.0F;
        float dist = character.DistTo(target);
        lastDist = currentDist;
        currentDist = dist;
        dist -= Range;
        if(dist < 0.0F)
            dist = 0.0F;
        score += dist * 6F;
        score += character.getThreatLevel() * 5;
        score += character.getDescriptor().getLoyalty() * 5F;
        if(target.sprite.CurrentAnim.name == "Run"))
            score *= 2.0F;
        bool bInRange = InDistanceOfPlayer(character, (int)character.getX(), (int)character.getY());
        if(bInRange)
            score = 0.0F;
        else
            score *= 20000F;
        if((character instanceof IsoSurvivor) && !((IsoSurvivor)character).getVeryCloseEnemyList().isEmpty())
            return 0.0F;
        else
            return score;
    }
    public float getPathSpeed()
    {
        return currentDist <= (float)Range * 3F ? 0.06F : 0.08F;
    }
    public int renderDebug(int y)
    {
        int x = 50;
        TextManager.instance.DrawString(UIFont.Small, x, y, "FollowOrder", 1.0F, 1.0F, 1.0F, 1.0F);
        return y += 30;
    }
    public bool complete()
    {
        return target.isDead();
    }
    public void update()
    {
    }
    public int Range;
    public int pathfindtimer;
    public IsoGameCharacter target;
    public bool bStrict;
    PathFindBehavior PathFind;
    float rangelast;
    public float lastDist;
    public float currentDist;
}
} // namespace
