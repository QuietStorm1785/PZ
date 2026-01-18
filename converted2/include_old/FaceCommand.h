#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   FaceCommand.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "IsoDirections.h"
#include "BaseCommand.h"
#include "objects.h"
class FaceCommand : public BaseCommand {
public:
{
    public FaceCommand()
    {
    }
    public void init(std::string object, std::string params[])
    {
        owner = object;
        dir = IsoDirections.valueOf(params[0]);
    }
    public void begin()
    {
        IsoGameCharacter chr = nullptr;
        if(currentinstance != nullptr && currentinstance.HasAlias(owner))
            chr = currentinstance.getAlias(owner);
        else
            chr = module.getCharacter(owner).Actual;
        if(chr == nullptr)
        {
            return;
        } else
        {
            chr.setDir(dir);
            return;
        }
    }
    public void Finish()
    {
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
    std::string owner;
    IsoDirections dir;
}
} // namespace
