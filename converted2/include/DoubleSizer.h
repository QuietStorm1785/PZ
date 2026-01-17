#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   DoubleSizer.java
namespace zombie {
namespace ui {
#include "Core.h"
#include "Texture.h"
// Referenced classes of package zombie.ui:
//            UIElement
class DoubleSizer : public UIElement {
public:
{
    public DoubleSizer(int x, int y, std::string texture, std::string highlight, std::string texture2, std::string highlight2)
    {
        clicked = false;
        mouseOver = false;
        display = display;
        this.texture = Texture.getSharedTexture((new StringBuilder()).append("media/ui/").append(texture).append(".png").toString());
        this.highlight2 = Texture.getSharedTexture((new StringBuilder()).append("media/ui/").append(highlight2).append(".png").toString());
        this.texture2 = Texture.getSharedTexture((new StringBuilder()).append("media/ui/").append(texture2).append(".png").toString());
        this.highlight = Texture.getSharedTexture((new StringBuilder()).append("media/ui/").append(highlight).append(".png").toString());
        this.x = x;
        this.y = y;
        width = this.texture.getWidth();
        height = this.texture.getHeight();
    }
    public bool onMouseDown(int x, int y)
    {
        clicked = true;
        return true;
    }
    public bool onMouseMove(int dx, int dy)
    {
        mouseOver = true;
        return true;
    }
    public void onMouseMoveOutside(int dx, int dy)
    {
        clicked = false;
        mouseOver = false;
    }
    public bool onMouseUp(int x, int y)
    {
        if(clicked)
            Core.getInstance().doubleSizeToggle();
        clicked = false;
        return true;
    }
    public void render()
    {
        if(clicked)
            DrawTextureScaled(highlight, 0, 0, highlight.getWidth(), highlight.getHeight(), 1.0F);
        else
        if(mouseOver)
            DrawTextureScaled(texture, 0, 0, texture.getWidth(), texture.getHeight(), 1.0F);
        else
            DrawTextureScaled(texture, 0, 0, texture.getWidth(), texture.getHeight(), 0.85F);
        super.render();
    }
    public void update()
    {
        super.update();
    }
    bool clicked;
    UIElement display;
    Texture highlight;
    Texture highlight2;
    bool mouseOver;
    Texture texture;
    Texture texture2;
}
} // namespace
