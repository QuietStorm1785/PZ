#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   SelectorBehavior.java
namespace zombie {
namespace behaviors {
#include "IsoGameCharacter.h"
#include "NulledArrayList.h"
// Referenced classes of package zombie.behaviors:
//            Behavior, DecisionPath
class SelectorBehavior : public Behavior {
public:
{
    public SelectorBehavior()
    {
        ID = 0;
    }
    public Behavior.BehaviorResult process(DecisionPath path, IsoGameCharacter character)
    {
        if(ID >= childNodes.size())
            return Behavior.BehaviorResult.Failed;
        Behavior.BehaviorResult res = processChild(path, character, ID);
        if(res == Behavior.BehaviorResult.Failed)
            ID++;
        if(res == Behavior.BehaviorResult.Succeeded)
            return res;
        if(ID == childNodes.size() && res == Behavior.BehaviorResult.Failed)
        {
            ID = 0;
            return Behavior.BehaviorResult.Failed;
        } else
        {
            return Behavior.BehaviorResult.Working;
        }
    }
    public void reset()
    {
    }
    public bool valid()
    {
        return true;
    }
    public int ID;
}
} // namespace
