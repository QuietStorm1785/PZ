#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AddEnemy.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include <algorithm>
#include "IsoGameCharacter.h"
#include "IsoSurvivor.h"
#include "BaseCommand.h"
#include "objects.h"
class AddEnemy : public BaseCommand {
public:
{
    public AddEnemy()
    {
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
        Other = params[0].trim();
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
        IsoGameCharacter other;
        if(currentinstance != nullptr && currentinstance.HasAlias(Other))
        {
            other = currentinstance.getAlias(Other);
        } else
        {
            if(module.getCharacter(Other) == nullptr)
                return;
            if(module.getCharacter(Other).Actual == nullptr)
                return;
            other = module.getCharacter(Other).Actual;
        }
        if(chr instanceof IsoSurvivor)
            ((IsoSurvivor)chr).getEnemyList().add(other);
    }
    public bool DoesInstantly()
    {
        return true;
    }
    std::string owner;
    std::string say;
    std::string Other;
    IsoGameCharacter chr;
}
} // namespace
