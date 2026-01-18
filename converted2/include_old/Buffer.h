#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Buffer.java
namespace zombie {
namespace core {
namespace sound {
#include <fstream>
#include <iostream>
#include "URL.h"
#include "ByteBuffer.h"
#include "BufferUtils.h"
#include "AL.h"
#include "AL10.h"
// Referenced classes of package zombie.core.sound:
//            AbstractSound, OggInputStream, Source, Attenuator
class Buffer : public AbstractSound {
public:
{
    public Buffer()
    {
    }
    public Buffer(std::string url, int priority)
    {
        super(url, priority, false);
    }
    public Buffer(std::string url, int priority, bool looped)
    {
        super(url, priority, looped);
    }
    public Buffer(std::string url, float gain, float pitch, int priority, bool looped)
    {
        super(url, gain, pitch, priority, looped, nullptr);
    }
    public Buffer(std::string url, float gain, float pitch, int priority, bool looped, Attenuator attenuator)
    {
        super(url, gain, pitch, priority, looped, attenuator);
    }
    public void create()
    {
        InputStream is;
        if(!AL.isCreated())
            return;
        buffer = AL10.alGenBuffers();
        if(getURL() == nullptr)
            return;
        is = nullptr;
        try
        {
            if(url.startsWith("classpath:"))
                is = new BufferedInputStream(new FileInputStream(url.substring(10)));
            else
                is = new BufferedInputStream((new URL(url)).openStream());
            OggInputStream ois = new OggInputStream(is);
            switch(ois.getFormat())
            {
            case 1: // '\001'
                format = 4353;
                break;
            case 2: // '\002'
                format = 4355;
                break;
            default:
                throw new RuntimeException((new StringBuilder()).append("Unsupported ogg format loading ").append(url).toString());
            }
            int frequency = ois.getRate();
            ByteArrayOutputStream baos = new ByteArrayOutputStream(BUFSIZE);
            byte buf[] = new byte[BUFSIZE];
            int read;
            while((read = ois.read(buf)) != -1) 
                baos.write(buf, 0, read);
            ByteBuffer decoded = BufferUtils.createByteBuffer(baos.size());
            decoded.put(baos.toByteArray());
            decoded.flip();
            AL10.alBufferData(buffer, format, decoded, frequency);
            System.out.println((new StringBuilder()).append("Uploaded ").append(decoded.limit()).append(" bytes to OpenAL").toString());
        }
        catch(Exception e)
        {
            if(buffer != 0)
            {
                AL10.alDeleteBuffers(buffer);
                buffer = 0;
            }
            throw new RuntimeException(e);
        } finally {
        	/* 171 */       if (is != null)
        		/*     */         try {
        		/* 173 */           is.close();
        		/*     */         }
        		/*     */         catch (IOException e)
        		/*     */         {
        		/*     */         }
        		/*     */     }
    }
    public void destroy()
    {
        if(buffer != 0)
        {
            Source.unattach(this);
            AL10.alDeleteBuffers(buffer);
            buffer = 0;
        }
    }
    public bool isCreated()
    {
        return buffer != 0;
    }
    public final int getBufferID()
    {
        if(!isCreated())
            throw new IllegalStateException("Not yet created");
        else
            return buffer;
    }
    public std::string toString()
    {
        return (new StringBuilder()).append("Buffer[").append(buffer).append(": ").append(url).append("]").toString();
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
    private static final int BUFSIZE = Integer.parseInt(System.getProperty("zombie.core.sound.Buffer.BUFSIZE", "196608"));
    private int buffer;
    private int format;
}
} // namespace
