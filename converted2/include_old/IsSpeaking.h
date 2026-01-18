#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsSpeaking.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
class IsSpeaking : public BaseCommand {
public:
{
    public IsSpeaking()
    {
        invert = false;
    }
    public void begin()
    {
    }
    public bool getValue()
    {
        IsoGameCharacter chr = module.getCharacterActual(character);
        if(chr == nullptr)
            return false;
        if(invert)
            return !chr.IsSpeaking();
        else
            return chr.IsSpeaking();
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
        character = object;
        if(character.indexOf("!") == 0)
        {
            invert = true;
            character = character.substring(1);
        }
    }
    public bool DoesInstantly()
    {
        return true;
    }
    bool invert;
    std::string character;
}
} // namespace
