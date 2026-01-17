#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsDead.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "BodyDamage.h"
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "objects.h"
class IsDead : public BaseCommand {
public:
{
    public IsDead()
    {
        invert = false;
    }
    public void init(std::string object, std::string params[])
    {
        owner = object;
        if(owner.indexOf("!") == 0)
        {
            invert = true;
            owner = owner.substring(1);
        }
    }
    public bool getValue()
    {
        IsoGameCharacter chr = nullptr;
        if(currentinstance != nullptr && currentinstance.HasAlias(owner))
            chr = currentinstance.getAlias(owner);
        else
            chr = module.getCharacter(owner).Actual;
        if(chr == nullptr)
            return false;
        if(invert)
            return chr.getHealth() > 0.0F && chr.getBodyDamage().getHealth() > 0.0F;
        else
            return chr.getHealth() <= 0.0F || chr.getBodyDamage().getHealth() <= 0.0F;
    }
    public void begin()
    {
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
    bool invert;
}
} // namespace
