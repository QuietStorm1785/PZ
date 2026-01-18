#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   OpenGLState.java
namespace zombie {
namespace core {
namespace opengl {
#include "GL11.h"
#include "IndieGL.h"
class OpenGLState {
public:
{
    public OpenGLState()
    {
    }
    public static final void disableAlphaTest()
    {
        if(!alphaTest)
        {
            return;
        } else
        {
            alphaTest = false;
            return;
        }
    }
    public static final void disableBlending()
    {
        if(!blending)
        {
            return;
        } else
        {
            blending = false;
            IndieGL.glDisable(3042);
            return;
        }
    }
    public static final void disableColorArray()
    {
        if(!colorArray)
        {
            return;
        } else
        {
            colorArray = false;
            GL11.glDisableClientState(32886);
            return;
        }
    }
    public static final void disableNormalArray()
    {
        if(!normalArray)
        {
            return;
        } else
        {
            normalArray = false;
            GL11.glDisableClientState(32885);
            return;
        }
    }
    public static final void disableScissor()
    {
        scissorTestCounter--;
        if(scissorTest)
            if(scissorTestCounter > 0)
            {
                GL11.glPopClientAttrib();
            } else
            {
                IndieGL.glDisable(3089);
                scissorTest = false;
            }
    }
    public static final void disableTextureArray()
    {
        if(!textureArray)
        {
            return;
        } else
        {
            textureArray = false;
            GL11.glDisableClientState(32888);
            return;
        }
    }
    public static final void disableVertexArray()
    {
        if(!vertexArray)
        {
            return;
        } else
        {
            vertexArray = false;
            GL11.glDisableClientState(32884);
            return;
        }
    }
    public static final void disableZtest()
    {
        if(!zTest)
        {
            return;
        } else
        {
            zTest = false;
            return;
        }
    }
    public static final void enableAlphaTest()
    {
        if(alphaTest)
        {
            return;
        } else
        {
            alphaTest = true;
            return;
        }
    }
    public static final void enableBlending()
    {
        if(blending)
        {
            return;
        } else
        {
            blending = true;
            GL11.glEnable(3042);
            return;
        }
    }
    public static final void enableColorArray()
    {
        if(colorArray)
        {
            return;
        } else
        {
            colorArray = true;
            GL11.glEnableClientState(32886);
            return;
        }
    }
    public static final void enableNormalArray()
    {
        if(normalArray)
        {
            return;
        } else
        {
            normalArray = true;
            GL11.glEnableClientState(32885);
            return;
        }
    }
    public static final void enableScissor(int x, int y, int width, int height)
    {
        if(!scissorTest)
        {
            GL11.glEnable(3089);
            scissorTest = true;
        }
        scissorTestCounter++;
        if(scissorTestCounter > 1)
            GL11.glPushClientAttrib(3088);
    }
    public static final void enableTextureArray()
    {
        if(textureArray)
        {
            return;
        } else
        {
            textureArray = true;
            GL11.glEnableClientState(32888);
            return;
        }
    }
    public static final void enableVertexArray()
    {
        if(vertexArray)
        {
            return;
        } else
        {
            vertexArray = true;
            GL11.glEnableClientState(32884);
            return;
        }
    }
    public static final void enableZtest()
    {
        if(zTest)
        {
            return;
        } else
        {
            zTest = true;
            return;
        }
    }
    public static final int getUsedTextureUnit()
    {
        return currentActiveTextureUnit;
    }
    public static final bool isUsedTexureUnit(int unit)
    {
        return currentActiveTextureUnit == unit;
    }
    public static final void useTranspBlendingMode()
    {
        IndieGL.glBlendFunc(770, 771);
    }
    public static int lastTextureID = -1;
    public static int lastlastTextureID = -1;
    protected static bool alphaTest = false;
    protected static bool blending = false;
    protected static bool zTest = false;
    protected static bool vertexArray = false;
    protected static bool colorArray = false;
    protected static bool textureArray = false;
    protected static bool normalArray = false;
    protected static bool scissorTest = false;
    protected static int scissorTestCounter = 0;
    protected static int currentActiveTextureUnit;
}
} // namespace
