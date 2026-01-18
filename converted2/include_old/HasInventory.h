#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   HasInventory.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "ItemContainer.h"
#include "BaseCommand.h"
#include "ScriptContainer.h"
#include "ScriptModule.h"
class HasInventory : public BaseCommand {
public:
{
    public HasInventory()
    {
        invert = false;
    }
    public void begin()
    {
    }
    public bool getValue()
    {
        IsoGameCharacter actual = module.getCharacterActual(character);
        ItemContainer cont = nullptr;
        if(actual != nullptr)
        {
            cont = actual.getInventory();
        } else
        {
            ScriptContainer chr = module.getScriptContainer(character);
            if(chr == nullptr)
                return false;
            cont = chr.getActual();
            if(cont == nullptr)
                return false;
        }
        if(invert)
            return !cont.contains(item);
        else
            return cont.contains(item);
    }
    public bool IsFinished()
    {
        return true;
    }
    public void update()
    {
    }
    public void init(std::string object, std::string params[])
    {
        character = object;
        item = params[0].replace("\"", "");
        if(character.indexOf("!") == 0)
        {
            invert = true;
            character = character.substring(1);
        }
    }
    public bool DoesInstantly()
    {
        return true;
    }
    bool invert;
    std::string character;
    std::string item;
}
} // namespace
