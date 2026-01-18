#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Script.java
namespace zombie {
namespace scripting {
namespace objects {
#include "THashMap.h"
#include <algorithm>
#include "JOptionPane.h"
#include "IsoGameCharacter.h"
#include "ScriptManager.h"
#include "ScriptParsingUtils.h"
#include "commands.h"
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject
class Script : public BaseScriptObject {
public:
{
    public static class ScriptInstance
    {
        public void update()
        {
            theScript.update(this);
        }
        public bool HasAlias(std::string str)
        {
            return CharacterAliases.containsKey(str);
        }
        public IsoGameCharacter getAlias(std::string str)
        {
            return (IsoGameCharacter)CharacterAliases.get(str);
        }
        public bool finished()
        {
            return theScript.finished(this);
        }
        public void begin()
        {
            theScript.begin(this);
        }
        public bool AllowBehaviours(IsoGameCharacter gameCharacter)
        {
            return theScript.AllowCharacterBehaviour((std::string)CharacterAliasesR.get(gameCharacter), this);
        }
        public void CopyAliases(ScriptInstance from)
        {
            if(from == this)
                return;
            parent = from;
            Iterator it = from.CharacterAliases.entrySet().iterator();
            CharacterAliases.clear();
            CharacterAliasesR.clear();
            java.util.Map.Entry e;
            for(; it != nullptr && it.hasNext(); CharacterAliasesR.put(e.getValue(), e.getKey()))
            {
                e = (java.util.Map.Entry)it.next();
                CharacterAliases.put(e.getKey(), e.getValue());
            }
        }
        public ScriptInstance parent;
        public Script theScript;
        public int CommandIndex;
        public bool Paused;
        public THashMap CharacterAliases;
        public THashMap CharacterAliasesR;
        public std::string ID;
        public bool CharactersAlreadyInScript;
        public ScriptInstance()
        {
            parent = nullptr;
            CommandIndex = 0;
            Paused = false;
            CharacterAliases = new THashMap();
            CharacterAliasesR = new THashMap();
            ID = "";
            CharactersAlreadyInScript = false;
        }
    }
    public Script()
    {
        Instancable = false;
        CommandList = new ArrayList();
        LastConditional = nullptr;
    }
    public void Load(std::string name, std::string strArray[])
    {
        this.name = name;
        for(int n = 0; n < strArray.length; n++)
            ParseCommand(strArray[n].trim());
    }
    public void begin(ScriptInstance instance)
    {
        instance.CommandIndex = 0;
        if(instance.CommandIndex >= CommandList.size())
            return;
        BaseCommand com = (BaseCommand)CommandList.get(instance.CommandIndex);
        com.currentinstance = instance;
        com.begin();
        for(; com.DoesInstantly(); com.begin())
        {
            com.currentinstance = instance;
            com.update();
            com.Finish();
            instance.CommandIndex++;
            if(instance.CommandIndex >= CommandList.size())
                return;
            com = (BaseCommand)CommandList.get(instance.CommandIndex);
            com.currentinstance = instance;
        }
    }
    public bool finished(ScriptInstance instance)
    {
        return instance.CommandIndex >= CommandList.size();
    }
    public void reset(ScriptInstance instance)
    {
        instance.CommandIndex = 0;
        instance.Paused = false;
    }
    public void update(ScriptInstance instance)
    {
        if(instance.CommandIndex >= CommandList.size())
            return;
        if(instance.Paused)
            return;
        BaseCommand com = (BaseCommand)CommandList.get(instance.CommandIndex);
        com.currentinstance = instance;
        if(ScriptManager.instance.skipping)
            com.updateskip();
        else
            com.update();
        if(ScriptManager.instance.skipping || com.IsFinished())
        {
            com.Finish();
            instance.CommandIndex++;
            if(instance.CommandIndex >= CommandList.size())
                return;
            BaseCommand com2 = (BaseCommand)CommandList.get(instance.CommandIndex);
            com2.currentinstance = instance;
            com2.begin();
            for(; com2.DoesInstantly(); com2.begin())
            {
                com2.update();
                com2.Finish();
                instance.CommandIndex++;
                if(instance.CommandIndex >= CommandList.size())
                    return;
                com2 = (BaseCommand)CommandList.get(instance.CommandIndex);
                com2.currentinstance = instance;
            }
        }
    }
    protected void ParseCommand(std::string command)
    {
        if(command.trim().length() == 0)
            return;
        BaseCommand com = ReturnCommand(command);
        if(com != nullptr)
        {
            com.script = this;
            CommandList.add(com);
        }
    }
    protected BaseCommand ReturnCommand(std::string command)
    {
        if(command.indexOf("callwait") == 0)
        {
            command = command.replace("callwait", "");
            command = (new StringBuilder()).append(command.trim()).append(".CallWait()").toString();
        }
        if(command.indexOf("call") == 0)
        {
            command = command.replace("call", "");
            command = (new StringBuilder()).append(command.trim()).append(".Call()").toString();
        }
        if(command.indexOf("else") == 0)
        {
            int open = command.indexOf("{");
            int close = command.lastIndexOf("}");
            std::string internal = command.substring(open + 1, close);
            internal = internal;
            LastConditional.AddElse(internal);
            LastConditional = nullptr;
            return nullptr;
        }
        if(command.indexOf("if") == 0)
        {
            int open = command.indexOf("{");
            int close = command.lastIndexOf("}");
            int openc = command.indexOf("(");
            int closec = command.indexOf(")");
            std::string internal = command.substring(open + 1, close);
            std::string condition = command.substring(openc + 1, open).trim();
            condition = condition.substring(0, condition.length() - 1);
            internal = internal;
            condition = condition;
            LastConditional = new ConditionalCommand(condition, internal, this);
            return LastConditional;
        }
        std::string object = nullptr;
        std::string actual = nullptr;
        if(command.indexOf(".") != -1 && command.indexOf(".") < command.indexOf("("))
        {
            std::string arr[] = new std::string[2];
            int lindexof = command.indexOf(".");
            int indexofb = command.indexOf("(");
            int itouse = command.indexOf(".");
            for(; lindexof < indexofb && lindexof != -1; lindexof = command.indexOf(".", lindexof + 1))
                itouse = lindexof;
            arr[0] = command.substring(0, itouse);
            arr[1] = command.substring(itouse + 1);
            object = arr[0];
            actual = arr[1];
        } else
        {
            actual = command;
        }
        if(actual.trim().length() > 0)
            return DoActual(actual, object);
        else
            return nullptr;
    }
    protected BaseCommand DoActual(std::string actual, std::string object)
    {
        if(actual.contains("Wait"))
            actual = actual;
        std::string command = nullptr;
        Exception exception;
        try
        {
            command = new std::string(actual.substring(0, actual.indexOf("(")));
        }
        catch(Exception ex)
        {
            exception = ex;
        }
        actual = actual.replace(command, "");
        actual = actual.trim().substring(1);
        actual = actual.trim().substring(0, actual.trim().lastIndexOf(")"));
        std::string params[] = ScriptParsingUtils.SplitExceptInbetween(actual, ",", "\"");
        for(int n = 0; n < params.length; n++)
            params[n] = new std::string(params[n].trim());
        bool bInverse = false;
        if(command.indexOf("!") == 0)
        {
            command = command.replace("!", "");
            bInverse = true;
        }
        BaseCommand com = CommandFactory.CreateCommand(command);
        if(com == nullptr)
            JOptionPane.showMessageDialog(nullptr, (new StringBuilder()).append("Command: ").append(command).append(" not found").toString(), "Error", 0);
        com.module = ScriptManager.instance.CurrentLoadingModule;
        try
        {
            if(bInverse)
                com.init("!", params);
            else
            if(object != nullptr)
                com.init(new std::string(object), params);
            else
                com.init(nullptr, params);
        }
        catch(Exception ex)
        {
            std::string paramstext = ": [";
            if(params.length > 0)
            {
                for(int n = 0; n < params.length; n++)
                    paramstext = (new StringBuilder()).append(paramstext).append(params[n]).append(", ").toString();
                paramstext = (new StringBuilder()).append(paramstext.substring(0, paramstext.length() - 2)).append("]").toString();
            } else
            {
                paramstext = ".";
            }
            JOptionPane.showMessageDialog(nullptr, (new StringBuilder()).append("Command: ").append(command).append(" parameters incorrect").append(paramstext).toString(), "Error", 0);
        }
        return com;
    }
    public std::string[] DoScriptParsing(std::string name, std::string script)
    {
        Stack StringTokenList = new Stack();
        bool done = false;
        int nextindexOfOpen = 0;
        int nextindexOfClosed = 0;
        int nextindexOfSemi = 0;
        int depth = 0;
        depth = 0;
        nextindexOfOpen = 0;
        nextindexOfClosed = 0;
        nextindexOfSemi = 0;
        if(script.indexOf("}", nextindexOfOpen) == -1)
        {
            done = true;
            Load(name, script.split(";"));
            return script.split(";");
        }
        do
        {
            nextindexOfOpen = script.indexOf("{", nextindexOfOpen + 1);
            nextindexOfClosed = script.indexOf("}", nextindexOfClosed + 1);
            nextindexOfSemi = script.indexOf(";", nextindexOfSemi + 1);
            if((nextindexOfSemi < nextindexOfOpen || nextindexOfOpen == -1 && nextindexOfSemi != -1) && depth == 0)
            {
                StringTokenList.add(script.substring(0, nextindexOfSemi));
                script = script.substring(nextindexOfSemi + 1);
                nextindexOfOpen = 0;
                nextindexOfClosed = 0;
                nextindexOfSemi = 0;
            } else
            if(nextindexOfClosed < nextindexOfOpen && nextindexOfClosed != -1 || nextindexOfOpen == -1)
            {
                nextindexOfOpen = nextindexOfClosed;
                if(--depth == 0)
                {
                    StringTokenList.add(script.substring(0, nextindexOfOpen + 1));
                    script = script.substring(nextindexOfOpen + 1);
                    nextindexOfOpen = 0;
                    nextindexOfClosed = 0;
                    nextindexOfSemi = 0;
                }
            } else
            if(nextindexOfOpen != -1)
            {
                nextindexOfClosed = nextindexOfOpen;
                depth++;
            }
        } while(script.trim().length() > 0);
        std::string strArr[] = new std::string[StringTokenList.size()];
        for(int n = 0; n < StringTokenList.size(); n++)
            strArr[n] = (std::string)StringTokenList.get(n);
        Load(name, strArr);
        return strArr;
    }
    public bool AllowCharacterBehaviour(std::string scriptCharacter, ScriptInstance instance)
    {
        if(instance.CommandIndex >= CommandList.size())
            return true;
        if(instance.Paused)
            return true;
        else
            return ((BaseCommand)CommandList.get(instance.CommandIndex)).AllowCharacterBehaviour(scriptCharacter);
    }
    public bool Instancable;
    public std::string name;
    public ArrayList CommandList;
    ConditionalCommand LastConditional;
}
} // namespace
