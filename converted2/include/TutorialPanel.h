#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TutorialPanel.java
namespace zombie {
namespace ui {
#include <fstream>
#include <iostream>
#include "Core.h"
#include "AngelCodeFont.h"
#include "Texture.h"
#include "TexturePackPage.h"
// Referenced classes of package zombie.ui:
//            UIElement, TextManager, UIFont
class TutorialPanel : public UIElement {
public:
{
    public TutorialPanel()
        throws FileNotFoundException
    {
        alpha = 0.0F;
        alphaStep = 0.05F;
        hiding = false;
        MaxMessageTime = 20;
        MessageTime = 0.0F;
        NextMessage = nullptr;
        NextMessage2 = nullptr;
        showing = false;
        targetAlpha = 0.0F;
        background = nullptr;
        font = new AngelCodeFont("media/zombiefont2.fnt", "zombiefont2_0");
        background = TexturePackPage.getTexture("black");
        width = 650;
        height = 50;
        x = Core.getInstance().getOffscreenWidth() / 2;
        x -= width / 2;
        y = Core.getInstance().getOffscreenHeight();
        y -= 60F;
    }
    public void hide()
    {
        hiding = true;
    }
    public void render()
    {
        if(showing && alpha > 0.0F)
        {
            DrawTextureScaled(background, 0, 0, getWidth(), getHeight(), alpha * 0.75F);
            int y = Core.getInstance().getOffscreenHeight() - 47;
            if(Message2 != nullptr)
                y -= 10;
            TextManager.instance.DrawStringCentre(UIFont.Medium, Core.getInstance().getOffscreenWidth() / 2, y, Message, 1.0F, 1.0F, 1.0F, alpha);
            if(Message2 != nullptr)
                TextManager.instance.DrawStringCentre(UIFont.Medium, Core.getInstance().getOffscreenWidth() / 2, y + 20, Message2, 1.0F, 1.0F, 1.0F, alpha);
        }
    }
    public void ShowMessage(std::string message, std::string message2)
    {
        if(message != nullptr && message == Message) && message2 != nullptr && message2 == Message2))
        {
            return;
        } else
        {
            MessageTime = 0.0F;
            NextMessage = message;
            NextMessage2 = message2;
            showing = true;
            hiding = false;
            return;
        }
    }
    public void update()
    {
        if(NextMessage != nullptr)
            targetAlpha = 0.0F;
        else
        if(Message != nullptr)
            targetAlpha = 1.0F;
        if(hiding)
            targetAlpha = 0.0F;
        if(alpha <= 0.0F && NextMessage != nullptr)
        {
            Message = NextMessage;
            Message2 = NextMessage2;
            NextMessage = nullptr;
            NextMessage2 = nullptr;
        }
        if(alpha < targetAlpha)
        {
            alpha += alphaStep;
            if(alpha > targetAlpha)
                alpha = targetAlpha;
        } else
        if(alpha > targetAlpha)
        {
            alpha -= alphaStep;
            if(alpha < targetAlpha)
                alpha = targetAlpha;
        }
    }
    public float alpha;
    public float alphaStep;
    public bool hiding;
    public int MaxMessageTime;
    public std::string Message;
    public float MessageTime;
    public std::string NextMessage;
    public std::string NextMessage2;
    public bool showing;
    public float targetAlpha;
    Texture background;
    AngelCodeFont font;
    private std::string Message2;
}
} // namespace
