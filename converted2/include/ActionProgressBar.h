#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ActionProgressBar.java
namespace zombie {
namespace ui {
#include "Color.h"
#include "Texture.h"
#include "TexturePackPage.h"
// Referenced classes of package zombie.ui:
//            UIElement
class ActionProgressBar : public UIElement {
public:
{
    public ActionProgressBar(int x, int y)
    {
        deltaValue = 1.0F;
        background = TexturePackPage.getTexture("BuildBar_Bkg");
        foreground = TexturePackPage.getTexture("BuildBar_Bar");
        this.x = x;
        this.y = y;
        width = background.getWidth();
        height = background.getHeight();
        followGameWorld = true;
    }
    public void render()
    {
        if(!isVisible())
        {
            return;
        } else
        {
            DrawUVSliceTexture(background, 0, 0, background.getWidth(), background.getHeight(), Color.white, 0.0F, 0.0F, 1.0F, 1.0F);
            DrawUVSliceTexture(foreground, 3, 0, foreground.getWidth(), foreground.getHeight(), Color.white, 0.0F, 0.0F, deltaValue, 1.0F);
            return;
        }
    }
    public void setValue(float delta)
    {
        deltaValue = delta;
    }
    public float getValue()
    {
        return deltaValue;
    }
    Texture background;
    Texture foreground;
    float deltaValue;
}
} // namespace
