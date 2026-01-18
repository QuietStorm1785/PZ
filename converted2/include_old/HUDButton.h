#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   HUDButton.java
namespace zombie {
namespace ui {
#include "FrameLoader.h"
#include "Texture.h"
#include "TexturePackPage.h"
// Referenced classes of package zombie.ui:
//            UIElement, UIEventHandler
class HUDButton : public UIElement {
public:
{
    public HUDButton(std::string name, int x, int y, std::string texture, std::string highlight, UIElement display)
    {
        clicked = false;
        overicon = nullptr;
        mouseOver = false;
        notclickedAlpha = 0.85F;
        clickedalpha = 1.0F;
        if(FrameLoader.bServer)
            return;
        this.display = display;
        this.name = name;
        if(this.texture == nullptr)
        {
            this.texture = Texture.getSharedTexture(texture);
            this.highlight = Texture.getSharedTexture(highlight);
        }
        this.x = x;
        this.y = y;
        width = this.texture.getWidth();
        height = this.texture.getHeight();
    }
    public HUDButton(std::string name, int x, int y, std::string texture, std::string highlight, UIEventHandler handler)
    {
        clicked = false;
        overicon = nullptr;
        mouseOver = false;
        notclickedAlpha = 0.85F;
        clickedalpha = 1.0F;
        if(FrameLoader.bServer)
            return;
        this.texture = TexturePackPage.getTexture(texture);
        this.highlight = TexturePackPage.getTexture(highlight);
        this.handler = handler;
        this.name = name;
        if(this.texture == nullptr)
        {
            this.texture = Texture.getSharedTexture(texture);
            this.highlight = Texture.getSharedTexture(highlight);
        }
        this.x = x;
        this.y = y;
        width = this.texture.getWidth();
        height = this.texture.getHeight();
    }
    public HUDButton(std::string name, int x, int y, std::string texture, std::string highlight, std::string overicon, UIElement display)
    {
        clicked = false;
        this.overicon = nullptr;
        mouseOver = false;
        notclickedAlpha = 0.85F;
        clickedalpha = 1.0F;
        if(FrameLoader.bServer)
            return;
        this.overicon = Texture.getSharedTexture(overicon);
        this.display = display;
        this.texture = TexturePackPage.getTexture(texture);
        this.highlight = TexturePackPage.getTexture(highlight);
        this.name = name;
        if(this.texture == nullptr)
        {
            this.texture = Texture.getSharedTexture(texture);
            this.highlight = Texture.getSharedTexture(highlight);
        }
        this.x = x;
        this.y = y;
        width = this.texture.getWidth();
        height = this.texture.getHeight();
    }
    public HUDButton(std::string name, int x, int y, std::string texture, std::string highlight, std::string overicon, UIEventHandler handler)
    {
        clicked = false;
        this.overicon = nullptr;
        mouseOver = false;
        notclickedAlpha = 0.85F;
        clickedalpha = 1.0F;
        if(FrameLoader.bServer)
            return;
        this.texture = TexturePackPage.getTexture(texture);
        this.highlight = TexturePackPage.getTexture(highlight);
        this.overicon = Texture.getSharedTexture(overicon);
        this.handler = handler;
        this.name = name;
        if(this.texture == nullptr)
        {
            this.texture = Texture.getSharedTexture(texture);
            this.highlight = Texture.getSharedTexture(highlight);
        }
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
        if(mouseOver || name == display.getClickedValue()))
            DrawTextureScaled(highlight, 0, dy, getWidth(), getHeight(), clickedalpha);
        else
            DrawTextureScaled(texture, 0, dy, getWidth(), getHeight(), notclickedAlpha);
        if(overicon != nullptr)
            DrawTextureScaled(overicon, 0, dy, overicon.getWidth(), overicon.getHeight(), 1.0F);
        super.render();
    }
    public void update()
    {
        super.update();
    }
    bool clicked;
    UIElement display;
    Texture highlight;
    Texture overicon;
    bool mouseOver;
    std::string name;
    Texture texture;
    UIEventHandler handler;
    public float notclickedAlpha;
    public float clickedalpha;
}
} // namespace
