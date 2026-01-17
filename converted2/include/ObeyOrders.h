#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ObeyOrders.java
namespace zombie {
namespace behaviors {
namespace survivor {
#include <algorithm>
#include "Behavior.h"
#include "DecisionPath.h"
#include "Order.h"
#include "IsoGameCharacter.h"
#include "IsoCamera.h"
class ObeyOrders : public Behavior {
public:
{
    public ObeyOrders(IsoGameCharacter chr)
    {
        Started = false;
        character = chr;
    }
    public zombie.behaviors.Behavior.BehaviorResult process(DecisionPath path, IsoGameCharacter character)
    {
        int n;
        if(character == IsoCamera.CamCharacter)
            n = 0;
        zombie.behaviors.Behavior.BehaviorResult res;
        if(character.getPersonalNeed() != nullptr)
        {
            if(!character.getPersonalNeed().bInit)
            {
                character.getPersonalNeed().initOrder();
                character.getPersonalNeed().bInit = true;
            }
            res = character.getPersonalNeed().process();
            if(character.getPersonalNeed().complete())
            {
                character.getPersonalNeeds().pop();
                character.setPersonalNeed(nullptr);
            } else
            if(character.getPersonalNeed().ActedThisFrame())
                return res;
        }
        if(character.getOrder() == nullptr)
            return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
        if(!character.getOrder().bInit)
        {
            character.getOrder().initOrder();
            character.getOrder().bInit = true;
        }
        res = character.getOrder().process();
        if(character.getOrder().complete())
            character.getOrders().pop();
        return res;
    }
    public void update()
    {
        if(character.getOrder() != nullptr)
            character.getOrder().update();
    }
    public void reset()
    {
    }
    public float getPathSpeed()
    {
        if(character.getOrder() != nullptr)
            return character.getOrder().getPathSpeed();
        if(character.getDangerLevels() == 0.0F)
            return 0.05F;
        float delta = 10F / character.getDangerLevels();
        if(delta > 1.0F)
            delta = 1.0F;
        if(delta < 0.0F)
            delta = 0.0F;
        return 0.05F + 0.02F * delta;
    }
    public bool valid()
    {
        return true;
    }
    public int renderDebug(int y)
    {
        if(character.getOrder() == nullptr)
            return y;
        else
            return character.getOrder().renderDebug(y);
    }
    IsoGameCharacter character;
    public bool Started;
}
} // namespace
