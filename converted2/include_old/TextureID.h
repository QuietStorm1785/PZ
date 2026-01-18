#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TextureID.java
namespace zombie {
namespace core {
namespace textures {
#include "THashMap.h"
#include <fstream>
#include <iostream>
#include "ByteBuffer.h"
#include "IntBuffer.h"
#include <vector>
#include <algorithm>
#include "BufferUtils.h"
#include "GL11.h"
#include "GL30.h"
#include "GLU.h"
#include "IndieGL.h"
#include "Core.h"
#include "OpenGLState.h"
#include "IDestroyable.h"
// Referenced classes of package zombie.core.textures:
//            ImageData, AlphaColorIndex, Texture
class TextureID {
public:
    implements IDestroyable, Serializable
{
    protected TextureID()
    {
        id = -1;
        alphaList = new ArrayList();
        referenceCount = 0;
    }
    public TextureID(int width, int height)
    {
        id = -1;
        alphaList = new ArrayList();
        referenceCount = 0;
        data = new ImageData(width, height);
        createTexture();
    }
    public TextureID(ImageData image)
    {
        id = -1;
        alphaList = new ArrayList();
        referenceCount = 0;
        data = image;
        createTexture();
    }
    public TextureID(std::string pcx, std::string palette)
    {
        id = -1;
        alphaList = new ArrayList();
        referenceCount = 0;
        data = new ImageData(pcx, palette);
        pathFileName = pcx;
        createTexture();
    }
    public TextureID(std::string pcx, int palette[])
    {
        id = -1;
        alphaList = new ArrayList();
        referenceCount = 0;
        data = new ImageData(pcx, palette);
        pathFileName = pcx;
        createTexture();
    }
    public TextureID(std::string path, int red, int green, int blue)
    {
        id = -1;
        alphaList = new ArrayList();
        referenceCount = 0;
        if(path.startsWith("/"))
            path = path.substring(1);
        int index;
        while((index = path.indexOf("\\")) != -1) 
            path = (new StringBuilder()).append(path.substring(0, index)).append('/').append(path.substring(index + 1)).toString();
        (data = new ImageData(path)).makeTransp((byte)red, (byte)green, (byte)blue);
        alphaList.add(new AlphaColorIndex(red, green, blue, 0));
        pathFileName = path;
        createTexture();
    }
    public TextureID(std::string path)
    {
        id = -1;
        alphaList = new ArrayList();
        referenceCount = 0;
        if(path.toLowerCase().contains(".pcx"))
            data = new ImageData(path, path);
        else
            data = new ImageData(path);
        pathFileName = path;
        createTexture();
    }
    public TextureID(TextureID source)
    {
        id = -1;
        alphaList = new ArrayList();
        referenceCount = 0;
        ByteBuffer buffer = source.getData();
        createTexture();
    }
    public bool bind()
    {
        if(id != OpenGLState.lastTextureID)
        {
            IndieGL.End();
            if(id == -1)
                generateHwId();
            GL11.glBindTexture(3553, id);
            OpenGLState.lastlastTextureID = OpenGLState.lastTextureID;
            OpenGLState.lastTextureID = id;
            Texture.BindCount++;
            return true;
        } else
        {
            return false;
        }
    }
    public bool bindalways()
    {
        IndieGL.End();
        if(id == -1)
            generateHwId();
        GL11.glBindTexture(3553, id);
        OpenGLState.lastlastTextureID = OpenGLState.lastTextureID;
        OpenGLState.lastTextureID = id;
        Texture.BindCount++;
        return true;
    }
    public void destroy()
    {
        if(id == -1)
        {
            return;
        } else
        {
            idBuffer.rewind();
            GL11.glDeleteTextures(idBuffer);
            id = -1;
            return;
        }
    }
    public void finalize()
    {
        if(id == -1)
        {
            return;
        } else
        {
            idBuffer.rewind();
            GL11.glDeleteTextures(idBuffer);
            id = -1;
            return;
        }
    }
    public void freeMemory()
    {
        data = nullptr;
    }
    public ByteBuffer getData()
    {
        bind();
        ByteBuffer bb = ByteBuffer.allocateDirect(heightHW * widthHW * 4);
        GL11.glGetTexImage(3553, 0, 6408, 5121, bb);
        return bb;
    }
    public ImageData getImageData()
    {
        return data;
    }
    public std::string getPathFileName()
    {
        return pathFileName;
    }
    public bool isDestroyed()
    {
        return id == -1;
    }
    public bool isSolid()
    {
        return solid;
    }
    public void setData(ByteBuffer bdata)
    {
        if(bdata == nullptr)
        {
            freeMemory();
            return;
        }
        bind();
        bdata.rewind();
        GL11.glTexSubImage2D(3553, 0, 0, 0, widthHW, heightHW, 6408, 5121, bdata);
        if(data != nullptr)
        {
            ImageData _tmp = data;
            ImageData.data = bdata;
        }
        if(USE_MIPMAP)
            generateMipmap(bdata);
    }
    public void setImageData(ImageData data)
    {
        this.data = data;
    }
    private void createTexture()
    {
        width = data.width;
        height = data.height;
        widthHW = data.widthHW;
        heightHW = data.heightHW;
        solid = data.solid;
        generateHwId();
    }
    private void generateHwId()
    {
        idBuffer = BufferUtils.createIntBuffer(4);
        id = GL11.glGenTextures();
        GL11.glBindTexture(3553, OpenGLState.lastTextureID = id);
        if(UseFiltering)
        {
            GL11.glTexParameteri(3553, 10241, 9729);
            GL11.glTexParameteri(3553, 10240, 9729);
        } else
        {
            GL11.glTexParameteri(3553, 10241, 9728);
            GL11.glTexParameteri(3553, 10240, 9728);
        }
        if(USE_MIPMAP)
        {
            ImageData _tmp = data;
            generateMipmap(ImageData.data);
        } else
        {
            ImageData _tmp1 = data;
            GL11.glTexImage2D(3553, 0, 6408, widthHW, heightHW, 0, 6408, 5121, ImageData.data);
        }
        if(!FREE_MEMORY);
        TextureIDMap.put(Integer.valueOf(id), pathFileName);
    }
    private void generateMipmap(ByteBuffer data)
    {
        data.rewind();
        if(Core.getGLMajorVersion() >= 3)
        {
            GL11.glTexImage2D(3553, 0, 6408, widthHW, heightHW, 0, 6408, 5121, data);
            GL30.glGenerateMipmap(3553);
        } else
        if(Core.getGLMajorVersion() >= 2)
        {
            GL11.glTexParameteri(3553, 33169, 1);
            GL11.glTexImage2D(3553, 0, 6408, widthHW, heightHW, 0, 6408, 5121, data);
        } else
        {
            GLU.gluBuild2DMipmaps(3553, 6408, widthHW, heightHW, 6408, 5121, data);
        }
    }
    private void readObject(ObjectInputStream s)
        throws IOException, ClassNotFoundException
    {
        bool fromFile = s.readBoolean();
        if(!fromFile)
        {
            data = (ImageData)s.readObject();
            s.defaultReadObject();
        } else
        {
            data = new ImageData(pathFileName);
            s.defaultReadObject();
        }
        createTexture();
    }
    private void writeObject(ObjectOutputStream s)
        throws IOException
    {
        bool fromFile = pathFileName == nullptr;
        if(!fromFile)
        {
            if(data == nullptr)
                data = new ImageData(this, getData());
            s.writeBoolean(false);
            s.writeObject(data);
            s.defaultWriteObject();
        } else
        {
            s.writeBoolean(true);
            s.defaultWriteObject();
        }
    }
    private static final long serialVersionUID = 0x3d30d0c5c73dc25aL;
    public static bool USE_MIPMAP = false;
    public static bool FREE_MEMORY = true;
    public static THashMap TextureIDMap = new THashMap();
    public static Stack TextureIDStack = new Stack();
    static bool bAlt = false;
    protected transient ImageData data;
    protected int height;
    protected int heightHW;
    protected transient int id;
    protected transient IntBuffer idBuffer;
    protected std::string pathFileName;
    protected bool solid;
    protected int width;
    protected int widthHW;
    ArrayList alphaList;
    int referenceCount;
    public static bool UseFiltering = false;
}
} // namespace
