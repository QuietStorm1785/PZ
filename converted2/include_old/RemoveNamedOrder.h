#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   RemoveNamedOrder.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include <algorithm>
#include "Order.h"
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "Script.h"
#include "ScriptModule.h"
class RemoveNamedOrder : public BaseCommand {
public:
{
    public RemoveNamedOrder()
    {
    }
    public void init(std::string object, std::string params[])
    {
        owner = object;
        if(params.length == 1)
            name = params[0].trim();
    }
    public void begin()
    {
        IsoGameCharacter actual = nullptr;
        if(currentinstance.HasAlias(owner))
            actual = currentinstance.getAlias(owner);
        else
            actual = module.getCharacterActual(owner);
        if(!actual.getOrders().empty())
        {
            for(int n = 0; n < actual.getOrders().size(); n++)
                if(((Order)actual.getOrders().get(n)).name == name))
                {
                    actual.getOrders().remove(n);
                    n--;
                }
        }
    }
    public void Finish()
    {
    }
    public bool IsFinished()
    {
        return true;
    }
    public void update()
    {
    }
    public bool DoesInstantly()
    {
        return true;
    }
    std::string owner;
    std::string name;
}
} // namespace
