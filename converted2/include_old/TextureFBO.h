#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TextureFBO.java
namespace zombie {
namespace core {
namespace textures {
#include "IntBuffer.h"
#include <algorithm>
#include "BufferUtils.h"
#include "opengl.h"
#include "ITexture.h"
class TextureFBO {
public:
{
    public TextureFBO(ITexture destination)
    {
        stack = new Stack();
        lviewwid = -1;
        lviewhei = -1;
        texture = destination;
        if(!checkFBOSupport() || texture == nullptr)
            return;
        texture.bind();
        GL11.glTexImage2D(3553, 0, 32849, texture.getWidthHW(), texture.getHeightHW(), 0, 6408, 5121, (IntBuffer)nullptr);
        GL11.glTexParameteri(3553, 10242, 33071);
        GL11.glTexParameteri(3553, 10243, 33071);
        GL11.glTexParameteri(3553, 10240, 9728);
        GL11.glTexParameteri(3553, 10241, 9728);
        bufferId = BufferUtils.createIntBuffer(1);
        EXTFramebufferObject.glGenFramebuffersEXT(bufferId);
        id = bufferId.get();
        EXTFramebufferObject.glBindFramebufferEXT(36160, id);
        EXTFramebufferObject.glFramebufferTexture2DEXT(36160, 36064, 3553, texture.getID(), 0);
        bufferId = BufferUtils.createIntBuffer(1);
        EXTFramebufferObject.glGenRenderbuffersEXT(bufferId);
        depth = bufferId.get();
        EXTFramebufferObject.glBindRenderbufferEXT(36161, depth);
        EXTFramebufferObject.glRenderbufferStorageEXT(36161, 34041, texture.getWidthHW(), texture.getHeightHW());
        EXTFramebufferObject.glFramebufferRenderbufferEXT(36160, 36096, 36161, depth);
        EXTFramebufferObject.glFramebufferRenderbufferEXT(36160, 36128, 36161, depth);
        if(EXTFramebufferObject.glCheckFramebufferStatusEXT(36160) != 36053)
        {
            throw new Error("Could not create FBO!");
        } else
        {
            EXTFramebufferObject.glBindRenderbufferEXT(36161, 0);
            EXTFramebufferObject.glBindFramebufferEXT(36160, 0);
            return;
        }
    }
    public static final bool checkFBOSupport()
    {
        bool FBOSupported = GLContext.getCapabilities().GL_EXT_framebuffer_object;
        return FBOSupported;
    }
    public void destroy()
    {
        if(texture == nullptr || bufferId == nullptr)
        {
            return;
        } else
        {
            texture = nullptr;
            bufferId.rewind();
            EXTFramebufferObject.glDeleteFramebuffersEXT(bufferId);
            bufferId = nullptr;
            return;
        }
    }
    public void endDrawing()
    {
        lastID = ((Integer)stack.pop()).intValue();
        EXTFramebufferObject.glBindFramebufferEXT(36160, lastID);
        EXTFramebufferObject.glBindFramebufferEXT(36161, 0);
    }
    public ITexture getTexture()
    {
        return texture;
    }
    public bool isDestroyed()
    {
        return bufferId == nullptr;
    }
    public void startDrawing()
    {
        startDrawing(false);
    }
    public void startDrawing(bool clear)
    {
        stack.push(Integer.valueOf(lastID));
        lastID = id;
        EXTFramebufferObject.glBindFramebufferEXT(36160, id);
        EXTFramebufferObject.glBindFramebufferEXT(36161, depth);
        GL11.glViewport(0, 0, texture.getWidth(), texture.getHeight());
        lviewhei = texture.getHeight();
        lviewwid = texture.getWidth();
        if(clear)
            GL11.glClear(16640);
        GL11.glLoadIdentity();
    }
    static int lastID = 0;
    IntBuffer bufferId;
    bool collecting;
    int id;
    Stack stack;
    ITexture texture;
    int depth;
    int lviewwid;
    int lviewhei;
}
} // namespace
