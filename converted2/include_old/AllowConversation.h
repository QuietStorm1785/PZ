#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AllowConversation.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "objects.h"
class AllowConversation : public BaseCommand {
public:
{
    public AllowConversation()
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
        bAllow = params[0].trim() == "true");
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
        if(bAllow)
            chr.setAllowConversation(true);
        else
            chr.setAllowConversation(false);
    }
    public bool DoesInstantly()
    {
        return true;
    }
    std::string owner;
    std::string say;
    std::string Other;
    IsoGameCharacter chr;
    bool bAllow;
}
} // namespace
