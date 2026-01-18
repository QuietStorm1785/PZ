#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   EndTutorialMessage.java
namespace zombie {
namespace ui {
#include "Core.h"
#include "IngameState.h"
// Referenced classes of package zombie.ui:
//            NewWindow, TextBox, DialogButton, UIFont
class EndTutorialMessage : public NewWindow {
public:
{
    public EndTutorialMessage()
    {
        super(Core.getInstance().getOffscreenWidth() / 2, Core.getInstance().getOffscreenHeight() / 2, 470, 10, true);
        IgnoreLossControl = true;
        std::string help = "This is the end of the tutorial<br><br>Now you're on your own<br><br>Whatever happens next, remember you always have a choice<br><br>But the smart choice may not be the one you want to make";
        TextBox text = new TextBox(UIFont.Medium, 0, 0, 450, help);
        text.Centred = true;
        text.ResizeParent = true;
        text.update();
        Nest(text, 20, 10, 20, 10);
        update();
        AddChild(new DialogButton(this, getWidth() / 2, getHeight() - 18, "Ok", "Ok"));
        x -= width / 2;
        y -= height / 2;
    }
    public void ButtonClicked(std::string name)
    {
        if(name == "Ok"))
        {
            setVisible(false);
            IngameState.instance.Paused = false;
        }
    }
}
} // namespace
