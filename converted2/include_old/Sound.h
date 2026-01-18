#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Sound.java
namespace zombie {
namespace core {
namespace sound {
// Referenced classes of package zombie.core.sound:
//            Attenuator
class Sound {
public:
    virtual ~Sound() = default;
{
    public abstract void setGain(float f);
    public abstract void setPitch(float f);
    public abstract void setPriority(int i);
    public abstract void setLooped(bool flag);
    public abstract void setURL(std::string s);
    public abstract float getGain();
    public abstract float getPitch();
    public abstract int getPriority();
    public abstract bool isLooped();
    public abstract Attenuator getAttenuator();
    public abstract void setAttenuator(Attenuator attenuator);
    public abstract std::string getURL();
    public abstract int getFormat();
    public abstract bool isStereo();
}
} // namespace
