#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LootMission.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include <algorithm>
#include <vector>
#include "characters.h"
#include "IsoCell.h"
#include "IsoWorld.h"
#include "BuildingScore.h"
#include "IsoBuilding.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            OrderSequence, GotoBuildingOrder, CallMeetingOrder, ArrangeLootingTeamOrder, 
//            EndMeetingOrder, LootBuilding, GotoSafehouseOrder, SecureSafehouse, 
//            ReturnToSafehouseConversation, DumpLootOrder
class LootMission : public OrderSequence {
public:
{
    public LootMission(IsoGameCharacter chr)
    {
        super(chr);
        this.chr = chr;
    }
    public void initOrder()
    {
        character = chr;
        Stack scores = IsoWorld.instance.CurrentCell.getBestBuildings(zombie.iso.IsoCell.BuildingSearchCriteria.General, 8);
        float highestNeedScore = -1F;
        IsoBuilding b = nullptr;
        for(int n = 0; n < scores.size(); n++)
        {
            if(((BuildingScore)scores.get(n)).building == ((IsoSurvivor)chr).getDescriptor().getGroup().Safehouse)
            {
                scores.remove(n);
                n--;
                continue;
            }
            float needsScore = ((BuildingScore)scores.get(n)).building.getNeedsScore(((IsoSurvivor)chr).getDescriptor().getGroup());
            if(needsScore > highestNeedScore)
            {
                highestNeedScore = needsScore;
                b = ((BuildingScore)scores.get(n)).building;
            }
        }
        if(b == nullptr || b.Exits.isEmpty())
            return;
        if(!character.IsInBuilding(((IsoSurvivor)chr).getDescriptor().getGroup().Safehouse))
            Orders.add(new GotoBuildingOrder(chr, ((IsoSurvivor)chr).getDescriptor().getGroup().Safehouse));
        Orders.add(new CallMeetingOrder(chr));
        Orders.add(new ArrangeLootingTeamOrder(chr, "Base.ArrangeLooting"));
        Orders.add(new EndMeetingOrder(chr));
        Orders.add(new GotoBuildingOrder(chr, b));
        Orders.add(new LootBuilding(chr, b, LootBuilding.LootStyle.Extreme));
        b = ((IsoSurvivor)chr).getDescriptor().getGroup().Safehouse;
        Orders.add(new GotoSafehouseOrder(chr));
        Orders.add(new SecureSafehouse(chr));
        Orders.add(new ReturnToSafehouseConversation(chr, "Base.BackWithLoot"));
        Orders.add(new DumpLootOrder(chr, b));
    }
    IsoBuilding b;
    IsoGameCharacter chr;
}
} // namespace
