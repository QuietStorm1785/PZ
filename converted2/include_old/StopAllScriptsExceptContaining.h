#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   StopAllScriptsExceptContaining.java
namespace zombie {
namespace scripting {
namespace commands {
#include <algorithm>
#include "ScriptManager.h"
#include "Script.h"
// Referenced classes of package zombie.scripting.commands:
//            BaseCommand
class StopAllScriptsExceptContaining : public BaseCommand {
public:
{
    public StopAllScriptsExceptContaining()
    {
        scripts = nullptr;
    }
    public void init(std::string object, std::string params[])
    {
        scripts = params[0].trim().replace("\"", "");
    }
    public void begin()
    {
        for(int n = 0; n < ScriptManager.instance.PlayingScripts.size(); n++)
            if(!((zombie.scripting.objects.Script.ScriptInstance)ScriptManager.instance.PlayingScripts.get(n)).theScript.name.contains(scripts))
                ScriptManager.instance.StopScript(((zombie.scripting.objects.Script.ScriptInstance)ScriptManager.instance.PlayingScripts.get(n)).theScript.name);
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
    std::string scripts;
}
} // namespace
