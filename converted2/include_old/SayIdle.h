#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   SayIdle.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include <algorithm>
#include "IsoGameCharacter.h"
#include "Rand.h"
#include "BaseCommand.h"
#include "objects.h"
// Referenced classes of package zombie.scripting.commands.Character:
//            StringFunctions
class SayIdle : public BaseCommand {
public:
{
    public SayIdle()
    {
        say = new Stack();
    }
    public bool IsFinished()
    {
        if(chr == nullptr)
            return true;
        else
            return !chr.isSpeaking();
    }
    public void update()
    {
    }
    public void init(std::string object, std::string params[])
    {
        owner = object;
        for(int n = 0; n < params.length; n++)
        {
            std::string total = params[n];
            total = module.getLanguage(total);
            if(total.indexOf("\"") == 0)
            {
                total = total.substring(1);
                total = total.substring(0, total.length() - 1);
            }
            say.add(total);
        }
    }
    public void begin()
    {
        if(currentinstance.HasAlias(owner))
        {
            chr = currentinstance.getAlias(owner);
            std::string str = (std::string)say.get(Rand.Next(say.size()));
            str = StringFunctions.EscapeChar(chr, str);
            chr.Say(str);
            return;
        }
        chr = module.getCharacter(owner).Actual;
        if(chr == nullptr)
        {
            return;
        } else
        {
            std::string str = (std::string)say.get(Rand.Next(say.size()));
            str = StringFunctions.EscapeChar(chr, str);
            chr.Say(str);
            return;
        }
    }
    public bool AllowCharacterBehaviour(std::string scriptCharacter)
    {
        return true;
    }
    public bool DoesInstantly()
    {
        return false;
    }
    std::string owner;
    Stack say;
    IsoGameCharacter chr;
}
} // namespace
