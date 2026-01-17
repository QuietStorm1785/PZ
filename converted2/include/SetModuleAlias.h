#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   SetModuleAlias.java
namespace zombie {
namespace scripting {
namespace commands {
#include "THashMap.h"
#include "ScriptManager.h"
// Referenced classes of package zombie.scripting.commands:
//            BaseCommand
class SetModuleAlias : public BaseCommand {
public:
{
    public SetModuleAlias()
    {
    }
    public void init(std::string object, std::string params[])
    {
        a = params[0].trim();
        b = params[1].trim();
    }
    public void begin()
    {
        ScriptManager.instance.ModuleAliases.put(a, b);
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
    std::string name;
    std::string a;
    std::string b;
}
} // namespace
