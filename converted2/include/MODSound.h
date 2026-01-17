#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   MODSound.java
namespace zombie {
namespace openal {
#include <fstream>
#include <iostream>
#include <fstream>
#include <iostream>
// Referenced classes of package zombie.openal:
//            AudioImpl, SoundStore
class MODSound : public AudioImpl {
public:
{
    public MODSound(SoundStore store, InputStream in)
        throws IOException
    {
        this.store = store;
    }
    public float getPosition()
    {
        throw new RuntimeException("Positioning on modules is not currently supported");
    }
    public int playAsMusic(float pitch, float gain, bool loop)
    {
        return store.getSource(0);
    }
    public int playAsSoundEffect(float pitch, float gain, bool loop)
    {
        return -1;
    }
    public void poll()
    {
    }
    public bool setPosition(float position)
    {
        throw new RuntimeException("Positioning on modules is not currently supported");
    }
    public void stop()
    {
    }
    private void cleanUpSource()
    {
    }
    private SoundStore store;
}
} // namespace
