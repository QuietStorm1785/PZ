#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Conditional.java
namespace zombie {
namespace scripting {
namespace objects {
#include "NulledArrayList.h"
#include "BaseCommand.h"
#include "ConditionalCommand.h"
// Referenced classes of package zombie.scripting.objects:
//            Script
class Conditional : public Script {
public:
{
    public Conditional(std::string con, std::string internal)
    {
        Conditions = new NulledArrayList();
        DoScriptParsing("", internal);
        if(con == nullptr)
            return;
        std::string cons[] = con.split("&&");
        for(int n = 0; n < cons.length; n++)
            if(!cons[n].trim().isEmpty())
                Conditions.add(ReturnCommand(cons[n].trim()));
    }
    public Conditional(std::string con, std::string internal, ConditionalCommand command)
    {
        Conditions = new NulledArrayList();
        this.command = command;
        DoScriptParsing("", internal);
        if(con == nullptr)
            return;
        std::string cons[] = con.split("&&");
        for(int n = 0; n < cons.length; n++)
            if(!cons[n].trim().isEmpty())
                Conditions.add(ReturnCommand(cons[n].trim()));
    }
    public bool ConditionPassed(Script.ScriptInstance inst)
    {
        for(int n = 0; n < Conditions.size(); n++)
        {
            ((BaseCommand)Conditions.get(n)).currentinstance = inst;
            if(!((BaseCommand)Conditions.get(n)).getValue())
                return false;
        }
        return true;
    }
    NulledArrayList Conditions;
    public ConditionalCommand command;
}
} // namespace
