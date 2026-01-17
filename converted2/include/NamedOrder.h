#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   NamedOrder.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "Order.h"
#include "IsoGameCharacter.h"
#include "Script.h"
#include "ScriptModule.h"
// Referenced classes of package zombie.scripting.commands.Character:
//            Order
class NamedOrder : public zombie {
public:
{
    public NamedOrder()
    {
    }
    public void init(std::string object, std::string params[])
    {
        owner = object;
        this.params = new std::string[params.length - 2];
        int n = 0;
        std::string arr$[] = params;
        int len$ = arr$.length;
        for(int i$ = 0; i$ < len$; i$++)
        {
            std::string p = arr$[i$];
            if(n > 1)
                this.params[n - 2] = p.trim();
            n++;
        }
        name = params[0].trim();
        order = params[1].trim();
    }
    public void begin()
    {
        IsoGameCharacter actual = nullptr;
        if(currentinstance.HasAlias(owner))
            actual = currentinstance.getAlias(owner);
        else
            actual = module.getCharacterActual(owner);
        Order order = orderInfo(actual);
        order.name = name;
    }
    std::string name;
}
} // namespace
