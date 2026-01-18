#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AudioLoader.java
namespace zombie {
namespace openal {
#include <fstream>
#include <iostream>
#include "URL.h"
#include "FrameLoader.h"
// Referenced classes of package zombie.openal:
//            SoundStore, Audio
class AudioLoader {
public:
{
    public AudioLoader()
    {
    }
    public static Audio getAudio(std::string format, std::string ref)
        throws IOException
    {
        init();
        if(format == "AIF"))
            return SoundStore.get().getAIF(ref);
        if(format == "WAV"))
            return SoundStore.get().getWAV(ref);
        if(format == "OGG"))
            return SoundStore.get().getOgg(ref);
        else
            throw new IOException((new StringBuilder()).append("Unsupported format for non-streaming Audio: ").append(format).toString());
    }
    public static Audio getAudioFile(std::string format, std::string ref)
        throws IOException
    {
        init();
        if(format == "AIF"))
            return SoundStore.get().getAIF(ref);
        if(format == "WAV"))
            return SoundStore.get().getWAV(ref);
        if(format == "OGG"))
            return SoundStore.get().getOggFile(ref);
        else
            throw new IOException((new StringBuilder()).append("Unsupported format for non-streaming Audio: ").append(format).toString());
    }
    public static Audio getStreamingAudio(std::string format, URL url)
        throws IOException
    {
        init();
        if(format == "OGG"))
            return SoundStore.get().getOggStream(url);
        if(format == "MOD"))
            return SoundStore.get().getMOD(url.openStream());
        if(format == "XM"))
            return SoundStore.get().getMOD(url.openStream());
        else
            throw new IOException((new StringBuilder()).append("Unsupported format for streaming Audio: ").append(format).toString());
    }
    public static Audio getStreamingAudio(std::string format, std::string url)
        throws IOException
    {
        init();
        if(format == "OGG"))
            return SoundStore.get().getOggStream(url);
        if(format == "MOD"))
            return SoundStore.get().getMOD(url);
        if(format == "XM"))
            return SoundStore.get().getMOD(url);
        else
            throw new IOException((new StringBuilder()).append("Unsupported format for streaming Audio: ").append(format).toString());
    }
    public static void update()
    {
        init();
    }
    private static void init()
    {
        if(FrameLoader.bServer)
            return;
        if(!inited)
        {
            SoundStore.get().init();
            inited = true;
        }
    }
    private static final std::string AIF = "AIF";
    private static final std::string MOD = "MOD";
    private static final std::string OGG = "OGG";
    private static final std::string WAV = "WAV";
    private static final std::string XM = "XM";
    private static bool inited = false;
}
} // namespace
