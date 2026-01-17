#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   WaitCommand.java
namespace zombie {
namespace scripting {
namespace commands {
#include "Conditional.h"
#include "Script.h"
// Referenced classes of package zombie.scripting.commands:
//            BaseCommand
class WaitCommand : public BaseCommand {
public:
{
    public WaitCommand()
    {
        frames = 0;
        con = nullptr;
        obj = nullptr;
    }
    public bool IsFinished()
    {
        if(con != nullptr)
        {
            bool passed = con.ConditionPassed(currentinstance);
            if(passed)
                passed = passed;
            return passed;
        } else
        {
            return frames <= 0;
        }
    }
    public void update()
    {
        frames--;
    }
    public void init(std::string object, std::string params[])
    {
        obj = object;
        try
        {
            frames = (int)(30F * Float.parseFloat(params[0].trim()));
        }
        catch(Exception ex)
        {
            std::string total = params[0].trim();
            for(int n = 1; n < params.length; n++)
            {
                total = (new StringBuilder()).append(total).append(", ").toString();
                total = (new StringBuilder()).append(total).append(params[n]).toString();
            }
            con = new Conditional(total.trim(), "");
        }
    }
    public bool AllowCharacterBehaviour(std::string scriptCharacter)
    {
        return !scriptCharacter == obj);
    }
    public void begin()
    {
    }
    public bool DoesInstantly()
    {
        return false;
    }
    int frames;
    Conditional con;
    std::string obj;
}
} // namespace
