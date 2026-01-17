#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestTaskCondition.java
namespace zombie {
namespace scripting {
namespace objects {
#include <algorithm>
#include "BaseCommand.h"
// Referenced classes of package zombie.scripting.objects:
//            Script
class QuestTaskCondition : public Script {
public:
{
    public QuestTaskCondition()
    {
        Conditions = new Stack();
    }
    public void Load(std::string name, std::string strArray[])
    {
        std::string con = strArray[0].trim();
        if(con == nullptr)
            return;
        std::string cons[] = con.split("&&");
        for(int n = 0; n < cons.length; n++)
            if(!cons[n].trim().isEmpty())
                Conditions.add(ReturnCommand(cons[n].trim()));
    }
    public bool ConditionPassed()
    {
        for(int n = 0; n < Conditions.size(); n++)
            if(!((BaseCommand)Conditions.get(n)).getValue())
                return false;
        return true;
    }
    Stack Conditions;
}
} // namespace
