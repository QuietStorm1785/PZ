#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TestStat.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "SurvivorDesc.h"
#include "Rand.h"
#include "BaseCommand.h"
#include "objects.h"
class TestStat : public BaseCommand {
public:
{
    public TestStat()
    {
        modifier = 0;
        invert = false;
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
        if(object.indexOf("!") == 0)
        {
            invert = true;
            object = object.substring(1);
        }
        owner = object;
        stat = params[0].trim();
        if(params.length > 1)
            modifier = Integer.parseInt(params[1].trim());
    }
    public bool getValue()
    {
        float stat = 0.0F;
        if(currentinstance != nullptr && currentinstance.HasAlias(owner))
            chr = currentinstance.getAlias(owner);
        else
            chr = module.getCharacter(owner).Actual;
        if(chr == nullptr)
            return false;
        if(this.stat.contains("Compassion"))
            stat = chr.getDescriptor().getCompassion();
        if(this.stat.contains("Bravery"))
            stat = chr.getDescriptor().getBravery() * 2.0F;
        if(this.stat.contains("Loner"))
            stat = chr.getDescriptor().getLoner();
        if(this.stat.contains("Temper"))
            stat = chr.getDescriptor().getTemper();
        stat *= 10F;
        if(invert)
            return (float)Rand.Next(100) >= stat + (float)modifier;
        else
            return (float)Rand.Next(100) < stat + (float)modifier;
    }
    public void begin()
    {
    }
    public bool AllowCharacterBehaviour(std::string scriptCharacter)
    {
        return true;
    }
    public bool DoesInstantly()
    {
        return true;
    }
    std::string owner;
    std::string stat;
    int modifier;
    IsoGameCharacter chr;
    bool invert;
}
} // namespace
