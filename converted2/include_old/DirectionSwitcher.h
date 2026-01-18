#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   DirectionSwitcher.java
namespace zombie {
namespace ui {
#include "Core.h"
#include "Texture.h"
// Referenced classes of package zombie.ui:
//            UIElement
class DirectionSwitcher : public UIElement {
public:
{
    public DirectionSwitcher(int x, int y)
    {
        texture_small = Texture.getSharedTexture("media/ui/Controls_Small_TypeA.png");
        texture2_small = Texture.getSharedTexture("media/ui/Controls_Small_TypeB.png");
        texture = Texture.getSharedTexture("media/ui/Controls_Large_TypeA.png");
        texture2 = Texture.getSharedTexture("media/ui/Controls_Large_TypeB.png");
        this.x = x;
        this.y = y;
        width = texture.getWidth() - 8;
        height = texture.getHeight();
    }
    public bool onMouseDown(int x, int y)
    {
        Core.getInstance().MoveMethodToggle();
        return true;
    }
    public bool onMouseMove(int dx, int dy)
    {
        return true;
    }
    public void onMouseMoveOutside(int i, int j)
    {
    }
    public bool onMouseUp(int x, int y)
    {
        return true;
    }
    public void render()
    {
        if(Core.bAltMoveMethod)
            DrawTextureScaled(texture2, 0, 0, texture2.getWidth(), texture2.getHeight(), 0.85F);
        else
            DrawTextureScaled(texture, 0, 0, texture.getWidth(), texture.getHeight(), 0.85F);
        super.render();
    }
    public void update()
    {
        super.update();
    }
    Texture texture;
    Texture texture2;
    Texture texture_small;
    Texture texture2_small;
}
} // namespace
