#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:45
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   SoundManager.java
namespace zombie {
#include <fstream>
#include <iostream>
#include "FloatBuffer.h"
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include "BufferUtils.h"
#include "AL10.h"
#include "IsoGameCharacter.h"
#include "IsoPlayer.h"
#include "Rand.h"
#include "PropertyContainer.h"
#include "SoundEffect.h"
#include "SoundEngine.h"
#include "Stream.h"
#include "IsoCamera.h"
#include "IsoGridSquare.h"
#include "IsoObject.h"
#include "IsoUtils.h"
#include "IsoFlagType.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Audio.h"
#include "AudioImpl.h"
#include "AudioLoader.h"
#include "SoundStore.h"
// Referenced classes of package zombie:
//            FrameLoader
class SoundManager {
public:
{
    class BlendInfo
    {
        public float TargetVolume;
        public Audio Track;
        public float Volume;
        private float blendSpeedAlpha;
        public bool isMusic;
        private std::string name;
        private bool StopOnSilent;
        public BlendInfo(std::string name, Audio track, float volume, float targetVolume, bool isMusic)
        {
            blendSpeedAlpha = 1.0F;
            StopOnSilent = true;
            this.isMusic = isMusic;
            Track = track;
            Volume = volume;
            TargetVolume = targetVolume;
            this.name = name;
        }
    }
    public SoundManager()
    {
        BlendInfoStack = new Stack();
        SoundVolume = 0.8F;
        BlendFrom = nullptr;
        NextMusicName = "";
        AllowMusic = true;
        DistMulti = 5F;
        str = nullptr;
        streamSound = nullptr;
    }
    public Audio BlendThenStart(Audio musicTrack, float f, std::string PrefMusic)
    {
        musicTrack = nullptr;
        std::string name = PrefMusic;
        for(int m = 0; m < BlendInfoStack.size(); m++)
            if(((BlendInfo)BlendInfoStack.get(m)).isMusic && ((BlendInfo)BlendInfoStack.get(m)).Track.isPlaying())
            {
                musicTrack = ((BlendInfo)BlendInfoStack.get(m)).Track;
                name = ((BlendInfo)BlendInfoStack.get(m)).name;
            }
        if(name != nullptr && musicTrack != nullptr)
        {
            if(!name == PrefMusic))
            {
                BlendVolume(musicTrack, 0.0F);
                NextMusic = PrepareMusic((new StringBuilder()).append("media/music/").append(PrefMusic).toString());
                NextMusicName = PrefMusic;
                BlendFrom = musicTrack;
                NextVolume = f;
            } else
            {
                NextMusic = musicTrack;
            }
            return NextMusic;
        } else
        {
            return PlayMusic(PrefMusic, (new StringBuilder()).append("media/music/").append(PrefMusic).toString(), true, f);
        }
    }
    public void BlendVolume(Audio audio, float targetVolume)
    {
        for(int n = 0; n < BlendInfoStack.size(); n++)
        {
            BlendInfo info = (BlendInfo)BlendInfoStack.get(n);
            if(info.Track == audio)
            {
                info.TargetVolume = targetVolume;
                return;
            }
        }
    }
    public void BlendVolume(Audio audio, float targetVolume, float blendSpeedAlpha)
    {
        for(int n = 0; n < BlendInfoStack.size(); n++)
        {
            BlendInfo info = (BlendInfo)BlendInfoStack.get(n);
            if(info.Track == audio)
            {
                info.TargetVolume = targetVolume;
                info.blendSpeedAlpha = blendSpeedAlpha;
                return;
            }
        }
    }
    public void PlayAsMusic(std::string name, Audio musicTrack, float volume)
    {
        if(!AllowMusic)
            return;
        if(!HasMusic(musicTrack))
        {
            BlendInfo info = new BlendInfo(name, musicTrack, volume, volume, true);
            BlendInfoStack.add(info);
            int id = musicTrack.playAsSoundEffect(1.0F, volume * 0.6F, false);
            musicTrack.setID(id);
        }
    }
    public bool IsMusicPlaying()
    {
        for(int n = 0; n < BlendInfoStack.size(); n++)
            if(((BlendInfo)BlendInfoStack.get(n)).isMusic)
                return true;
        return false;
    }
    public void CheckDoMusic()
    {
        if(!AllowMusic)
            return;
        if(AllowMusic)
            return;
        if((streamSound == nullptr || !streamSound.isActive()) && IsoPlayer.getInstance() != nullptr && (Rand.Next(1500) == 0 || IsoPlayer.getInstance().getTicksSinceSeenZombie() <= 5))
        {
            std::string name = "longambient.ogg";
            if(IsoPlayer.getInstance() != nullptr && IsoPlayer.getInstance().getTicksSinceSeenZombie() <= 5)
                name = zombieTuneChoices[Rand.Next(zombieTuneChoices.length)];
            else
            if(Rand.Next(4) != 0)
                name = millingTuneChoices[Rand.Next(millingTuneChoices.length)];
            str = new Stream((new StringBuilder()).append("classpath:media/music/").append(name).toString(), 1);
            str.create();
            str.setLooped(false);
            str.setGain(0.7F);
            streamSound = SoundEngine.instance.play(str);
            streamSound.setGain(0.7F);
        }
    }
    public void PlayAsMusic(std::string name, Audio musicTrack, bool loop, float volume)
    {
        if(!AllowMusic)
            return;
        if(!HasMusic(musicTrack))
        {
            BlendInfo info = new BlendInfo(name, musicTrack, volume * 0.6F, volume * 0.6F, true);
            BlendInfoStack.add(info);
            int id = musicTrack.playAsSoundEffect(1.0F, volume * 0.6F, loop);
            musicTrack.setID(id);
        }
    }
    public Audio PlayMusic(std::string n, std::string name, bool loop, float maxGain)
    {
        Audio musicTrack = nullptr;
        if(!AllowMusic)
            return nullptr;
        maxGain *= 0.6F;
        try
        {
            musicTrack = AudioLoader.getAudio("OGG", name);
        }
        catch(IOException ex) { }
        int id = 0;
        if(AllowMusic)
        {
            id = musicTrack.playAsSoundEffect(1.0F, maxGain, loop);
            BlendInfo info = new BlendInfo(n, musicTrack, maxGain, maxGain, true);
            BlendInfoStack.add(info);
            musicTrack.setID(id);
        }
        return musicTrack;
    }
    public Audio PlaySound(std::string name, bool loop, float maxGain)
    {
        if(IsoPlayer.DemoMode)
            return nullptr;
        Audio musicTrack = nullptr;
        maxGain *= SoundVolume;
        try
        {
            musicTrack = AudioLoader.getAudio("OGG", (new StringBuilder()).append("media/sound/").append(name).append(".ogg").toString());
        }
        catch(IOException ex) { }
        int id = musicTrack.playAsSoundEffect(1.0F, maxGain, loop);
        BlendInfo info = new BlendInfo(name, musicTrack, maxGain, maxGain, false);
        BlendInfoStack.add(info);
        musicTrack.setID(id);
        return musicTrack;
    }
    public Audio PlaySoundEvenSilent(std::string name, bool loop, float maxGain)
    {
        if(IsoPlayer.DemoMode)
            return nullptr;
        Audio musicTrack = nullptr;
        maxGain *= SoundVolume;
        try
        {
            musicTrack = AudioLoader.getAudio("OGG", (new StringBuilder()).append("media/sound/").append(name).append(".ogg").toString());
        }
        catch(IOException ex) { }
        int id = musicTrack.playAsSoundEffect(1.0F, maxGain, loop);
        BlendInfo info = new BlendInfo(name, musicTrack, maxGain, maxGain, false);
        info.StopOnSilent = false;
        BlendInfoStack.add(info);
        musicTrack.setID(id);
        return musicTrack;
    }
    public Audio PlayJukeboxSound(std::string name, bool loop, float maxGain)
    {
        Audio musicTrack = nullptr;
        maxGain *= SoundVolume;
        try
        {
            musicTrack = AudioLoader.getAudio("OGG", (new StringBuilder()).append("custommusic/").append(name).append(".ogg").toString());
        }
        catch(IOException ex) { }
        int id = musicTrack.playAsSoundEffect(1.0F, maxGain, loop);
        BlendInfo info = new BlendInfo(name, musicTrack, maxGain, maxGain, false);
        BlendInfoStack.add(info);
        musicTrack.setID(id);
        return musicTrack;
    }
    public Audio PlaySoundWav(std::string name, bool loop, float maxGain, float pitchVar)
    {
        Audio musicTrack = nullptr;
        maxGain *= SoundVolume;
        try
        {
            musicTrack = AudioLoader.getAudio("WAV", (new StringBuilder()).append("media/sound/").append(name).append(".wav").toString());
        }
        catch(IOException ex) { }
        float pitchChange = 0.0F;
        if(pitchVar > 0.0F)
            pitchChange = (float)Rand.Next((int)(pitchVar * 1000F)) / 1000F - pitchVar / 2.0F;
        int id = musicTrack.playAsSoundEffect(1.0F + pitchChange, maxGain, loop);
        BlendInfo info = new BlendInfo(name, musicTrack, maxGain, maxGain, false);
        BlendInfoStack.add(info);
        musicTrack.setID(id);
        return musicTrack;
    }
    public Audio PlaySoundWav(std::string name, bool loop, float maxGain)
    {
        Audio musicTrack = nullptr;
        maxGain *= SoundVolume;
        try
        {
            musicTrack = AudioLoader.getAudio("WAV", (new StringBuilder()).append("media/sound/").append(name).append(".wav").toString());
        }
        catch(IOException ex) { }
        int id = musicTrack.playAsSoundEffect(1.0F, maxGain, loop);
        BlendInfo info = new BlendInfo(name, musicTrack, maxGain, maxGain, false);
        BlendInfoStack.add(info);
        musicTrack.setID(id);
        return musicTrack;
    }
    public Audio PlaySoundWav(std::string name, int variations, bool loop, float maxGain)
    {
        Audio musicTrack = nullptr;
        Integer var = Integer.valueOf(Rand.Next(variations));
        var = Integer.valueOf(var.intValue() + 1);
        try
        {
            musicTrack = AudioLoader.getAudio("WAV", (new StringBuilder()).append("media/sound/").append(name).append(var.toString()).append(".wav").toString());
        }
        catch(IOException ex) { }
        int id = musicTrack.playAsSoundEffect(1.0F, maxGain, loop);
        return musicTrack;
    }
    public void update3D()
    {
        float listenerx = 0.0F;
        float listenery = 0.0F;
        float listenerz = 0.0F;
        Vector3 v = new Vector3();
        v.x = -1F;
        v.y = 1.0F;
        v.z = -1F;
        v.normalize();
        FloatBuffer listenerOri = BufferUtils.createFloatBuffer(6).put(new float[] {
            v.x, v.y, v.z, 0.0F, 1.0F, 0.0F
        });
        FloatBuffer listenerVel = BufferUtils.createFloatBuffer(3).put(new float[] {
            0.0F, 0.0F, 0.0F
        });
        FloatBuffer listenerPos = BufferUtils.createFloatBuffer(3).put(new float[] {
            0.0F, 0.0F, 0.0F
        });
        listenerPos.rewind();
        listenerVel.rewind();
        listenerOri.rewind();
        AL10.alListener(4100, listenerPos);
        AL10.alListener(4102, listenerVel);
        AL10.alListener(4111, listenerOri);
    }
    public Audio PlayWorldSound(std::string name, IsoGridSquare source, float pitchVar, float radius, float maxGain, bool ignoreOutside)
    {
        return PlayWorldSound(name, false, source, pitchVar, radius, maxGain, ignoreOutside);
    }
    public Audio PlayWorldSound(std::string name, bool loop, IsoGridSquare source, float pitchVar, float radius, float maxGain, bool ignoreOutside)
    {
        if(IsoPlayer.DemoMode)
            return nullptr;
        if(FrameLoader.bServer || source == nullptr)
            return nullptr;
        maxGain *= SoundVolume;
        Vector2 p = new Vector2(IsoCamera.CamCharacter.getX(), IsoCamera.CamCharacter.getY());
        Vector2 s = new Vector2(source.getX(), source.getY());
        float dist = IsoUtils.DistanceTo(IsoCamera.CamCharacter.getX(), IsoCamera.CamCharacter.getY(), IsoCamera.CamCharacter.getZ(), source.getX(), source.getY(), source.getZ());
        if(IsoCamera.CamCharacter.HasTrait("HardOfHearing"))
            dist *= 4.5F;
        if(dist > radius)
            return nullptr;
        if(!ignoreOutside && (IsoCamera.CamCharacter.getCurrentSquare().getProperties().Is(IsoFlagType.exterior) && !source.getProperties().Is(IsoFlagType.exterior) || !IsoCamera.CamCharacter.getCurrentSquare().getProperties().Is(IsoFlagType.exterior) && source.getProperties().Is(IsoFlagType.exterior)))
            maxGain *= 0.3F;
        float gain = (1.0F - dist / radius) * maxGain;
        Audio musicTrack = nullptr;
        try
        {
            musicTrack = AudioLoader.getAudio("OGG", (new StringBuilder()).append("media/sound/").append(name).append(".ogg").toString());
        }
        catch(IOException ex) { }
        float x = IsoUtils.XToScreen(s.x, s.y, 0.0F, 0);
        float y = IsoUtils.XToScreen(s.x, s.y, 0.0F, 0);
        float x2 = IsoUtils.XToScreen(p.x, p.y, 0.0F, 0);
        float y2 = IsoUtils.XToScreen(p.x, p.y, 0.0F, 0);
        x -= x2;
        y -= y2;
        float DistMulti = this.DistMulti;
        DistMulti *= 15F / radius;
        float z = 0.0F;
        float pitchChange = 0.0F;
        if(pitchVar > 0.0F)
            pitchChange = (float)Rand.Next((int)(pitchVar * 1000F)) / 1000F - pitchVar / 2.0F;
        x /= 700F;
        y /= 700F;
        Vector2 dir = new Vector2(x, y);
        if(dir.getLength() > 0.0F)
            dir.normalize();
        musicTrack.playAsSoundEffect(1.0F + pitchChange, gain, loop, ((float)source.getX() - IsoCamera.CamCharacter.getX()) * DistMulti, ((float)source.getZ() - IsoCamera.CamCharacter.getZ()) * DistMulti, ((float)source.getY() - IsoCamera.CamCharacter.getY()) * DistMulti);
        return musicTrack;
    }
    public Audio PlayWorldSound(std::string name, IsoGridSquare source, float pitchVar, float radius, float maxGain, int choices, bool ignoreOutside)
    {
        Integer choice = Integer.valueOf(Rand.Next(choices) + 1);
        return PlayWorldSound((new StringBuilder()).append(name).append(choice.toString()).toString(), source, pitchVar, radius, maxGain, ignoreOutside);
    }
    public Audio PlayWorldSoundWav(std::string name, IsoGridSquare source, float pitchVar, float radius, float maxGain, bool ignoreOutside)
    {
        return PlayWorldSoundWav(name, false, source, pitchVar, radius, maxGain, ignoreOutside);
    }
    public Audio PlayWorldSoundWav(std::string name, bool loop, IsoGridSquare source, float pitchVar, float radius, float maxGain, bool ignoreOutside)
    {
        if(IsoPlayer.DemoMode)
            return nullptr;
        if(FrameLoader.bServer || source == nullptr)
            return nullptr;
        maxGain *= SoundVolume;
        Vector2 p = new Vector2(IsoCamera.CamCharacter.getX(), IsoCamera.CamCharacter.getY());
        Vector2 s = new Vector2(source.getX(), source.getY());
        float dist = IsoUtils.DistanceTo(IsoCamera.CamCharacter.getX(), IsoCamera.CamCharacter.getY(), IsoCamera.CamCharacter.getZ() * 5F, source.getX(), source.getY(), source.getZ() * 5);
        if(IsoCamera.CamCharacter.HasTrait("HardOfHearing"))
            dist *= 4.5F;
        if(dist > radius)
            return nullptr;
        if(!ignoreOutside && (IsoCamera.CamCharacter.getCurrentSquare().getProperties().Is(IsoFlagType.exterior) && !source.getProperties().Is(IsoFlagType.exterior) || !IsoCamera.CamCharacter.getCurrentSquare().getProperties().Is(IsoFlagType.exterior) && source.getProperties().Is(IsoFlagType.exterior)))
            maxGain *= 0.3F;
        float gain = (1.0F - dist / radius) * maxGain;
        gain = maxGain;
        Audio musicTrack = nullptr;
        float DistMulti = this.DistMulti;
        DistMulti *= 15F / radius;
        try
        {
            musicTrack = AudioLoader.getAudio("WAV", (new StringBuilder()).append("media/sound/").append(name).append(".wav").toString());
        }
        catch(IOException ex) { }
        float x = IsoUtils.XToScreen(s.x, s.y, 0.0F, 0);
        float y = IsoUtils.XToScreen(s.x, s.y, 0.0F, 0);
        float x2 = IsoUtils.XToScreen(p.x, p.y, 0.0F, 0);
        float y2 = IsoUtils.XToScreen(p.x, p.y, 0.0F, 0);
        x -= x2;
        y -= y2;
        float z = 0.0F;
        float pitchChange = 0.0F;
        if(pitchVar > 0.0F)
            pitchChange = (float)Rand.Next((int)(pitchVar * 1000F)) / 1000F - pitchVar / 2.0F;
        x /= 700F;
        y /= 700F;
        Vector2 dir = new Vector2(x, y);
        if(dir.getLength() > 0.0F)
            dir.normalize();
        gain *= gain;
        musicTrack.playAsSoundEffect(1.0F + pitchChange, gain, loop, ((float)source.getX() - IsoCamera.CamCharacter.getX()) * DistMulti, ((float)source.getZ() - IsoCamera.CamCharacter.getZ()) * DistMulti, ((float)source.getY() - IsoCamera.CamCharacter.getY()) * DistMulti);
        BlendInfo info = new BlendInfo(name, musicTrack, gain, gain, false);
        BlendInfoStack.add(info);
        return musicTrack;
    }
    public void PlayWorldSoundWav(std::string name, IsoGridSquare source, float pitchVar, float radius, float maxGain, int choices, bool ignoreOutside)
    {
        Integer choice = Integer.valueOf(Rand.Next(choices) + 1);
        PlayWorldSoundWav((new StringBuilder()).append(name).append(choice.toString()).toString(), source, pitchVar, radius, maxGain, ignoreOutside);
    }
    public Audio PrepareMusic(std::string name)
    {
        Audio musicTrack = nullptr;
        try
        {
            musicTrack = AudioLoader.getAudio("OGG", name);
        }
        catch(IOException ex) { }
        return musicTrack;
    }
    public Audio Start(Audio musicTrack, float f, std::string PrefMusic)
    {
        if(musicTrack != nullptr)
            BlendVolume(musicTrack, 0.0F);
        return PlayMusic(PrefMusic, (new StringBuilder()).append("media/music/").append(PrefMusic).toString(), true, f);
    }
    public void Update()
    {
        SoundStore.get().poll(0);
        if(!AllowMusic && streamSound != nullptr)
        {
            streamSound.stop();
            streamSound = nullptr;
        }
        CheckDoMusic();
        for(int n = 0; n < BlendInfoStack.size(); n++)
        {
            BlendInfo info = (BlendInfo)BlendInfoStack.get(n);
            Audio audio = info.Track;
            float target = info.TargetVolume;
            float current = info.Volume;
            if(BlendFrom == audio && current == 0.0F && info.StopOnSilent)
            {
                audio.stop();
                PlayAsMusic(NextMusicName, NextMusic, true, NextVolume);
                BlendFrom = nullptr;
            }
            if(!audio.isPlaying())
            {
                BlendInfoStack.remove(n);
                n--;
                continue;
            }
            if(current < target)
            {
                current += 0.01F * info.blendSpeedAlpha;
                if(current > target)
                    current = target;
            }
            if(current > target)
            {
                current -= 0.01F * info.blendSpeedAlpha;
                if(current < target)
                    current = target;
            }
            audio.setVolume(current);
            info.Volume = current;
        }
    }
    private bool HasMusic(Audio musicTrack)
    {
        for(int n = 0; n < BlendInfoStack.size(); n++)
        {
            BlendInfo info = (BlendInfo)BlendInfoStack.get(n);
            if(info.Track == musicTrack)
                return true;
        }
        return false;
    }
    public void Purge()
    {
        for(int n = 0; n < BlendInfoStack.size(); n++)
        {
            BlendInfo info = (BlendInfo)BlendInfoStack.get(n);
            info.Track.stop();
        }
        BlendInfoStack.clear();
    }
    public void StopMusic()
    {
        AllowMusic = false;
        for(int n = 0; n < BlendInfoStack.size(); n++)
        {
            BlendInfo info = (BlendInfo)BlendInfoStack.get(n);
            if(info.isMusic)
            {
                info.Track.stop();
                BlendInfoStack.remove(n);
                n--;
            }
        }
    }
    public void StopSound(Audio SoundEffect)
    {
        for(int n = 0; n < BlendInfoStack.size(); n++)
            if(((BlendInfo)BlendInfoStack.get(n)).Track == SoundEffect)
            {
                BlendInfoStack.remove(n);
                return;
            }
        SoundEffect.stop();
        SoundStore.get().audioStore.push((AudioImpl)SoundEffect);
    }
    public void CacheSound(std::string file)
    {
        if(file.contains(".wav"))
            try
            {
                AudioLoader.getAudio("WAV", (new StringBuilder()).append("media/sound/").append(file).toString());
            }
            catch(IOException ex)
            {
                Logger.getLogger(SoundManager.class.getName()).log(Level.SEVERE, nullptr, ex);
            }
        if(file.contains(".ogg"))
            try
            {
                AudioLoader.getAudio("OGG", (new StringBuilder()).append("media/sound/").append(file).toString());
            }
            catch(IOException ex)
            {
                Logger.getLogger(SoundManager.class.getName()).log(Level.SEVERE, nullptr, ex);
            }
    }
    public void update4()
    {
        IsoObject.alphaStep = -100F;
    }
    public void update2()
    {
    }
    public void update3()
    {
    }
    public void update1()
    {
    }
    public Stack BlendInfoStack;
    public Audio MusicTrack;
    public float SoundVolume;
    private Audio BlendFrom;
    private Audio NextMusic;
    private float NextVolume;
    private std::string NextMusicName;
    public bool AllowMusic;
    float DistMulti;
    public std::string millingTuneChoices[] = {
        "tune1.ogg", "tune5.ogg", "tune10.ogg", "tune9.ogg", "tune11.ogg", "tune12.ogg", "tune13.ogg", "tune17.ogg", "tune18.ogg", "tune19.ogg"
    };
    public std::string zombieTuneChoices[] = {
        "tune7.ogg", "tune4.ogg", "tune6.ogg", "tune14.ogg", "tune15.ogg", "tune16.ogg"
    };
    Stream str;
    SoundEffect streamSound;
    public static SoundManager instance = new SoundManager();
}} // namespace
