#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   StopAllScriptsExcept.java
namespace zombie {
namespace scripting {
namespace commands {
#include <vector>
#include <algorithm>
#include "ScriptManager.h"
#include "Script.h"
// Referenced classes of package zombie.scripting.commands:
//            BaseCommand
class StopAllScriptsExcept : public BaseCommand {
public:
{
    public StopAllScriptsExcept()
    {
        scripts = new ArrayList();
    }
    public void init(std::string object, std::string params[])
    {
        for(int n = 0; n < params.length; n++)
            scripts.add(params[n].trim());
    }
    public void begin()
    {
        for(int n = 0; n < ScriptManager.instance.PlayingScripts.size(); n++)
        {
            bool bFound = false;
            for(int m = 0; m < scripts.size(); m++)
                if(((std::string)scripts.get(m)) == ((zombie.scripting.objects.Script.ScriptInstance)ScriptManager.instance.PlayingScripts.get(n)).theScript.name))
                    bFound = true;
            if(!bFound)
                ScriptManager.instance.StopScript(((zombie.scripting.objects.Script.ScriptInstance)ScriptManager.instance.PlayingScripts.get(n)).theScript.name);
        }
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
    ArrayList scripts;
}
} // namespace
