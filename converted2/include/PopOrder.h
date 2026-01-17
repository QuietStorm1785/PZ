#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   PopOrder.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include <algorithm>
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "Script.h"
#include "ScriptModule.h"
class PopOrder : public BaseCommand {
public:
{
    public PopOrder()
    {
        index = -1;
    }
    public void init(std::string object, std::string params[])
    {
        owner = object;
        if(params.length == 1)
            index = Integer.parseInt(params[0].trim());
    }
    public void begin()
    {
        IsoGameCharacter actual = nullptr;
        if(currentinstance.HasAlias(owner))
            actual = currentinstance.getAlias(owner);
        else
            actual = module.getCharacterActual(owner);
        if(!actual.getOrders().empty())
            if(index == -1)
            {
                actual.getOrders().pop();
            } else
            {
                index = actual.getOrders().size() - index - 1;
                if(index < actual.getOrders().size() && index >= 0)
                    actual.getOrders().remove(index);
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
    int index;
}
} // namespace
