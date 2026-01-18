#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Style.java
namespace zombie {
namespace core {
namespace Styles {
// Referenced classes of package zombie.core.Styles:
//            AlphaOp, GeometryData
class Style {
public:
    virtual ~Style() = default;
{
    public abstract void setupState();
    public abstract void resetState();
    public abstract int getStyleID();
    public abstract AlphaOp getAlphaOp();
    public abstract bool getRenderSprite();
    public abstract GeometryData build();
    public abstract void render(int i, int j);
}
} // namespace
