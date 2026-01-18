#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ReturnToSafehouseConversation.java
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
//            ConversationOrder, FollowOrder
class ReturnToSafehouseConversation : public ConversationOrder {
public:
{
    public ReturnToSafehouseConversation(IsoGameCharacter chr, std::string script)
    {
        super(chr, script);
    }
    public void initOrder()
    {
        Stack available = ((IsoSurvivor)chr).getAvailableMembers();
        int c = available.size();
        Stack Returning = new Stack();
        Stack AtHome = new Stack();
        THashMap map = new THashMap();
        map.put("Leader", chr);
        for(int n = 0; n < available.size(); n++)
        {
            IsoGameCharacter cs = (IsoGameCharacter)available.get(n);
            if(cs.getOrder() instanceof FollowOrder)
                Returning.add(cs);
            else
                AtHome.add(cs);
        }
        for(int n = 0; n < Returning.size(); n++)
            map.put((new StringBuilder()).append("Returning").append(n + 1).toString(), Returning.get(n));
        for(int n = 0; n < AtHome.size(); n++)
            map.put((new StringBuilder()).append("AtSafehouse").append(n + 1).toString(), AtHome.get(n));
        if(!IsoPlayer.isGhostMode());
        inst = ScriptManager.instance.PlayInstanceScript(nullptr, scriptName, map);
    }
}
} // namespace
