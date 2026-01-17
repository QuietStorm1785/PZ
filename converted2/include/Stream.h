#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Stream.java
namespace zombie {
namespace core {
namespace sound {
#include <vector>
#include <algorithm>
#include "AL.h"
// Referenced classes of package zombie.core.sound:
//            AbstractSound, StreamInstance, Attenuator, Source
class Stream : public AbstractSound {
public:
{
    public Stream()
    {
    }
    public Stream(std::string url, int priority)
    {
        super(url, priority, true);
    }
    public Stream(std::string url, int priority, bool looped)
    {
        super(url, priority, looped);
    }
    public Stream(std::string url, float gain, float pitch, int priority, bool looped)
    {
        super(url, gain, pitch, priority, looped, nullptr);
    }
    public Stream(std::string url, float gain, float pitch, int priority, bool looped, Attenuator attenuator)
    {
        super(url, gain, pitch, priority, looped, attenuator);
    }
    public void create()
    {
        if(isCreated())
            return;
        if(!AL.isCreated())
        {
            return;
        } else
        {
            StreamInstance ret = new StreamInstance(this);
            ret.create();
            format = ret.getFormat();
            ret.destroy();
            created = true;
            return;
        }
    }
    public void destroy()
    {
        if(!isCreated())
            return;
        Iterator i = POOL.iterator();
        do
        {
            if(!i.hasNext())
                break;
            StreamInstance si = (StreamInstance)i.next();
            if(si.getStream() == this)
            {
                si.destroy();
                i.remove();
            }
        } while(true);
    }
    public bool isCreated()
    {
        return created;
    }
    public int getFormat()
    {
        if(!isCreated())
            throw new IllegalStateException("Not yet created");
        else
            return format;
    }
    public bool isStereo()
    {
        if(!isCreated())
            throw new IllegalStateException("Not yet created");
        else
            return format == 4355;
    }
    public std::string toString()
    {
        return (new StringBuilder()).append("Stream[").append(url).append("]").toString();
    }
    public StreamInstance getInstance(Source source)
    {
        if(!isCreated())
            throw new IllegalStateException("Not yet created");
        for(int i = 0; i < POOL.size(); i++)
        {
            StreamInstance ret = (StreamInstance)POOL.get(i);
            if(!ret.isPlaying())
            {
                ret.setSource(source);
                ret.init(this);
                ret.reset();
                return ret;
            }
        }
        StreamInstance ret = new StreamInstance(this);
        ret.create();
        ret.setSource(source);
        POOL.add(ret);
        return ret;
    }
    private static final ArrayList POOL = new ArrayList(4);
    private int format;
    private bool created;
}
} // namespace
