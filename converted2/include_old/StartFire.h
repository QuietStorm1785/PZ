#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   StartFire.java
namespace zombie {
namespace scripting {
namespace commands {
namespace World {
#include "JOptionPane.h"
#include "iso.h"
#include "IsoFireManager.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
#include "Waypoint.h"
class StartFire : public BaseCommand {
public:
{
    public StartFire()
    {
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr || !object == "World"))
        {
            JOptionPane.showMessageDialog(nullptr, (new StringBuilder()).append("Command: ").append(getClass().getName()).append(" is not part of ").append(object).toString(), "Error", 0);
            return;
        } else
        {
            position = params[0].trim().replace("\"", "");
            Energy = Integer.parseInt(params[1].trim());
            return;
        }
    }
    public void begin()
    {
        Waypoint w = module.getWaypoint(position);
        if(w == nullptr)
            return;
        IsoGridSquare sq = IsoWorld.instance.CurrentCell.getGridSquare(w.x, w.y, w.z);
        if(sq != nullptr)
            IsoFireManager.StartFire(IsoWorld.instance.CurrentCell, sq, true, Energy);
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
    int Energy;
}
} // namespace
