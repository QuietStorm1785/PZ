#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   VBOBuffer.java
namespace zombie {
namespace core {
namespace VBO {
#include "FloatBuffer.h"
#include "IntBuffer.h"
#include "BufferUtils.h"
#include "opengl.h"
class VBOBuffer {
public:
{
    public VBOBuffer()
    {
    }
    public static void init()
    {
        stride = 32;
        Indices = BufferUtils.createIntBuffer(50000);
        Vertices = BufferUtils.createFloatBuffer(50000 * stride);
        vertexBufferID = createVBOID();
        colourBufferID = createVBOID();
        indexBufferID = createVBOID();
    }
    public static int createVBOID()
    {
        if(GLContext.getCapabilities().GL_ARB_vertex_buffer_object)
        {
            IntBuffer buffer = BufferUtils.createIntBuffer(1);
            ARBVertexBufferObject.glGenBuffersARB(buffer);
            return buffer.get(0);
        } else
        {
            return 0;
        }
    }
    public static void bufferData(int id, FloatBuffer buffer)
    {
        if(GLContext.getCapabilities().GL_ARB_vertex_buffer_object)
        {
            ARBVertexBufferObject.glBindBufferARB(34962, id);
            ARBVertexBufferObject.glBufferDataARB(34962, buffer, 35044);
        }
    }
    public static void bufferElementData(int id, IntBuffer buffer)
    {
        if(GLContext.getCapabilities().GL_ARB_vertex_buffer_object)
        {
            ARBVertexBufferObject.glBindBufferARB(34963, id);
            ARBVertexBufferObject.glBufferDataARB(34963, buffer, 35044);
        }
    }
    public static void draw()
    {
    }
    public static void render()
    {
        bufferData(vertexBufferID, Vertices);
        bufferElementData(indexBufferID, Indices);
        GL11.glEnableClientState(32884);
        GL11.glEnableClientState(32886);
        GL11.glEnableClientState(32888);
        int offset = 0;
        GL11.glVertexPointer(2, 5126, stride, offset);
        offset = 8;
        GL11.glColorPointer(4, 5126, stride, offset);
        offset = 24;
        GL11.glTexCoordPointer(2, 5126, stride, offset);
        GL12.glDrawRangeElements(7, 0, numQuads, Indices);
    }
    static int vertexBufferID = -1;
    static int colourBufferID = -1;
    static int indexBufferID = -1;
    static int numQuads = 0;
    static IntBuffer Indices = nullptr;
    static FloatBuffer Vertices = nullptr;
    static int stride = 0;
}
} // namespace
