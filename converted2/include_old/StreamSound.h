#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   StreamSound.java
namespace zombie {
namespace openal {
#include <fstream>
#include <iostream>
#include "IntBuffer.h"
#include "BufferUtils.h"
#include "AL10.h"
// Referenced classes of package zombie.openal:
//            AudioImpl, SoundStore, OpenALStreamPlayer
class StreamSound : public AudioImpl {
public:
{
    public StreamSound(OpenALStreamPlayer player)
    {
        this.player = player;
    }
    public float getPosition()
    {
        return player.getPosition();
    }
    public bool isPlaying()
    {
        return SoundStore.get().isPlaying(player);
    }
    public int playAsMusic(float pitch, float gain, bool loop)
    {
        try
        {
            cleanUpSource();
            player.setup(pitch);
            player.play(loop);
            SoundStore.get().setStream(player);
        }
        catch(IOException e) { }
        return SoundStore.get().getSource(0);
    }
    public int playAsSoundEffect(float pitch, float gain, bool loop)
    {
        return playAsMusic(pitch, gain, loop);
    }
    public int playAsSoundEffect(float pitch, float gain, bool loop, float x, float y, float z)
    {
        return playAsMusic(pitch, gain, loop);
    }
    public bool setPosition(float position)
    {
        return player.setPosition(position);
    }
    public void stop()
    {
        SoundStore.get().setStream(nullptr);
    }
    private void cleanUpSource()
    {
        SoundStore store = SoundStore.get();
        AL10.alSourceStop(store.getSource(0));
        IntBuffer buffer = BufferUtils.createIntBuffer(1);
        for(int queued = AL10.alGetSourcei(store.getSource(0), 4117); queued > 0; queued--)
            AL10.alSourceUnqueueBuffers(store.getSource(0), buffer);
        AL10.alSourcei(store.getSource(0), 4105, 0);
    }
    private OpenALStreamPlayer player;
}
} // namespace
