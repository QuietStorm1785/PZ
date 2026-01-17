#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   PlaySoundEffect.java
namespace zombie {
namespace scripting {
namespace commands {
namespace World {
#include "JOptionPane.h"
#include "SoundManager.h"
#include "iso.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
#include "Waypoint.h"
class PlaySoundEffect : public BaseCommand {
public:
{
    public PlaySoundEffect()
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
            format = params[0].trim().replace("\"", "");
            sound = params[1].trim().replace("\"", "");
            position = params[2].trim().replace("\"", "");
            pitchVar = Float.parseFloat(params[3].trim().replace("\"", ""));
            radius = Integer.parseInt(params[4].trim().replace("\"", ""));
            volume = Float.parseFloat(params[5].trim().replace("\"", ""));
            ignoreOutside = params[6].trim().replace("\"", "") == "true");
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
            if(format == "WAV"))
                SoundManager.instance.PlayWorldSoundWav(sound, sq, pitchVar, radius, volume, ignoreOutside);
            else
            if(format == "OGG"))
                SoundManager.instance.PlayWorldSound(sound, sq, pitchVar, radius, volume, ignoreOutside);
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
    std::string sound;
    float pitchVar;
    int radius;
    float volume;
    bool ignoreOutside;
    public std::string format;
}
} // namespace
