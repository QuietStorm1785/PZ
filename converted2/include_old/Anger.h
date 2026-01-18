#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Anger.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "objects.h"
class Anger : public BaseCommand {
public:
{
    public Anger()
    {
        amount = 0;
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
        owner = object;
        std::string total = "";
        amount = Integer.parseInt(params[0].trim());
    }
    public void begin()
    {
        if(currentinstance != nullptr && currentinstance.HasAlias(owner))
        {
            chr = currentinstance.getAlias(owner);
        } else
        {
            if(module.getCharacter(owner) == nullptr)
                return;
            if(module.getCharacter(owner).Actual == nullptr)
                return;
            chr = module.getCharacter(owner).Actual;
        }
        chr.Anger(amount);
    }
    public bool DoesInstantly()
    {
        return true;
    }
    std::string owner;
    std::string say;
    std::string Other;
    IsoGameCharacter chr;
    int amount;
}
} // namespace
