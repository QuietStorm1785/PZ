#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TransparentStyle.java
namespace zombie {
namespace core {
namespace Styles {
#include "GL11.h"
// Referenced classes of package zombie.core.Styles:
//            AbstractStyle, AlphaOp
class TransparentStyle : public AbstractStyle {
public:
{
    public TransparentStyle()
    {
    }
    public void setupState()
    {
        GL11.glBlendFunc(770, 771);
    }
    public void resetState()
    {
    }
    public AlphaOp getAlphaOp()
    {
        return AlphaOp.KEEP;
    }
    public int getStyleID()
    {
        return 2;
    }
    public bool getRenderSprite()
    {
        return true;
    }
    private static final long serialVersionUID = 1L;
    public static TransparentStyle instance = new TransparentStyle();
}
} // namespace
