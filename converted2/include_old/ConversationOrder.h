#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ConversationOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include "THashMap.h"
#include <algorithm>
#include "Behavior.h"
#include "characters.h"
#include "ScriptManager.h"
#include "Script.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            Order
class ConversationOrder : public Order {
public:
{
    public ConversationOrder(IsoGameCharacter chr, std::string script)
    {
        super(chr);
        this.chr = chr;
        scriptName = script;
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        if(inst == nullptr || inst.finished())
            return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
        else
            return zombie.behaviors.Behavior.BehaviorResult.Working;
    }
    public void initOrder()
    {
        Stack available = ((IsoSurvivor)chr).getAvailableMembers();
        THashMap map = new THashMap();
        map.put("Leader", chr);
        for(int n = 0; n < available.size(); n++)
            map.put((new StringBuilder()).append("Member").append(n + 1).toString(), available.get(n));
        if(!IsoPlayer.isGhostMode());
        inst = ScriptManager.instance.PlayInstanceScript(nullptr, scriptName, map);
    }
    public bool complete()
    {
        return inst == nullptr || inst.finished();
    }
    public void update()
    {
    }
    zombie.scripting.objects.Script.ScriptInstance inst;
    std::string scriptName;
    IsoGameCharacter chr;
}
} // namespace
