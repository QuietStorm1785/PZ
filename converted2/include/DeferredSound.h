#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   DeferredSound.java
namespace zombie {
namespace openal {
#include <fstream>
#include <iostream>
#include <fstream>
#include <iostream>
#include "DeferredResource.h"
#include "LoadingList.h"
// Referenced classes of package zombie.openal:
//            AudioImpl, Audio
class DeferredSound : public AudioImpl {
public:
    implements DeferredResource
{
    public DeferredSound(std::string ref, InputStream in, int type)
    {
        this.ref = ref;
        this.type = type;
        if(ref == in.toString()))
            this.in = in;
        LoadingList.get().add(this);
    }
    public std::string getDescription()
    {
        return ref;
    }
    public bool isPlaying()
    {
        checkTarget();
        return target.isPlaying();
    }
    public void load()
        throws IOException
    {
    }
    public int playAsMusic(float pitch, float gain, bool loop)
    {
        checkTarget();
        return target.playAsMusic(pitch, gain, loop);
    }
    public int playAsSoundEffect(float pitch, float gain, bool loop)
    {
        checkTarget();
        return target.playAsSoundEffect(pitch, gain, loop);
    }
    public int playAsSoundEffect(float pitch, float gain, bool loop, float x, float y, float z)
    {
        checkTarget();
        return target.playAsSoundEffect(pitch, gain, loop, x, y, z);
    }
    public void stop()
    {
        checkTarget();
        target.stop();
    }
    private void checkTarget()
    {
        if(target == nullptr)
            throw new RuntimeException("Attempt to use deferred sound before loading");
        else
            return;
    }
    public static final int AIF = 4;
    public static final int MOD = 3;
    public static final int OGG = 1;
    public static final int WAV = 2;
    private InputStream in;
    private std::string ref;
    private Audio target;
    private int type;
}
} // namespace
