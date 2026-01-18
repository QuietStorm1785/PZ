#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoJukebox.java
namespace zombie {
namespace iso {
namespace objects {
#include "SoundManager.h"
#include "WorldSoundManager.h"
#include "IsoPlayer.h"
#include "Core.h"
#include "Rand.h"
#include "IngameState.h"
#include "iso.h"
#include "IsoSprite.h"
#include "Audio.h"
class IsoJukebox : public IsoObject {
public:
{
    public IsoJukebox(IsoCell cell, IsoGridSquare sq, IsoSprite spr)
    {
        super(cell, sq, spr);
        JukeboxTrack = nullptr;
        IsPlaying = false;
        MusicRadius = 30F;
        Activated = false;
        WorldSoundPulseRate = 150;
        WorldSoundPulseDelay = 0;
    }
    public std::string getObjectName()
    {
        return "Jukebox";
    }
    public IsoJukebox(IsoCell cell)
    {
        super(cell);
        JukeboxTrack = nullptr;
        IsPlaying = false;
        MusicRadius = 30F;
        Activated = false;
        WorldSoundPulseRate = 150;
        WorldSoundPulseDelay = 0;
    }
    public IsoJukebox(IsoCell cell, IsoGridSquare sq, std::string gid)
    {
        super(cell, sq, gid);
        JukeboxTrack = nullptr;
        IsPlaying = false;
        MusicRadius = 30F;
        Activated = false;
        WorldSoundPulseRate = 150;
        WorldSoundPulseDelay = 0;
        JukeboxTrack = nullptr;
        IsPlaying = false;
        Activated = false;
        WorldSoundPulseDelay = 0;
    }
    public void SetPlaying(bool ShouldPlay)
    {
        if(IsPlaying == ShouldPlay)
            return;
        IsPlaying = ShouldPlay;
        if(IsPlaying && JukeboxTrack == nullptr)
        {
            std::string Trackname = nullptr;
            switch(Rand.Next(4))
            {
            case 0: // '\0'
                Trackname = "paws1";
                break;
            case 1: // '\001'
                Trackname = "paws2";
                break;
            case 2: // '\002'
                Trackname = "paws3";
                break;
            case 3: // '\003'
                Trackname = "paws4";
                break;
            }
            JukeboxTrack = SoundManager.instance.PlaySound(Trackname, false, 0.0F);
        }
    }
    public bool onMouseLeftClick(int x, int y)
    {
        if(IsoPlayer.getInstance() == nullptr)
            return false;
        if(IsoPlayer.getInstance().getCurrentSquare() == nullptr)
            return false;
        float DistRatioFromSource = 0.0F;
        int Dist = Math.abs(square.getX() - IsoPlayer.getInstance().getCurrentSquare().getX()) + Math.abs((square.getY() - IsoPlayer.getInstance().getCurrentSquare().getY()) + Math.abs(square.getZ() - IsoPlayer.getInstance().getCurrentSquare().getZ()));
        if(Dist < 4)
            if(!Activated)
            {
                if(Core.NumJukeBoxesActive < Core.MaxJukeBoxesActive)
                {
                    WorldSoundPulseDelay = 0;
                    Activated = true;
                    SetPlaying(true);
                    Core.NumJukeBoxesActive++;
                }
            } else
            {
                WorldSoundPulseDelay = 0;
                SetPlaying(false);
                Activated = false;
                if(JukeboxTrack != nullptr)
                {
                    SoundManager.instance.StopSound(JukeboxTrack);
                    JukeboxTrack.stop();
                    JukeboxTrack = nullptr;
                }
                Core.NumJukeBoxesActive--;
            }
        return true;
    }
    public void update()
    {
        if(IsoPlayer.getInstance() == nullptr)
            return;
        if(IsoPlayer.getInstance().getCurrentSquare() == nullptr)
            return;
        if(Activated)
        {
            float DistRatioFromSource = 0.0F;
            int Dist = Math.abs(square.getX() - IsoPlayer.getInstance().getCurrentSquare().getX()) + Math.abs((square.getY() - IsoPlayer.getInstance().getCurrentSquare().getY()) + Math.abs(square.getZ() - IsoPlayer.getInstance().getCurrentSquare().getZ()));
            if((float)Dist < MusicRadius)
            {
                SetPlaying(true);
                DistRatioFromSource = (MusicRadius - (float)Dist) / MusicRadius;
            }
            if(JukeboxTrack != nullptr)
            {
                float DistRatioFromSourceMod = DistRatioFromSource + 0.2F;
                if(DistRatioFromSourceMod > 1.0F)
                    DistRatioFromSourceMod = 1.0F;
                SoundManager.instance.BlendVolume(JukeboxTrack, DistRatioFromSource);
                SoundManager.instance.BlendVolume(IngameState.instance.musicTrack, (1.0F - DistRatioFromSourceMod) * 0.5F);
                if(WorldSoundPulseDelay > 0)
                    WorldSoundPulseDelay--;
                if(WorldSoundPulseDelay == 0)
                {
                    WorldSoundManager.instance.addSound(IsoPlayer.getInstance(), square.getX(), square.getY(), square.getZ(), 70, 70, true);
                    WorldSoundPulseDelay = WorldSoundPulseRate;
                }
                if(!JukeboxTrack.isPlaying())
                {
                    WorldSoundPulseDelay = 0;
                    SetPlaying(false);
                    Activated = false;
                    if(JukeboxTrack != nullptr)
                    {
                        SoundManager.instance.StopSound(JukeboxTrack);
                        JukeboxTrack.stop();
                        JukeboxTrack = nullptr;
                    }
                    Core.NumJukeBoxesActive--;
                }
            }
        }
    }
    private Audio JukeboxTrack;
    private bool IsPlaying;
    private float MusicRadius;
    private bool Activated;
    private int WorldSoundPulseRate;
    private int WorldSoundPulseDelay;
}
} // namespace
