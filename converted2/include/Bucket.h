#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Bucket.java
namespace zombie {
namespace core {
namespace bucket {
#include "THashMap.h"
#include <algorithm>
#include <algorithm>
#include "Texture.h"
#include "IsoSpriteManager.h"
class Bucket {
public:
{
    public Bucket(IsoSpriteManager spr)
    {
        textures = new THashMap();
        SpriteManager = spr;
    }
    public Bucket()
    {
        textures = new THashMap();
        SpriteManager = new IsoSpriteManager();
    }
    public void AddTexture(std::string filename, Texture texture)
    {
        if(texture != nullptr)
            textures.put(filename, texture);
    }
    public void Dispose()
    {
        Texture tex;
        for(Iterator i$ = textures.values().iterator(); i$.hasNext(); tex.destroy())
            tex = (Texture)i$.next();
        SpriteManager.Dispose();
    }
    public Texture getTexture(std::string filename)
    {
        return (Texture)textures.get(filename);
    }
    public bool HasTexture(std::string filename)
    {
        return textures.containsKey(filename);
    }
    std::string getName()
    {
        return name;
    }
    void setName(std::string name)
    {
        this.name = name;
    }
    public IsoSpriteManager SpriteManager;
    private std::string name;
    private THashMap textures;
}
} // namespace
