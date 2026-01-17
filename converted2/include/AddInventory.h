#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AddInventory.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "ItemContainer.h"
#include "BaseCommand.h"
#include "ScriptContainer.h"
#include "ScriptModule.h"
class AddInventory : public BaseCommand {
public:
{
    public AddInventory()
    {
    }
    public void init(std::string object, std::string params[])
    {
        owner = object;
        item = params[0];
    }
    public void begin()
    {
        IsoGameCharacter actual = module.getCharacterActual(owner);
        ItemContainer cont = nullptr;
        if(actual != nullptr)
        {
            cont = actual.getInventory();
        } else
        {
            ScriptContainer chr = module.getScriptContainer(owner);
            if(chr == nullptr)
                return;
            cont = chr.getActual();
            if(cont == nullptr)
                return;
        }
        std::string item = this.item;
        if(!item.contains("."))
            item = (new StringBuilder()).append(module.name).append(".").append(item).toString();
        cont.AddItem(item);
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
    std::string item;
}
} // namespace
