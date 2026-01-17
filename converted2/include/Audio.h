#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Audio.java
namespace zombie {
namespace openal {
class Audio {
public:
    virtual ~Audio() = default;
{
    public abstract int getBufferID();
    public abstract float getPosition();
    public abstract bool isPlaying();
    public abstract int playAsMusic(float f, float f1, bool flag);
    public abstract int playAsSoundEffect(float f, float f1, bool flag);
    public abstract int playAsSoundEffect(float f, float f1, bool flag, float f2, float f3, float f4);
    public abstract void setID(int i);
    public abstract bool setPosition(float f);
    public abstract void setVolume(float f);
    public abstract void stop();
    public abstract int playAsSoundEffectUnbuffered(float f, float f1, bool flag);
}
} // namespace
