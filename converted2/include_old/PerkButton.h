#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   PerkButton.java
namespace zombie {
namespace ui {
#include "FrameLoader.h"
#include "Texture.h"
// Referenced classes of package zombie.ui:
//            UIElement, UIEventHandler
class PerkButton : public UIElement {
public:
{
    public PerkButton(std::string name, int x, int y, Texture texture, bool bAvailable, bool bPicked, UIEventHandler handler)
    {
        clicked = false;
        overicon = nullptr;
        mouseOver = false;
        this.bPicked = false;
        this.bAvailable = false;
        notclickedAlpha = 0.85F;
        clickedalpha = 1.0F;
        if(FrameLoader.bServer)
            return;
        this.bAvailable = bAvailable;
        this.bPicked = bPicked;
        this.texture = texture;
        this.handler = handler;
        this.name = name;
        if(this.texture == nullptr)
            this.texture = texture;
        this.x = x;
        this.y = y;
        width = this.texture.getWidth();
        height = this.texture.getHeight();
    }
    public bool onMouseDown(int x, int y)
    {
        if(bAvailable && !bPicked)
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
        if(display == nullptr)
            return;
        if(!name == display.getClickedValue()))
            mouseOver = false;
    }
    public bool onMouseUp(int x, int y)
    {
        if(clicked)
            if(display != nullptr)
                display.ButtonClicked(name);
            else
            if(handler != nullptr)
                handler.Selected(name, 0, 0);
        clicked = false;
        return true;
    }
    public void render()
    {
        int dy = 0;
        if(clicked)
            dy++;
        float notclickedalpha = 1.0F;
        if(bAvailable && !bPicked)
            notclickedalpha = 0.5F;
        if(!bAvailable)
            notclickedalpha = 0.2F;
        if(bPicked)
            notclickedalpha = 1.0F;
        DrawTextureScaled(texture, 0, dy, getWidth(), getHeight(), notclickedalpha);
        super.render();
    }
    public void update()
    {
        super.update();
    }
    bool clicked;
    UIElement display;
    Texture overicon;
    bool mouseOver;
    std::string name;
    Texture texture;
    bool bPicked;
    bool bAvailable;
    UIEventHandler handler;
    public float notclickedAlpha;
    public float clickedalpha;
}
} // namespace
