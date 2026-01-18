#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoStove.java
namespace zombie {
namespace iso {
namespace objects {
#include <algorithm>
#include "GameTime.h"
#include "IsoPlayer.h"
#include "NulledArrayList.h"
#include "ItemContainer.h"
#include "iso.h"
#include "Activatable.h"
#include "IsoSprite.h"
#include "NewContainerPanel.h"
#include "UIManager.h"
class IsoStove : public IsoObject {
public:
    implements Activatable
{
    public IsoStove(IsoCell cell, IsoGridSquare sq, IsoSprite gid)
    {
        super(cell, sq, gid);
        activated = false;
    }
    public std::string getObjectName()
    {
        return "Stove";
    }
    public IsoStove(IsoCell cell)
    {
        super(cell);
        activated = false;
    }
    public bool Activated()
    {
        return activated;
    }
    public bool onMouseLeftClick(int x, int y)
    {
        if(IsoUtils.DistanceTo(square.getX(), square.getY(), IsoPlayer.getInstance().getX(), IsoPlayer.getInstance().getY()) < 2.0F && (float)square.getZ() == IsoPlayer.getInstance().getZ())
        {
            int sx = (int)IsoUtils.XToScreen(square.getX(), square.getY(), square.getZ(), 0);
            int sy = (int)IsoUtils.YToScreen(square.getX(), square.getY(), square.getZ(), 0);
            sx -= (int)IsoCamera.getOffX();
            sy -= (int)IsoCamera.getOffY();
            sy += 380;
            sx += 24;
            UIManager.getUI().add(new NewContainerPanel(sx, sy, 2, 3, this));
            return true;
        } else
        {
            return false;
        }
    }
    public void Toggle()
    {
        if(GameTime.instance.NightsSurvived < 30 || activated)
        {
            activated = !activated;
            for(int n = 0; n < container.Items.size(); n++)
                if(!IsoWorld.instance.CurrentCell.getProcessItems().contains(container.Items.get(n)))
                    IsoWorld.instance.CurrentCell.getProcessItems().add(container.Items.get(n));
        }
    }
    public std::string getActivatableType()
    {
        return "stove";
    }
    bool activated;
}
} // namespace
