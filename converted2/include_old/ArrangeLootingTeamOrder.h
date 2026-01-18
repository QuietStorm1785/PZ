#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ArrangeLootingTeamOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include "THashMap.h"
#include <algorithm>
#include "characters.h"
#include "ScriptManager.h"
#include "Script.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            ConversationOrder, IdleOrder, FollowOrder
class ArrangeLootingTeamOrder : public ConversationOrder {
public:
{
    public ArrangeLootingTeamOrder(IsoGameCharacter chr, std::string script)
    {
        super(chr, script);
    }
    public void initOrder()
    {
        Stack available = ((IsoSurvivor)chr).getAvailableMembers();
        int c = available.size();
        Stack Guards = new Stack();
        Stack Companions = new Stack();
        if(c == 0)
            return;
        if(c == 1)
            Guards.addAll(available);
        else
        if(c == 2)
        {
            Guards.add(available.get(0));
            Companions.add(available.get(1));
        } else
        if(c == 3)
        {
            Guards.add(available.get(0));
            Companions.add(available.get(1));
            Companions.add(available.get(2));
        } else
        if(c == 4)
        {
            Guards.add(available.get(0));
            Companions.add(available.get(1));
            Companions.add(available.get(2));
            Guards.add(available.get(3));
        } else
        if(c >= 5)
        {
            Guards.add(available.get(0));
            Companions.add(available.get(1));
            Companions.add(available.get(2));
            Guards.add(available.get(3));
            Companions.add(available.get(4));
            for(int n = 5; n < available.size(); n++)
                Guards.add(available.get(n));
        }
        THashMap map = new THashMap();
        map.put("Leader", chr);
        for(int n = 0; n < Guards.size(); n++)
        {
            map.put((new StringBuilder()).append("Guard").append(n + 1).toString(), Guards.get(n));
            ((IsoGameCharacter)Guards.get(n)).GiveOrder(new IdleOrder((IsoGameCharacter)Guards.get(n)), true);
        }
        for(int n = 0; n < Companions.size(); n++)
        {
            map.put((new StringBuilder()).append("Companion").append(n + 1).toString(), Companions.get(n));
            ((IsoGameCharacter)Companions.get(n)).GiveOrder(new FollowOrder((IsoGameCharacter)Companions.get(n), chr, 4), true);
        }
        if(!IsoPlayer.isGhostMode());
        inst = ScriptManager.instance.PlayInstanceScript(nullptr, scriptName, map);
    }
}
} // namespace
