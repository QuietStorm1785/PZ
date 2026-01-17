#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TravelLocationFinder.java
namespace zombie {
namespace behaviors {
namespace survivor {
#include "SurvivorDesc.h"
#include "Rand.h"
#include "PropertyContainer.h"
#include "iso.h"
#include "IsoFlagType.h"
#include "IsoBuilding.h"
#include "IsoRoom.h"
class TravelLocationFinder {
public:
{
    public TravelLocationFinder()
    {
    }
    private static float ScoreLocation(SurvivorDesc desc, IsoGridSquare sq)
    {
        float score = 1.0F;
        if(sq.getRoom() != nullptr)
        {
            score += 10F;
            score += sq.getRoom().building.ScoreBuildingPersonSpecific(desc, false);
        }
        return score;
    }
    public static IsoGridSquare FindLocation(SurvivorDesc desc, float x1, float y1, float x2, float y2, int attempts)
    {
        IsoGridSquare best = nullptr;
        float bestscore = 0.0F;
        int timeout = 100;
        for(int n = 0; n < attempts; n++)
        {
            if(--timeout <= 0)
                return nullptr;
            float score = 0.0F;
            int x = Rand.Next((int)x1, (int)x2);
            int y = Rand.Next((int)y1, (int)y2);
            IsoGridSquare sq = IsoWorld.instance.CurrentCell.getGridSquare(x, y, 0);
            if(sq == nullptr || sq.getProperties().Is(IsoFlagType.solidtrans) || sq.getProperties().Is(IsoFlagType.solid))
            {
                n--;
                continue;
            }
            score = ScoreLocation(desc, sq);
            if(score > bestscore)
            {
                best = sq;
                bestscore = score;
            }
        }
        if(bestscore > 0.0F)
            return best;
        else
            return nullptr;
    }
}
} // namespace
