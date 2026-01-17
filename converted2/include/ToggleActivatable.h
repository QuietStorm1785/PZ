#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ToggleActivatable.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Activatable {
#include "Activatable.h"
#include "BaseCommand.h"
#include "ScriptActivatable.h"
#include "ScriptModule.h"
class ToggleActivatable : public BaseCommand {
public:
{
    public ToggleActivatable()
    {
        num = 1.0F;
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
        owner = object;
    }
    public void begin()
    {
        ScriptActivatable chr = module.getActivatable(owner);
        if(chr == nullptr)
            return;
        Activatable acc = chr.getActual();
        if(acc != nullptr)
            acc.Toggle();
    }
    public bool DoesInstantly()
    {
        return true;
    }
    std::string owner;
    float num;
}
} // namespace
