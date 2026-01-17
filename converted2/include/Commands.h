#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Commands.java
namespace zombie {
namespace console {
#include "InvalidParameterException.h"
#include "IsoPlayer.h"
#include "ItemContainer.h"
#include "PZConsole.h"
#include "TutorialManager.h"
class Commands {
public:
{
    public Commands()
    {
    }
    public static void Log(std::string str)
    {
        PZConsole.instance.Log(str);
    }
    public static void ProcessCommand(std::string command, std::string params[])
    {
        command = command.toLowerCase();
        if(command == "addinv"))
            IsoPlayer.getInstance().getInventory().AddItem(params[0]);
        else
        if(command == "debug"))
        {
            if(params.length > 1)
                throw new InvalidParameterException();
            if(params[0] == "on"))
            {
                TutorialManager.Debug = true;
                Log("Debug mode activated");
            }
            if(params[0] == "off"))
            {
                TutorialManager.Debug = false;
                Log("Debug mode deactivated");
            }
        }
    }
}
} // namespace
