#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AddHelpIconToWorld.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Tutorial {
#include "JOptionPane.h"
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
#include "Waypoint.h"
#include "UIManager.h"
class AddHelpIconToWorld : public BaseCommand {
public:
{
    public AddHelpIconToWorld()
    {
        offset = 0;
        x = 0;
        y = 0;
        z = 0;
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr || !object == "Tutorial"))
        {
            JOptionPane.showMessageDialog(nullptr, (new StringBuilder()).append("Command: ").append(getClass().getName()).append(" is not part of ").append(object).toString(), "Error", 0);
            return;
        }
        title = params[0].trim().replace("\"", "");
        title = module.getLanguage(title);
        if(title.indexOf("\"") == 0)
        {
            title = title.substring(1);
            title = title.substring(0, title.length() - 1);
        }
        message = params[1].trim().replace("\"", "");
        message = module.getLanguage(message);
        if(message.indexOf("\"") == 0)
        {
            message = message.substring(1);
            message = message.substring(0, message.length() - 1);
        }
        location = params[2].trim().replace("\"", "");
        offset = Integer.parseInt(params[3].trim());
    }
    public void begin()
    {
        Waypoint pt = module.getWaypoint(location.trim());
        if(pt != nullptr)
        {
            x = pt.x;
            y = pt.y;
            z = pt.z;
        } else
        {
            IsoGameCharacter chr = module.getCharacterActual(location);
            if(chr != nullptr)
            {
                x = (int)chr.getX();
                y = (int)chr.getY();
                z = (int)chr.getZ();
            }
        }
        UIManager.AddTutorial(x, y, z, title, message, false, offset);
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
    std::string title;
    std::string message;
    std::string location;
    int offset;
    int x;
    int y;
    int z;
}
} // namespace
