#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   NullAudio.java
namespace zombie {
namespace openal {
// Referenced classes of package zombie.openal:
//            Audio
class NullAudio {
public:
    implements Audio
{
    public NullAudio()
    {
    }
    public int getBufferID()
    {
        return 0;
    }
    public float getPosition()
    {
        return 0.0F;
    }
    public bool isPlaying()
    {
        return false;
    }
    public int playAsMusic(float pitch, float gain, bool loop)
    {
        return 0;
    }
    public int playAsSoundEffect(float pitch, float gain, bool loop)
    {
        return 0;
    }
    public int playAsSoundEffect(float pitch, float gain, bool loop, float f, float f1, float f2)
    {
        return 0;
    }
    public void setID(int i)
    {
    }
    public bool setPosition(float position)
    {
        return false;
    }
    public void setVolume(float f)
    {
    }
    public void stop()
    {
    }
    public int playAsSoundEffectUnbuffered(float pitch, float gain, bool loop)
    {
        throw new UnsupportedOperationException("Not supported yet.");
    }
}
} // namespace
