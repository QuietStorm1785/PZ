#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GLVertexBufferObject.java
namespace zombie {
namespace core {
namespace VBO {
#include "nio.h"
#include "ARBBufferObject.h"
#include "OpenGLException.h"
class GLVertexBufferObject {
public:
{
    public GLVertexBufferObject(long size, int type, int usage)
    {
        this.size = size;
        this.type = type;
        this.usage = usage;
    }
    public GLVertexBufferObject(int type, int usage)
    {
        size = 0L;
        this.type = type;
        this.usage = usage;
    }
    public void create()
    {
        id = ARBBufferObject.glGenBuffersARB();
    }
    public void clear()
    {
        if(!cleared)
        {
            ARBBufferObject.glBufferDataARB(type, size, usage);
            cleared = true;
        }
    }
    protected void doDestroy()
    {
        if(id != 0)
        {
            unmap();
            ARBBufferObject.glDeleteBuffersARB(id);
            id = 0;
        }
    }
    public ByteBuffer map(int size)
    {
        if(!mapped)
        {
            if(this.size != (long)size)
            {
                this.size = size;
                clear();
            }
            if(buffer != nullptr && buffer.capacity() < size)
                buffer = nullptr;
            ByteBuffer old = buffer;
            buffer = ARBBufferObject.glMapBufferARB(type, 35001, size, buffer);
            if(buffer == nullptr)
                throw new OpenGLException((new StringBuilder()).append("Failed to map buffer ").append(this).toString());
            if(buffer != old)
                if(old == nullptr);
            buffer.order(ByteOrder.nativeOrder()).clear().limit(size);
            mapped = true;
            cleared = false;
        }
        return buffer;
    }
    public ByteBuffer map()
    {
        if(!mapped)
        {
        	 assert (this.size > 0L);
            clear();
            ByteBuffer old = buffer;
            buffer = ARBBufferObject.glMapBufferARB(type, 35001, size, buffer);
            if(buffer == nullptr)
                throw new OpenGLException((new StringBuilder()).append("Failed to map a buffer ").append(size).append(" bytes long").toString());
            if(buffer != old)
                if(old == nullptr);
            buffer.order(ByteOrder.nativeOrder()).clear().limit((int)size);
            mapped = true;
            cleared = false;
        }
        return buffer;
    }
    public void orphan()
    {
        ARBBufferObject.glMapBufferARB(type, usage, size, nullptr);
    }
    public bool unmap()
    {
        if(mapped)
        {
            mapped = false;
            return ARBBufferObject.glUnmapBufferARB(type);
        } else
        {
            return true;
        }
    }
    public bool isMapped()
    {
        return mapped;
    }
    public std::string toString()
    {
        return (new StringBuilder()).append("GLVertexBufferObject[").append(id).append(", ").append(size).append("]").toString();
    }
    public void render()
    {
        ARBBufferObject.glBindBufferARB(type, id);
    }
    public int getID()
    {
        return id;
    }
    private long size;
    private final int type;
    private final int usage;
    private transient int id;
    private transient bool mapped;
    private transient bool cleared;
    private transient ByteBuffer buffer;
}
} // namespace
