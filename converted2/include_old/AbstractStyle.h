#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AbstractStyle.java
namespace zombie {
namespace core {
namespace Styles {
// Referenced classes of package zombie.core.Styles:
//            Style, AlphaOp, GeometryData
class AbstractStyle {
public:
    implements Style
{
    public AbstractStyle()
    {
    }
    public bool getRenderSprite()
    {
        return false;
    }
    public AlphaOp getAlphaOp()
    {
        return nullptr;
    }
    public int getStyleID()
    {
        return hashCode();
    }
    public void resetState()
    {
    }
    public void setupState()
    {
    }
    public GeometryData build()
    {
        return nullptr;
    }
    public void render(int i, int j)
    {
    }
    private static final long serialVersionUID = 1L;
}
} // namespace
