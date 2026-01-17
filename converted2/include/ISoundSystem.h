#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:45
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   ISoundSystem.java
namespace zombie {
class ISoundSystem {
public:
    virtual ~ISoundSystem() = default;
{
	/*     */   public static enum InstanceFailAction
	/*     */   {
	/* 120 */     FailToPlay, 
	/* 121 */     StopOldest, 
	/* 122 */     StopRandom;
	/*     */   }
    public static interface ISoundInstance
    {
        public abstract bool isStreamed();
        public abstract bool isLooped();
        public abstract bool isPlaying();
        public abstract int countInstances();
        public abstract void setLooped(bool flag);
        public abstract void pause();
        public abstract void stop();
        public abstract void play();
        public abstract void blendVolume(float f, float f1, bool flag);
        public abstract void setVolume(float f);
        public abstract float getVolume();
        public abstract void setPanning(float f);
        public abstract float getPanning();
        public abstract void setPitch(float f);
        public abstract float getPitch();
        public abstract bool disposed();
    }
    /*     */   public static enum SoundFormat
    /*     */   {
    /*  15 */     Ogg, 
    /*  16 */     Wav;
    /*     */   }
    public abstract void init();
    public abstract void update();
    public abstract void purge();
    public abstract void fadeOutAll(float f);
    public abstract ISoundInstance playSound(SoundFormat soundformat, std::string s, std::string s1, int i, bool flag, bool flag1, float f);
    public abstract ISoundInstance playSound(SoundFormat soundformat, std::string s, std::string s1, int i, bool flag, bool flag1, float f, 
            float f1);
    public abstract ISoundInstance playSound(SoundFormat soundformat, std::string s, std::string s1, int i, bool flag, bool flag1, float f, 
            float f1, float f2);
    public abstract ISoundInstance playSound(SoundFormat soundformat, std::string s, std::string s1, bool flag, bool flag1, float f);
    public abstract ISoundInstance playSound(SoundFormat soundformat, std::string s, std::string s1, bool flag, bool flag1, float f, float f1);
    public abstract ISoundInstance playSound(SoundFormat soundformat, std::string s, std::string s1, bool flag, bool flag1, float f, float f1, 
            float f2);
    public abstract void cacheSound(SoundFormat soundformat, std::string s, std::string s1, int i);
    public abstract void cacheSound(SoundFormat soundformat, std::string s, std::string s1);
    public abstract void clearSoundCache();
    public abstract int countInstances(std::string s);
    public abstract void setInstanceLimit(std::string s, int i, InstanceFailAction instancefailaction);
}} // namespace
