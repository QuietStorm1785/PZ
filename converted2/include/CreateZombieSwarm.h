#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   CreateZombieSwarm.java
namespace zombie {
namespace scripting {
namespace commands {
namespace World {
#include "JOptionPane.h"
#include "IsoWorld.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
#include "Zone.h"
class CreateZombieSwarm : public BaseCommand {
public:
{
    public CreateZombieSwarm()
    {
        num = 1;
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr || !object == "World"))
        {
            JOptionPane.showMessageDialog(nullptr, (new StringBuilder()).append("Command: ").append(getClass().getName()).append(" is not part of ").append(object).toString(), "Error", 0);
            return;
        } else
        {
            num = Integer.parseInt(params[0].trim());
            position = params[1].trim().replace("\"", "");
            return;
        }
    }
    public void begin()
    {
        Zone w = module.getZone(position);
        if(w == nullptr)
        {
            return;
        } else
        {
            IsoWorld.instance.CreateSwarm(num, w.x, w.y, w.x2, w.y2);
            return;
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
    std::string position;
    int num;
}
} // namespace
