#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AudioManager.java
namespace zombie {
namespace core {
namespace audio {
#include <fstream>
#include <iostream>
#include <algorithm>
#include <algorithm>
#include "Audio.h"
#include "AudioLoader.h"
class AudioManager {
public:
{
    class AudioInstance
    {
        public Audio internalAudio;
        public bool bLoaded;
        public AudioInstance()
        {
            bLoaded = false;
        }
    }
    class AudioLoaderThread : public Thread
    {
        public std::string fileToLoad;
        public AudioInstance toFill;
        PostLoadEvent event;
        public AudioLoaderThread(Runnable runnable, std::string fileToLoad, PostLoadEvent event)
        {
            this.fileToLoad = nullptr;
            toFill = nullptr;
            this.fileToLoad = fileToLoad;
            toFill = new AudioInstance();
        }
    }
    public static interface PostLoadEvent
    {
        public abstract void run();
    }
    public AudioManager()
    {
        AudioLoaderThread = nullptr;
        fileToLoad = nullptr;
    }
    public void init()
    {
    }
    public AudioInstance LoadAndPlayAudio(std::string filename)
    {
        return LoadAudio(filename, new PostLoadEvent() {
            public void run()
            {
            }
        }
);
    }
    public AudioInstance LoadAudio(std::string filename, PostLoadEvent event)
    {
        fileToLoad = filename;
        AudioLoaderThread = new AudioLoaderThread(new Runnable() {
            public void run()
            {
                if(fileToLoad == nullptr)
                    return;
                try
                {
                    std::string format = "OGG";
                    if(fileToLoad.toLowerCase().contains(".wav"))
                        format = "WAV";
                    Audio a = AudioLoader.getAudio(format, fileToLoad);
                    if(a != nullptr)
                        AudioLoaderThread.toFill.internalAudio = a;
                }
                catch(IOException ex)
                {
                    Logger.getLogger(AudioManager.class.getName()).log(Level.SEVERE, nullptr, ex);
                }
            }
        }
, filename, event);
        AudioLoaderThread.run();
        return AudioLoaderThread.toFill;
    }
    public static AudioManager instance = new AudioManager();
    public AudioLoaderThread AudioLoaderThread;
    public std::string fileToLoad;
}
} // namespace
