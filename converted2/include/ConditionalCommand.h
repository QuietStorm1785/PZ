#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ConditionalCommand.java
namespace zombie {
namespace scripting {
namespace commands {
#include "Conditional.h"
#include "Script.h"
// Referenced classes of package zombie.scripting.commands:
//            BaseCommand
class ConditionalCommand : public BaseCommand {
public:
{
    public ConditionalCommand(std::string con, std::string internal, Script parent)
    {
        bDoIt = false;
        this.con = new Conditional(con, internal, this);
        inst = new zombie.scripting.objects.Script.ScriptInstance();
        inst.theScript = this.con;
        this.parent = parent;
    }
    public void init(std::string s, std::string as[])
    {
    }
    public bool AllowCharacterBehaviour(std::string scriptCharacter)
    {
        if(bDoIt)
            return con.AllowCharacterBehaviour(scriptCharacter, inst);
        if(elsecon != nullptr)
            return elsecon.AllowCharacterBehaviour(scriptCharacter, inst);
        else
            return true;
    }
    public void begin()
    {
        bDoIt = con.ConditionPassed(currentinstance);
        if(bDoIt)
        {
            inst.CopyAliases(currentinstance);
            inst.theScript = con;
            inst.begin();
        } else
        if(elsecon != nullptr)
        {
            elseinst.CopyAliases(currentinstance);
            elseinst.theScript = elsecon;
            elseinst.begin();
        }
    }
    public bool IsFinished()
    {
        return !bDoIt && elsecon == nullptr || bDoIt && inst.finished() || !bDoIt && elsecon != nullptr && elseinst.finished();
    }
    public void update()
    {
        if(bDoIt)
        {
            inst.CopyAliases(currentinstance);
            inst.update();
        } else
        if(elsecon != nullptr)
        {
            elseinst.CopyAliases(currentinstance);
            elseinst.update();
        }
    }
    public bool DoesInstantly()
    {
        return false;
    }
    public void AddElse(std::string internal)
    {
        elsecon = new Conditional(nullptr, internal);
        elseinst = new zombie.scripting.objects.Script.ScriptInstance();
        elseinst.theScript = elsecon;
    }
    bool bDoIt;
    zombie.scripting.objects.Script.ScriptInstance inst;
    public Script parent;
    Conditional con;
    Conditional elsecon;
    zombie.scripting.objects.Script.ScriptInstance elseinst;
}
} // namespace
