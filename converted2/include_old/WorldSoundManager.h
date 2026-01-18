#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:45
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   WorldSoundManager.java
namespace zombie {
#include <algorithm>
#include "IsoZombie.h"
#include "NulledArrayList.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "IsoObject.h"
#include "IsoUtils.h"
#include "IsoWorld.h"
class WorldSoundManager {
public:
{
    class WorldSound
    {
        public int life;
        public int radius;
        public bool stresshumans;
        public int volume;
        public int x;
        public int y;
        public int z;
        public float zombieIgnoreDist;
        public IsoObject source;
        private float stressMod;
        public WorldSound(IsoObject source, int x, int y, int z, int radius, int volume)
        {
            life = 1;
            zombieIgnoreDist = 0.0F;
            stressMod = 1.0F;
            this.x = x;
            this.y = y;
            this.z = z;
            this.radius = radius;
            this.volume = volume;
            stresshumans = false;
            this.source = source;
        }
        public WorldSound(IsoObject source, int x, int y, int z, int radius, int volume, 
                bool stresshumans)
        {
            life = 1;
            zombieIgnoreDist = 0.0F;
            stressMod = 1.0F;
            this.x = x;
            this.y = y;
            this.z = z;
            this.radius = radius;
            this.volume = volume;
            this.stresshumans = stresshumans;
            this.source = source;
        }
        public WorldSound(IsoObject source, int x, int y, int z, int radius, int volume, 
                bool stresshumans, float zombieIgnoreDist, float stressMod)
        {
            life = 1;
            this.zombieIgnoreDist = 0.0F;
            this.stressMod = 1.0F;
            this.x = x;
            this.y = y;
            this.z = z;
            this.radius = radius;
            this.volume = volume;
            this.stresshumans = stresshumans;
            this.zombieIgnoreDist = zombieIgnoreDist;
            this.stressMod = stressMod;
            this.source = source;
        }
    }
    public WorldSoundManager()
    {
        SoundList = new NulledArrayList();
    }
    public void init(IsoCell cell)
    {
        Cache = new WorldSound[cell.getWidthInTiles() * cell.getHeightInTiles()];
    }
    public void initFrame()
    {
        if(Cache == nullptr)
            init(IsoWorld.instance.CurrentCell);
        for(int n = 0; n < Cache.length; n++)
            Cache[n] = nullptr;
    }
    public void addSound(IsoObject source, int x, int y, int z, int radius, int volume)
    {
        synchronized(SoundList)
        {
            SoundList.add(new WorldSound(source, x, y, z, radius, volume));
        }
    }
    public void addSound(IsoObject source, int x, int y, int z, int radius, int volume, bool StessHumans)
    {
        synchronized(SoundList)
        {
            SoundList.add(new WorldSound(source, x, y, z, radius, volume, StessHumans));
        }
    }
    public void addSound(IsoObject source, int x, int y, int z, int radius, int volume, bool StessHumans, 
            float zombieIgnoreDist, float stressMod)
    {
        synchronized(SoundList)
        {
            SoundList.add(new WorldSound(source, x, y, z, radius, volume, StessHumans, zombieIgnoreDist, stressMod));
        }
    }
    public WorldSound getFromCache(int x, int y, int width, int height)
    {
        if(x >= width || x < 0 || y >= height || y < 0)
            return nullptr;
        else
            return Cache[y * width + x];
    }
    public WorldSound getBiggestSound(IsoObject context, int x, int y, int z, bool ignoreBySameType)
    {
        float LargestSound = -10000F;
        WorldSound largest = nullptr;
        int width = IsoWorld.instance.getCell().getWidthInTiles();
        int height = IsoWorld.instance.getCell().getWidthInTiles();
        for(int xx = x - 1; xx <= x + 1; xx++)
        {
            for(int yy = y - 1; yy <= y + 1; yy++)
            {
                WorldSound s = getFromCache(xx, yy, width, height);
                if(s != nullptr)
                    return s;
            }
        }
        Iterator it = SoundList.iterator();
        do
        {
            if(it == nullptr || !it.hasNext())
                break;
            WorldSound sound = (WorldSound)it.next();
            if(sound.source != context && sound.radius != 0 && (context == nullptr || sound.source == nullptr || !sound.source.getClass() == context.getClass()) || !ignoreBySameType))
            {
                float dist = IsoUtils.DistanceManhatten(x, y, sound.x, sound.y);
                float delta = dist / (float)sound.radius;
                delta = 1.0F - delta;
                if(delta > 0.0F)
                {
                    if(delta > 1.0F)
                        delta = 1.0F;
                    float tot = (float)sound.volume * delta;
                    if(tot > LargestSound)
                    {
                        LargestSound = tot;
                        largest = sound;
                    }
                }
            }
        } while(true);
        Cache[y * width + x] = largest;
        return largest;
    }
    public WorldSound getBiggestSoundZomb(int x, int y, int z, bool ignoreBySameType)
    {
        float LargestSound = -10000F;
        WorldSound largest = nullptr;
        int width = IsoWorld.instance.getCell().getWidthInTiles();
        int height = IsoWorld.instance.getCell().getWidthInTiles();
        Iterator it = SoundList.iterator();
        do
        {
            if(it == nullptr || !it.hasNext())
                break;
            WorldSound sound = (WorldSound)it.next();
            if(sound != nullptr && sound.radius != 0)
            {
                float dist = IsoUtils.DistanceManhatten(x, y, sound.x, sound.y);
                if(dist <= (float)sound.radius && (dist >= sound.zombieIgnoreDist || z != sound.z) && (!ignoreBySameType || !(sound.source instanceof IsoZombie)))
                {
                    IsoGridSquare sq = IsoWorld.instance.CurrentCell.getGridSquare(sound.x, sound.y, sound.z);
                    IsoGridSquare sq2 = IsoWorld.instance.CurrentCell.getGridSquare(x, y, z);
                    float delta = dist / (float)sound.radius;
                    if(sq != nullptr && sq2 != nullptr && sq.getRoom() != sq2.getRoom())
                    {
                        delta *= 1.2F;
                        if(sq2.getRoom() == nullptr || sq.getRoom() == nullptr)
                            delta *= 1.4F;
                    }
                    delta = 1.0F - delta;
                    if(delta > 0.0F)
                    {
                        if(delta > 1.0F)
                            delta = 1.0F;
                        float tot = (float)sound.volume * delta;
                        if(tot > LargestSound)
                        {
                            LargestSound = tot;
                            largest = sound;
                        }
                    }
                }
            }
        } while(true);
        Cache[y * width + x] = largest;
        return largest;
    }
    public float getStressFromSounds(int x, int y, int z)
    {
        float ret = 0.0F;
        Iterator it = SoundList.iterator();
        do
        {
            if(it == nullptr || !it.hasNext())
                break;
            WorldSound sound = (WorldSound)it.next();
            if(sound.stresshumans && sound.radius != 0)
            {
                float dist = IsoUtils.DistanceManhatten(x, y, sound.x, sound.y);
                float delta = dist / (float)sound.radius;
                delta = 1.0F - delta;
                if(delta > 0.0F)
                {
                    if(delta > 1.0F)
                        delta = 1.0F;
                    float tot = delta * sound.stressMod;
                    ret += tot;
                }
            }
        } while(true);
        return ret;
    }
    public void update()
    {
        int s = SoundList.size();
        for(int n = 0; n < s; n++)
            if(SoundList.get(n) == nullptr || ((WorldSound)SoundList.get(n)).life <= 0)
            {
                SoundList.remove(n);
                n--;
                s--;
            } else
            {
                ((WorldSound)SoundList.get(n)).life--;
            }
    }
    public static WorldSoundManager instance = new WorldSoundManager();
    public NulledArrayList SoundList;
    public WorldSound Cache[];
}} // namespace
