#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   CharactersAlreadyInScript.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Script {
#include "BaseCommand.h"
#include "Script.h"
class CharactersAlreadyInScript : public BaseCommand {
public:
{
    public CharactersAlreadyInScript()
    {
        invert = false;
    }
    public bool getValue()
    {
        if(invert)
            return !currentinstance.CharactersAlreadyInScript;
        else
            return currentinstance.CharactersAlreadyInScript;
    }
    public bool IsFinished()
    {
        return true;
    }
    public void update()
    {
    }
    public void init(std::string object, std::string params[])
    {
        val = object;
        if(val != nullptr && val.indexOf("!") == 0)
        {
            invert = true;
            val = val.substring(1);
        }
    }
    public bool DoesInstantly()
    {
        return true;
    }
    public void begin()
    {
    }
    std::string position;
    std::string val;
    private bool invert;
}
} // namespace
