#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   DraggableWindow.java
namespace zombie {
namespace ui {
#include <fstream>
#include <iostream>
#include "AngelCodeFont.h"
#include "Texture.h"
#include "TexturePackPage.h"
// Referenced classes of package zombie.ui:
//            UIElement
class DraggableWindow : public UIElement {
public:
{
    public DraggableWindow(int x, int y, std::string title, std::string background)
        throws FileNotFoundException
    {
        alpha = 1.0F;
        clickX = 0;
        clickY = 0;
        closing = false;
        moving = false;
        rwidth = 256;
        this.background = nullptr;
        titlebar = nullptr;
        font = new AngelCodeFont("media/zombiefont2.fnt", "zombiefont2_0");
        this.background = TexturePackPage.getTexture(background);
        titlebar = TexturePackPage.getTexture(title);
        this.x = x;
        this.y = y;
        width = 256;
        height = 256;
        alpha = 0.75F;
        visible = false;
    }
    public bool onMouseDown(int x, int y)
    {
        super.onMouseDown(x, y);
        if(y < 16 && x < rwidth - 20)
        {
            clickX = x;
            clickY = y;
            moving = true;
            setCapture(true);
        } else
        if(y < 16 && x < getWidth())
            closing = true;
        return true;
    }
    public bool onMouseMove(int dx, int dy)
    {
        super.onMouseMove(dx, dy);
        if(moving)
        {
            setX(getX() + (float)dx);
            setY(getY() + (float)dy);
        }
        return false;
    }
    public bool onMouseUp(int x, int y)
    {
        super.onMouseUp(x, y);
        if(y < 16 && x >= rwidth - 20 && closing)
            setVisible(false);
        moving = false;
        setCapture(false);
        return true;
    }
    public void render()
    {
        if(background == nullptr)
            return;
        if(moving)
            DrawTexture(titlebar, 0, 0, 1.0F);
        else
            DrawTexture(titlebar, 0, 0, 0.75F);
        DrawTexture(background, 0, 16, 0.75F);
        super.render();
    }
    public void update()
    {
        super.update();
    }
    public float alpha;
    public int clickX;
    public int clickY;
    public bool closing;
    public bool moving;
    public int rwidth;
    Texture background;
    AngelCodeFont font;
    Texture titlebar;
}
} // namespace
