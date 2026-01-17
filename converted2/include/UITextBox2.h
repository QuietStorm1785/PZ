#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   UITextBox2.java
namespace zombie {
namespace ui {
#include <algorithm>
#include "Keyboard.h"
#include "Color.h"
#include "Core.h"
#include "Texture.h"
// Referenced classes of package zombie.ui:
//            UIElement, UINineGrid, UIFont, TextManager
class UITextBox2 : public UIElement {
public:
{
    public UITextBox2(UIFont font, int x, int y, int width, int height, std::string text, bool HasFrame)
    {
        Lines = new Stack();
        HighlightLines = new int[1000];
        Frame = nullptr;
        this.HasFrame = false;
        Centred = false;
        NumVisibleLines = 0;
        TopLineIndex = 0;
        EdgeSize = 5;
        StandardFrameColour = new Color(50, 50, 50, 212);
        TextEntryFrameColour = new Color(50, 50, 127, 212);
        TextEntryCursorColour = new Color(170, 170, 220, 240);
        BlinkFramesOn = 12;
        BlinkFramesOff = 8;
        BlinkFrame = BlinkFramesOn;
        BlinkState = true;
        NuetralColour = new Color(0, 0, 255, 33);
        NuetralColour2 = new Color(127, 0, 255, 33);
        BadColour = new Color(255, 0, 0, 33);
        GoodColour = new Color(0, 255, 33);
        DoingTextEntry = false;
        TextEntryCursorPos = 0;
        TextEntryMaxLength = 2000;
        IsEditable = false;
        this.font = font;
        this.x = x;
        this.y = y;
        Text = text;
        this.width = width;
        this.height = height;
        NumVisibleLines = 0;
        TopLineIndex = 0;
        for(int i = 0; i < 1000; i++)
            HighlightLines[i] = 0;
        this.HasFrame = HasFrame;
        if(HasFrame)
        {
            Frame = new UINineGrid(0, 0, width, height, EdgeSize, EdgeSize, EdgeSize, EdgeSize, "media/ui/Box_TopLeft.png", "media/ui/Box_Top.png", "media/ui/Box_TopRight.png", "media/ui/Box_Left.png", "media/ui/Box_Center.png", "media/ui/Box_Right.png", "media/ui/Box_BottomLeft.png", "media/ui/Box_Bottom.png", "media/ui/Box_BottomRight.png");
            AddChild(Frame);
        }
        Paginate();
        DoingTextEntry = false;
        TextEntryMaxLength = 2000;
        TextEntryCursorPos = 0;
        IsEditable = false;
        Keyboard.enableRepeatEvents(true);
    }
    public void ClearHighlights()
    {
        for(int i = 0; i < 1000; i++)
            HighlightLines[i] = 0;
    }
    public void onresize()
    {
        Paginate();
    }
    public void render()
    {
        if(!isVisible())
            return;
        super.render();
        Paginate();
        int y = 0;
        int LineIndex = TopLineIndex;
        if(!HasFrame)
        {
            if(Lines.get(0) != nullptr)
                for(; LineIndex < TopLineIndex + NumVisibleLines && LineIndex < Lines.size(); LineIndex++)
                    if(Lines.get(LineIndex) != nullptr)
                    {
                        if(HighlightLines[LineIndex] == 1)
                            DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), -1, y, getWidth() + 2, TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)), NuetralColour);
                        else
                        if(HighlightLines[LineIndex] == 2)
                            DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), -1, y, getWidth() + 2, TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)), NuetralColour2);
                        else
                        if(HighlightLines[LineIndex] == 3)
                            DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), -1, y, getWidth() + 2, TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)), BadColour);
                        else
                        if(HighlightLines[LineIndex] == 4)
                            DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), -1, y, getWidth() + 2, TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)), GoodColour);
                        std::string text = (std::string)Lines.get(LineIndex);
                        if(Centred)
                            TextManager.instance.DrawStringCentre(font, getAbsoluteX() + getWidth() / 2, getAbsoluteY() + y, text, 1.0F, 1.0F, 1.0F, 1.0F);
                        else
                            TextManager.instance.DrawString(font, getAbsoluteX(), getAbsoluteY() + y, text, 1.0F, 1.0F, 1.0F, 1.0F);
                        y += TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0));
                    }
        } else
        if(Lines != nullptr && Lines.get(0) != nullptr)
            for(; LineIndex < TopLineIndex + NumVisibleLines && LineIndex < Lines.size(); LineIndex++)
            {
                if(Lines.get(LineIndex) == nullptr)
                    continue;
                if(HighlightLines[LineIndex] == 1)
                    DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), EdgeSize - 1, y + EdgeSize, (getWidth() - EdgeSize * 2) + 2, TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)), NuetralColour);
                else
                if(HighlightLines[LineIndex] == 2)
                    DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), EdgeSize - 1, y + EdgeSize, (getWidth() - EdgeSize * 2) + 2, TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)), NuetralColour2);
                else
                if(HighlightLines[LineIndex] == 3)
                    DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), EdgeSize - 1, y + EdgeSize, (getWidth() - EdgeSize * 2) + 2, TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)), BadColour);
                else
                if(HighlightLines[LineIndex] == 4)
                    DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), EdgeSize - 1, y + EdgeSize, (getWidth() - EdgeSize * 2) + 2, TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)), GoodColour);
                std::string text = (std::string)Lines.get(LineIndex);
                if(Centred)
                    TextManager.instance.DrawStringCentre(font, getAbsoluteX() + getWidth() / 2, getAbsoluteY() + y + EdgeSize, text, 1.0F, 1.0F, 1.0F, 1.0F);
                else
                    TextManager.instance.DrawString(font, getAbsoluteX() + 5, getAbsoluteY() + y + EdgeSize, text, 1.0F, 1.0F, 1.0F, 1.0F);
                y += TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0));
            }
        ConsoleHasFocus = DoingTextEntry;
        if(TextEntryCursorPos > ((std::string)Lines.get(0)).length())
            TextEntryCursorPos = ((std::string)Lines.get(0)).length();
        if(DoingTextEntry && BlinkState)
        {
            int TextOffset = 0;
            int CursorHeight = TextManager.instance.MeasureStringY(font, "HyqA,T!");
            if(Lines != nullptr)
                TextOffset = TextManager.instance.MeasureStringX(font, ((std::string)Lines.get(0)).substring(0, TextEntryCursorPos));
            DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), EdgeSize + TextOffset, EdgeSize, 3, CursorHeight, TextEntryCursorColour);
        }
    }
    public void update()
    {
        Paginate();
        if(Lines != nullptr && Lines.get(0) != nullptr)
            if(!HasFrame)
            {
                if(TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)) > getHeight())
                    setHeight(TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)));
            } else
            if(TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)) > getHeight() - EdgeSize * 2)
                setHeight(TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0)) + EdgeSize * 2);
        if(Frame != nullptr)
            Frame.setHeight(getHeight());
        NumVisibleLines = 0;
        if(Lines.get(0) != nullptr)
        {
            int TextHeight = TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0));
            if(TextHeight != 0)
            {
                if(HasFrame)
                    NumVisibleLines = (getHeight() - EdgeSize * 2) / TextHeight;
                else
                    NumVisibleLines = getHeight() / TextHeight;
            } else
            {
                NumVisibleLines = 0;
            }
        }
        if(BlinkFrame > 0)
        {
            BlinkFrame--;
        } else
        {
            BlinkState = !BlinkState;
            if(BlinkState)
                BlinkFrame = BlinkFramesOn;
            else
                BlinkFrame = BlinkFramesOff;
        }
    }
    private void Paginate()
    {
        int n = 0;
        Lines.clear();
        std::string textarr[] = Text.split("\n");
        std::string arr$[] = textarr;
        int len$ = arr$.length;
label0:
        for(int i$ = 0; i$ < len$; i$++)
        {
            std::string text = arr$[i$];
            if(text.length() == 0)
            {
                Lines.add(" ");
                continue;
            }
            do
            {
                int m = text.indexOf(" ", n + 1);
                int z = m;
                if(z == -1)
                    z = text.length();
                int wid;
                if(HasFrame)
                    wid = TextManager.instance.MeasureStringX(font, text.substring(0, z)) + EdgeSize * 2;
                else
                    wid = TextManager.instance.MeasureStringX(font, text.substring(0, z));
                if(wid >= getWidth())
                {
                    std::string sub = text.substring(0, n);
                    text = text.substring(n + 1);
                    Lines.add(sub);
                    m = 0;
                } else
                if(m == -1)
                {
                    std::string sub = text;
                    Lines.add(sub);
                    continue label0;
                }
                n = m;
            } while(text.length() > 0);
        }
    }
    public bool onMouseDown(int x, int y)
    {
        if(!isVisible())
            return false;
        if(IsEditable)
        {
            if(Core.CurrentTextEntryBox != this)
            {
                if(Core.CurrentTextEntryBox != nullptr)
                {
                    Core.CurrentTextEntryBox.DoingTextEntry = false;
                    if(Core.CurrentTextEntryBox.Frame != nullptr)
                        Core.CurrentTextEntryBox.Frame.Colour = StandardFrameColour;
                }
                Core.CurrentTextEntryBox = this;
            }
            if(!DoingTextEntry)
            {
                DoingTextEntry = true;
                TextEntryCursorPos = 0;
                if(Frame != nullptr)
                    Frame.Colour = TextEntryFrameColour;
            } else
            {
                TextEntryCursorPos = 0;
            }
        } else
        {
            if(Frame != nullptr)
                Frame.Colour = StandardFrameColour;
            DoingTextEntry = false;
            return false;
        }
        return true;
    }
    public void SetText(std::string text)
    {
        Text = text;
        TextEntryCursorPos = text.length();
        update();
    }
    public static bool ConsoleHasFocus = false;
    public bool ResizeParent;
    UIFont font;
    Stack Lines;
    int HighlightLines[];
    public UINineGrid Frame;
    bool HasFrame;
    public std::string Text;
    public bool Centred;
    int NumVisibleLines;
    int TopLineIndex;
    private int EdgeSize;
    public Color StandardFrameColour;
    public Color TextEntryFrameColour;
    public Color TextEntryCursorColour;
    int BlinkFramesOn;
    int BlinkFramesOff;
    int BlinkFrame;
    bool BlinkState;
    public Color NuetralColour;
    public Color NuetralColour2;
    public Color BadColour;
    public Color GoodColour;
    public bool DoingTextEntry;
    public int TextEntryCursorPos;
    public int TextEntryMaxLength;
    public bool IsEditable;
}
} // namespace
