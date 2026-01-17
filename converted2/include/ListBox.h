#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ListBox.java
namespace zombie {
namespace ui {
#include <algorithm>
#include "Color.h"
#include "Texture.h"
#include "IListBoxItem.h"
// Referenced classes of package zombie.ui:
//            UIElement, UIEventHandler
class ListBox : public UIElement {
public:
{
    public static class ListItem
    {
        public Color leftCol;
        public Color rightCol;
        public Color backCol;
        public IListBoxItem item;
        public bool bDisabled;
        public Texture Icon;
        public ListItem(IListBoxItem item, Color leftCol, Color rightCol, Color backCol)
        {
            bDisabled = false;
            Icon = nullptr;
            this.item = item;
            bDisabled = false;
            this.leftCol = leftCol;
            this.rightCol = rightCol;
            this.backCol = backCol;
        }
        public ListItem(IListBoxItem item, Texture IconTex, Color leftCol, Color rightCol, Color backCol)
        {
            bDisabled = false;
            Icon = nullptr;
            this.item = item;
            bDisabled = false;
            this.leftCol = leftCol;
            this.rightCol = rightCol;
            this.backCol = backCol;
            Icon = IconTex;
        }
        public ListItem(IListBoxItem item, Color leftCol, Color rightCol, Color backCol, bool bDisabled)
        {
            this.bDisabled = false;
            Icon = nullptr;
            this.item = item;
            this.bDisabled = bDisabled;
            this.leftCol = leftCol;
            this.rightCol = rightCol;
            this.backCol = backCol;
        }
    }
    public ListBox(std::string name, UIEventHandler messages)
    {
        background = new Color(255, 255, 255, 10);
        selColour = new Color(0, 0, 255, 10);
        selColourDis = new Color(255, 0, 255, 30);
        itemHeight = 20;
        topIndex = 0;
        timeSinceClick = 0;
        clicked = false;
        mouseOver = false;
        Selected = -1;
        LastSelected = -1;
        Items = new Stack();
        messageParent = messages;
        this.name = name;
    }
    public void SetItemHeight(int NewHeight)
    {
        itemHeight = NewHeight;
    }
    private void Selected(int Selected)
    {
        messageParent.Selected(name, Selected, LastSelected);
    }
    public void remove(IListBoxItem remove)
    {
        for(int n = 0; n < Items.size(); n++)
            if(((ListItem)Items.get(n)).item == remove)
            {
                Items.remove(n);
                n--;
            }
    }
    public IListBoxItem getSelected()
    {
        if(Selected != -1)
            return ((ListItem)Items.get(Selected)).item;
        else
            return nullptr;
    }
    public void AddItem(IListBoxItem item, Color leftCol, Color rightCol, Color backCol)
    {
        Items.add(new ListItem(item, leftCol, rightCol, backCol));
    }
    public void AddItem(IListBoxItem item, Texture IconTex, Color leftCol, Color rightCol, Color backCol)
    {
        Items.add(new ListItem(item, IconTex, leftCol, rightCol, backCol));
    }
    public void AddItem(IListBoxItem item, Color leftCol, Color rightCol, Color backCol, bool bDisabled)
    {
        Items.add(new ListItem(item, leftCol, rightCol, backCol, bDisabled));
    }
    public void AddItem(IListBoxItem item, std::string IconName, Color leftCol, Color rightCol, Color backCol)
    {
        Items.add(new ListItem(item, leftCol, rightCol, backCol));
    }
    public void AddItem(IListBoxItem item, std::string IconName, Color leftCol, Color rightCol, Color backCol, bool bDisabled)
    {
        Items.add(new ListItem(item, leftCol, rightCol, backCol, bDisabled));
    }
    public void render()
    {
        DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), 0, 0, getWidth(), getHeight(), background);
        for(int n = topIndex; n < Items.size() && n < topIndex + getHeight() / itemHeight; n++)
        {
            Texture ItemTex = ((ListItem)Items.get(n)).Icon;
            ListItem item = (ListItem)Items.get(n);
            int y = (n - topIndex) * itemHeight;
            if(Selected == n)
            {
                if(((ListItem)Items.get(Selected)).bDisabled)
                    DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), 0, y + 1, getWidth(), itemHeight - 2, selColourDis);
                else
                    DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), 0, y + 1, getWidth(), itemHeight - 2, selColour);
            } else
            if(((ListItem)Items.get(n)).bDisabled)
                DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), 0, y + 1, getWidth(), itemHeight - 2, new Color(0.4F, 0.2F, 0.2F, 0.5F));
            else
                DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), 0, y + 1, getWidth(), itemHeight - 2, item.backCol);
            if(ItemTex == nullptr)
            {
                DrawText(item.item.getLeftLabel(), 10, (y + itemHeight / 2) - 6, item.leftCol.r, item.leftCol.g, item.leftCol.b, item.leftCol.a);
                DrawTextRight(item.item.getRightLabel(), (0 + getWidth()) - 10, (y + itemHeight / 2) - 6, item.rightCol.r, item.rightCol.g, item.rightCol.b, item.rightCol.a);
                continue;
            }
            if(((ListItem)Items.get(n)).bDisabled)
                DrawTextureScaledCol(ItemTex, 2, y + 2, ItemTex.getWidth(), ItemTex.getWidth(), Color.gray);
            else
                DrawTextureScaledCol(ItemTex, 2, y + 2, ItemTex.getWidth(), ItemTex.getWidth(), Color.white);
            DrawText(item.item.getLeftLabel(), 10 + ItemTex.getWidth() + 4, (y + itemHeight / 2) - 6, item.leftCol.r, item.leftCol.g, item.leftCol.b, item.leftCol.a);
            DrawTextRight(item.item.getRightLabel(), ((0 + getWidth()) - 10) + ItemTex.getWidth() + 4, (y + itemHeight / 2) - 6, item.rightCol.r, item.rightCol.g, item.rightCol.b, item.rightCol.a);
        }
    }
    public bool onMouseMove(int dx, int dy)
    {
        mouseOver = true;
        return true;
    }
    public void onMouseMoveOutside(int dx, int dy)
    {
        mouseOver = false;
    }
    private void DoubleClick(int mx, int my)
    {
        if(Selected != -1 && !((ListItem)Items.get(Selected)).bDisabled)
            messageParent.DoubleClick(name, mx, my);
    }
    public bool onMouseUp(int x, int y)
    {
        if(clicked)
        {
            timeSinceClick = 0;
            LastSelected = this.Selected;
            int Selected = y / itemHeight;
            Selected += topIndex;
            if(Selected < Items.size() && Selected >= 0)
            {
                this.Selected = Selected;
                Selected(Selected);
            }
        }
        clicked = false;
        setCapture(false);
        return false;
    }
    public void update()
    {
        super.update();
        timeSinceClick++;
    }
    public bool onMouseDown(int x, int y)
    {
        if(timeSinceClick < 10)
            DoubleClick(x, y);
        clicked = true;
        setCapture(true);
        return false;
    }
    public Color background;
    public Color selColour;
    public Color selColourDis;
    public int itemHeight;
    public int topIndex;
    int timeSinceClick;
    bool clicked;
    private bool mouseOver;
    public int Selected;
    public int LastSelected;
    UIEventHandler messageParent;
    private std::string name;
    public Stack Items;
}
} // namespace
