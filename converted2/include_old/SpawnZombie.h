#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   SpawnZombie.java
namespace zombie {
namespace scripting {
namespace commands {
namespace World {
#include "JOptionPane.h"
#include "IsoZombie.h"
#include "NulledArrayList.h"
#include "iso.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
#include "Waypoint.h"
class SpawnZombie : public BaseCommand {
public:
{
    public SpawnZombie()
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
        {
            IsoZombie zombie = new IsoZombie(IsoWorld.instance.CurrentCell);
            zombie.KeepItReal = true;
            zombie.setX(w.x);
            zombie.setY(w.y);
            zombie.setZ(w.z);
            zombie.setCurrent(sq);
            IsoWorld.instance.CurrentCell.getZombieList().add(zombie);
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
}
} // namespace
