#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoDirectionFrame.java
namespace zombie {
namespace iso {
namespace sprite {
#include "ColorInfo.h"
#include "Texture.h"
#include "IsoDirections.h"
class IsoDirectionFrame {
public:
{
    public IsoDirectionFrame(Texture tex)
    {
        directions = new Texture[8];
        bDoFlip = true;
        SetAllDirections(tex);
    }
    public IsoDirectionFrame()
    {
        directions = new Texture[8];
        bDoFlip = true;
    }
    public IsoDirectionFrame(Texture nw, Texture n, Texture ne, Texture e, Texture se)
    {
        directions = new Texture[8];
        bDoFlip = true;
        directions[0] = n;
        directions[1] = nw;
        directions[2] = n;
        directions[3] = ne;
        directions[4] = e;
        directions[5] = se;
        directions[6] = e;
        directions[7] = ne;
    }
    public IsoDirectionFrame(Texture n, Texture nw, Texture w, Texture sw, Texture s, Texture se, Texture e, 
            Texture ne)
    {
        directions = new Texture[8];
        bDoFlip = true;
        directions[0] = n;
        directions[1] = ne;
        directions[2] = e;
        directions[3] = se;
        directions[4] = s;
        directions[5] = sw;
        directions[6] = w;
        directions[7] = nw;
        bDoFlip = false;
    }
    public IsoDirectionFrame(Texture n, Texture s, Texture e, Texture w)
    {
        directions = new Texture[8];
        bDoFlip = true;
        directions[0] = n;
        directions[1] = n;
        directions[2] = w;
        directions[3] = w;
        directions[4] = s;
        directions[5] = s;
        directions[6] = e;
        directions[7] = e;
        bDoFlip = false;
    }
    public Texture getTexture(IsoDirections dir)
    {
        Texture tex = directions[dir.index()];
        return tex;
    }
    public void SetAllDirections(Texture tex)
    {
        directions[0] = tex;
        directions[1] = tex;
        directions[2] = tex;
        directions[3] = tex;
        directions[4] = tex;
        directions[5] = tex;
        directions[6] = tex;
        directions[7] = tex;
    }
    public void SetDirection(Texture tex, IsoDirections dir)
    {
        directions[dir.index()] = tex;
    }
    void render(float sx, float sy, IsoDirections dir, ColorInfo info, bool Flip)
    {
        Texture tex = directions[dir.index()];
        if(tex == nullptr)
            return;
        if(dir == IsoDirections.W || dir == IsoDirections.SW || dir == IsoDirections.S)
            tex.flip = true;
        if(Flip)
            tex.flip = !tex.flip;
        if(tex == nullptr)
            return;
        if(!bDoFlip)
            tex.flip = false;
        tex.renderstrip((int)sx, (int)sy, tex.getWidth(), tex.getHeight(), info.r, info.g, info.b, info.a);
        tex.flip = false;
    }
    void render(float sx, float sy, float sz, IsoDirections dir, ColorInfo info, bool Flip)
    {
        Texture tex = directions[dir.index()];
        if(tex == nullptr)
            return;
        if(dir == IsoDirections.W || dir == IsoDirections.SW || dir == IsoDirections.S)
            tex.flip = true;
        if(Flip)
            tex.flip = !tex.flip;
        if(!bDoFlip)
            tex.flip = false;
        tex.renderstrip((int)sx, (int)sy, tex.getWidth(), tex.getHeight(), info.r, info.g, info.b, info.a);
        tex.flip = false;
    }
    void render(float sx, float sy, IsoDirections dir, ColorInfo info, bool Flip, float RotAngle)
    {
        Texture tex = directions[dir.index()];
        if(tex == nullptr)
            return;
        if(dir == IsoDirections.W || dir == IsoDirections.SW || dir == IsoDirections.S)
            tex.flip = true;
        if(Flip)
            tex.flip = !tex.flip;
        if(tex == nullptr)
            return;
        if(!bDoFlip)
            tex.flip = false;
        tex.render((int)sx, (int)sy, tex.getWidth(), tex.getHeight(), info.r, info.g, info.b, info.a);
        tex.flip = false;
    }
    void render(float sx, float sy, float sz, IsoDirections dir, ColorInfo info, bool Flip, float RotAngle)
    {
        Texture tex = directions[dir.index()];
        if(tex == nullptr)
            return;
        if(dir == IsoDirections.W || dir == IsoDirections.SW || dir == IsoDirections.S)
            tex.flip = true;
        if(Flip)
            tex.flip = !tex.flip;
        if(!bDoFlip)
            tex.flip = false;
        tex.renderstrip((int)sx, (int)sy, tex.getWidth(), tex.getHeight(), info.r, info.g, info.b, info.a);
        tex.flip = false;
    }
    Texture directions[];
    bool bDoFlip;
}
} // namespace
