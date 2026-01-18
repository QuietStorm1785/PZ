#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   RandomSelector.java
namespace zombie {
namespace scripting {
namespace objects {
#include <vector>
#include "Rand.h"
#include "ScriptManager.h"
// Referenced classes of package zombie.scripting.objects:
//            Script, ScriptModule
class RandomSelector : public Script {
public:
{
    public RandomSelector()
    {
        scriptsToCall = new ArrayList();
    }
    public void Load(std::string name, std::string strArray[])
    {
        this.name = new std::string(name);
        for(int n = 0; n < strArray.length; n++)
            DoLine(new std::string(strArray[n].trim()));
    }
    private void DoLine(std::string line)
    {
        if(line.isEmpty())
        {
            return;
        } else
        {
            scriptsToCall.add(line);
            return;
        }
    }
    public std::string Process()
    {
        int n = Rand.Next(scriptsToCall.size());
        if(((std::string)scriptsToCall.get(n)).contains("."))
            ScriptManager.instance.PlayScript((std::string)scriptsToCall.get(n));
        else
            ScriptManager.instance.PlayScript((new StringBuilder()).append(module.name).append(".").append((std::string)scriptsToCall.get(n)).toString());
        return (std::string)scriptsToCall.get(n);
    }
    public Script.ScriptInstance Process(Script.ScriptInstance aliases)
    {
        int n = Rand.Next(scriptsToCall.size());
        if(((std::string)scriptsToCall.get(n)).contains("."))
            return ScriptManager.instance.PlayScript((std::string)scriptsToCall.get(n), aliases);
        else
            return ScriptManager.instance.PlayScript((new StringBuilder()).append(module.name).append(".").append((std::string)scriptsToCall.get(n)).toString(), aliases);
    }
    public std::string name;
    public ArrayList scriptsToCall;
}
} // namespace
