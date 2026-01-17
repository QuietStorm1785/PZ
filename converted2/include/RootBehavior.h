#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   RootBehavior.java
namespace zombie {
namespace behaviors {
#include "IsoGameCharacter.h"
#include "NulledArrayList.h"
// Referenced classes of package zombie.behaviors:
//            Behavior, DecisionPath
class RootBehavior : public Behavior {
public:
{
    public RootBehavior()
    {
    }
    public Behavior.BehaviorResult process(DecisionPath path, IsoGameCharacter character)
    {
        if(childNodes.size() == 0)
            return Behavior.BehaviorResult.Working;
        for(int ID = 0; ID < childNodes.size(); ID++)
            processChild(path, character, ID);
        return Behavior.BehaviorResult.Working;
    }
    public void reset()
    {
    }
    public bool valid()
    {
        return true;
    }
}
} // namespace
